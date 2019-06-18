/*
 * timer_init.c
 *
 *  Created on: 05-Jun-2019
 *      Author: Mayuresh
 */
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
//#include "inc/tm4c123gh6pm.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "timer_init.h"

void Tim_ISR (void);

void Timer_init(void)
{
        SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER5);

        TimerDisable(TIMER5_BASE,TIMER_BOTH);
        TimerConfigure(TIMER5_BASE,TIMER_CFG_PERIODIC_UP);
        TimerLoadSet(TIMER5_BASE,TIMER_BOTH,8000000);
       // TimerControlStall(TIMER3_BASE,TIMER_BOTH,true);
        IntEnable(INT_TIMER5A);
        TimerIntRegister(TIMER5_BASE,TIMER_BOTH,Tim_ISR);
        TimerIntEnable(TIMER5_BASE,TIMER_TIMA_TIMEOUT);
        IntMasterEnable();
       // GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2);
        TimerEnable(TIMER5_BASE,TIMER_BOTH);
}


