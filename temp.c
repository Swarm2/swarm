/*
 * uart_interrupt.c
 *
 *  Created on: 29-May-2019
 *      Author: Mayuresh
 */
#include "stdint.h"
#include "stdbool.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
#include "driverlib/interrupt.h"
uint32_t c=0;
char request[25]="which color to blink";
void ISR(void)
{

        c=UARTCharGetNonBlocking(UART0_BASE);
        UARTCharPut(UART0_BASE,c);

}

int main()
{
    //uint32_t *i=0,*j=0;
    int i=0;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART0_BASE,SysCtlClockGet(), 9600,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    IntMasterEnable();
   // IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
    IntRegister(INT_UART0,ISR);                             //ISR is a name of function used as interrupt handler
    UARTIntRegister(UART0_BASE, ISR);
    UARTFIFODisable(UART0_BASE);
    UARTFIFOEnable(UART0_BASE);
    UARTFIFOLevelSet(UART0_BASE,UART_FIFO_TX4_8,UART_FIFO_RX4_8);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);
    //UARTFIFOLevelGet(UART0_BASE,i,j);
    for(i=0;request[i]!='\0';i++)
    {

        UARTCharPut(UART0_BASE,request[i]);

    }

    while(1)
        {
        //GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_3,0xFF);
       //SysCtlDelay(1000000);
        GPIOPinWrite(GPIO_PORTF_BASE,c,0xFF);
        SysCtlDelay(1000000);
        GPIOPinWrite(GPIO_PORTF_BASE,c,0x00);
        SysCtlDelay(1000000);

    }

}
