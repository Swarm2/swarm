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


void uart_init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART0_BASE,SysCtlClockGet(), 9600,(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    IntMasterEnable();
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
    IntRegister(INT_UART0,Uart_ISR);                             //ISR is a name of function used as interrupt handler
    UARTIntRegister(UART0_BASE, Uart_ISR);

}



