/*
 * test2.c
 *
 *  Created on: 06-Jun-2019
 *      Author: mayuresh
 */




/*
 * timer_init.c
 *
 *  Created on: 05-Jun-2019
 *      Author: mayuresh
 */
//#include "timer_init.h"
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
#include "driverlib/pin_map.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
uint32_t k;
void storage_buffer(){
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,0xFF);
    SysCtlDelay(1000000);
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3,0x00);
    SysCtlDelay(1000000);

    }
int main(){
    SysCtlClockSet(SYSCTL_SYSDIV_50|SYSCTL_USE_PLL|SYSCTL_XTAL_1MHZ|SYSCTL_OSC_MAIN);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    //GPIOIntTypeSet(ui32Port,uint8_t ui8Pins,uint32_t ui32IntType);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3);

    TimerDisable(TIMER3_BASE,TIMER_A);
    TimerConfigure(TIMER3_BASE,TIMER_CFG_PERIODIC_UP);
    //TimerControlEvent(TIMER0_BASE,TIMER_A,TIMER_EVENT_BOTH_EDGES);
    TimerControlStall(TIMER3_BASE,TIMER_A,true);        //for running while debuging.
                                                                                //...will be removed once code is finalized

    IntMasterEnable();
    TimerIntEnable(TIMER3_BASE,TIMER_TIMA_TIMEOUT);        //what in case of interrupt when full width timer

    TimerIntRegister(TIMER3_BASE,TIMER_A,storage_buffer);
    TimerLoadSet(TIMER3_BASE,TIMER_A,65536);//what is load value of timer
    //calling interrupt after 12.5ms---->x=16*12500=200000
    //how to enable timer interrupt
    IntEnable(INT_TIMER3A);
    //IntEnable(INT_TIMER3B);
    TimerEnable(TIMER3_BASE, TIMER_A);
    k=SysCtlClockGet();
    while(1){
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 ,0xFF);
        SysCtlDelay(10000);
        GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1 ,0x00);
        SysCtlDelay(10000);


    }
}


