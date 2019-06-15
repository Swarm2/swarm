/*
 * uart_init.c
 *
 *  Created on: 09-Jun-2019
 *      Author: Mayuresh
 */
/*
 * uart_init.c
 *
 *  Created on: 06-Jun-2019
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

void Uart_ISR(void);
void Uart0_ISR(void);




void uart_init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART5);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    GPIOPinConfigure(GPIO_PE4_U5RX);
    GPIOPinConfigure(GPIO_PE5_U5TX);
    GPIOPinTypeUART(GPIO_PORTE_BASE,GPIO_PIN_4 | GPIO_PIN_5);
    UARTConfigSetExpClk(UART5_BASE,SysCtlClockGet(), 115200,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    IntMasterEnable();
  UARTIntEnable(UART5_BASE, UART_INT_RX | UART_INT_RT);
  UARTFIFOEnable(UART5_BASE);
    IntRegister(INT_UART5,Uart_ISR);                             //ISR is a name of function used as interrupt handler
    UARTIntRegister(UART5_BASE, Uart_ISR);
    //UARTFIFOEnable(UART5_BASE);
   // UARTFIFOLevelSet(UART5_BASE,UART_FIFO_TX1_8, UART_FIFO_RX2_8);




    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART0_BASE,SysCtlClockGet(), 115200,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    IntMasterEnable();
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
    IntRegister(INT_UART0,Uart0_ISR);                             //ISR is a name of function used as interrupt handler
    UARTIntRegister(UART0_BASE, Uart0_ISR);

}
