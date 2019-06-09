

/**
 * main.c
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
#include "driverlib/qei.h"
#include "driverlib/pin_map.h"
#include "encoder_init.h"
#include "timer_init.h"
//#include "uart_init.h"

uint32_t store_ptr;
uint32_t timestamp[100];

encoder_parameters wh1,wh2;

void Tim_ISR(void)
{


    wh1.pos[store_ptr]=QEIPositionGet(QEI0_BASE);
    wh2.pos[store_ptr]=QEIPositionGet(QEI1_BASE);
    wh1.direction[store_ptr]=QEIDirectionGet(QEI0_BASE);
    wh2.direction[store_ptr]=QEIDirectionGet(QEI1_BASE);
    wh1.velocity[store_ptr]=QEIVelocityGet(QEI0_BASE);
    wh2.velocity[store_ptr]=QEIVelocityGet(QEI1_BASE);
    timestamp[store_ptr]=12500*(store_ptr+1);
    store_ptr++;
    if(store_ptr>1000)
    store_ptr=0;
    QEIPositionSet(QEI1_BASE,0);
    QEIPositionSet(QEI0_BASE,0);

   // GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,0xFF);
    TimerIntClear(TIMER3_BASE,TIMER_TIMA_TIMEOUT);

}
int main(void)
{
    encoder_init();
    Timer_init();
    while(1){
   // GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,0x00);

    }

}
