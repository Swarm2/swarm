/*
 * encoder.c
 *
 *  Created on: 01-Jun-2019
 *      Author: Mayuresh
 */
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/qei.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
//#include "utils/uartstdio.h"

uint32_t p=0,v=0;
int32_t d=0,i=0;
char k[1000];
int main()
{
        /*SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
        //SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
        GPIOPinConfigure(GPIO_PB0_U1RX);
        GPIOPinConfigure(GPIO_PB1_U1TX);
        GPIOPinTypeUART(GPIO_PORTB_BASE,GPIO_PIN_0 | GPIO_PIN_1);
       //UARTEnable(UART0_BASE);
        UARTConfigSetExpClk(UART1_BASE,SysCtlClockGet(), 9600,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
        */
    //GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
   // SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);


    //HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY; //In Tiva include this is the same as "_DD" in older versions (0x4C4F434B)
     //      HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= 0x80;
     // HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0;

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinConfigure(GPIO_PC5_PHA1);
    GPIOPinConfigure(GPIO_PC6_PHB1);
    GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART0_BASE,SysCtlClockGet(), 9600,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));


   // GPIOPinConfigure(GPIO_PF4_IDX0);
    GPIOPinTypeQEI( GPIO_PORTC_BASE, GPIO_PIN_5 | GPIO_PIN_6);
   // GPIOPinTypeQEI( GPIO_PORTF_BASE, GPIO_PIN_4);
    QEIDisable(QEI1_BASE);
    //QEIIntDisable(QEI0_BASE,QEI_INTERROR | QEI_INTDIR | QEI_INTTIMER | QEI_INTINDEX);
    QEIConfigure(QEI1_BASE,QEI_CONFIG_CAPTURE_A_B |QEI_CONFIG_NO_RESET|QEI_CONFIG_QUADRATURE |QEI_CONFIG_NO_SWAP,799);
    QEIEnable(QEI1_BASE);
   // QEIVelocityEnable(QEI0_BASE);
   // QEIVelocityConfigure(QEI0_BASE,QEI_VELDIV_1,10);
    QEIPositionSet(QEI1_BASE,100);

    while(1){


        k[i]=QEIPositionGet(QEI1_BASE);
        SysCtlDelay(1000);
        i++;
       if(i==1000)
        break;

        /* if(k!=t)
        UARTCharPutNonBlocking(UART1_BASE,k);
        t=k;
    }*/
    /*while(1)
    {
    p=QEIPositionGet(QEI0_BASE);
   // sprintf(t,"%d",p);
    UARTCharPutNonBlocking(UART0_BASE,t[0]);
    while(t[i]!='\0')
    {
    UARTCharPutNonBlocking(UART0_BASE,t[i]);
    i++;
    }

    d=QEIDirectionGet(QEI0_BASE);
    //v=QEIVelocityGet(QEI0_BASE);
    }*/
    }
        return 0;
}

