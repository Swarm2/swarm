/*
 * encoder.c
 *
 *  Created on: 01-Jun-2019
 *      Author: Mayuresh
 */
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

uint32_t p=0,v=0;
int32_t d=0;
int main()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI0);
   // SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    GPIOPinConfigure(GPIO_PD6_PHA0);
    GPIOPinConfigure(GPIO_PD7_PHB0);
   // GPIOPinConfigure(GPIO_PF4_IDX0);
    GPIOPinTypeQEI( GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);
   // GPIOPinTypeQEI( GPIO_PORTF_BASE, GPIO_PIN_4);
    QEIConfigure(QEI0_BASE,QEI_CONFIG_CAPTURE_A_B |QEI_CONFIG_NO_RESET|QEI_CONFIG_QUADRATURE |QEI_CONFIG_NO_SWAP,799);
    QEIEnable(QEI0_BASE);
   // QEIVelocityEnable(QEI0_BASE);
   // QEIVelocityConfigure(QEI0_BASE,QEI_VELDIV_1,10);
    QEIPositionSet(QEI0_BASE,0);

    while(1)
    {
    p=QEIPositionGet(QEI0_BASE);

    d=QEIDirectionGet(QEI0_BASE);
    //v=QEIVelocityGet(QEI0_BASE);
    }

}

