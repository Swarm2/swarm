

/**
 * main.c
 */

#include "stdio.h"
#include "math.h"
# include "stdlib.h"
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
#include "driverlib/qei.h"
#include "driverlib/uart.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "encoder_init.h"
#include "timer_init.h"
#include "uart_init.h"



#define WIDTH 12.00                //distance between the two wheels
#define CIRCUM 8.00                //circumference of wheel
#define PPR 400.00                 //pulses per revoluton
#define L(x) ((x*CIRCUM)/PPR)     //expression for distance covered by wheel




float lL=0,lR=0,dtheta=0,theta=0,disp=0,x[400],y[400];
uint32_t store_ptr=0,read_ptr=0,send_ptr=0;
uint32_t timestamp[100];
encoder_parameters wh1,wh2;
bool state1;
char s[100];
void Tim_ISR(void)
{


    wh1.pos[store_ptr]=QEIPositionGet(QEI0_BASE);
    wh2.pos[store_ptr]=QEIPositionGet(QEI1_BASE);
    wh1.direction[store_ptr]=QEIDirectionGet(QEI0_BASE);
    wh2.direction[store_ptr]=QEIDirectionGet(QEI1_BASE);
    wh1.velocity[store_ptr]=QEIVelocityGet(QEI0_BASE);
    wh2.velocity[store_ptr]=QEIVelocityGet(QEI1_BASE);
    state1=1;
    timestamp[store_ptr]=12500*(store_ptr+1);
    store_ptr++;
   /* if(store_ptr>300 )
    {
    store_ptr=0;
    }*/
    QEIPositionSet(QEI1_BASE,97);
    QEIPositionSet(QEI0_BASE,97);
    GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,0xFF);


   // GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,0xFF);
    TimerIntClear(TIMER3_BASE,TIMER_TIMA_TIMEOUT);

}
void Uart_ISR(void)
{
    if(UARTCharGetNonBlocking(UART0_BASE)=='0')
    {

      /* while(send_ptr<read_ptr)
       {
           //sprintf(s,"%f",x[send_ptr]);
           UARTCharPut(UART0_BASE,x[send_ptr]);
           send_ptr++;
       }*/

    }

}
int main(void)

{

    encoder_init();
    uart_init();
    Timer_init();

    while(1){

       /* while(state1)
        {
            read_ptr++;
        }*/
       //lL = (wh1.pos[2]);

        //lR = L(wh2.pos[store_ptr]);
   //GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,0x00);
        if(read_ptr!=store_ptr)
        {


        lL = L(wh1.pos[read_ptr]);
              lR = L(wh2.pos[read_ptr]);
              //Serial.println(lL);
              dtheta = (lL-lR)/(2*WIDTH);
              theta = theta + dtheta; // update of theta to calculate the x and y displacement

                if(!((abs(lL)>abs(lR))^(dtheta>0)))
                {
                  disp= -abs(lL+lR)/2;    // only magnitude of displacement of center of bot
                }
                else
                {
                  disp= abs(lL+lR)/2;
                }

              if(theta>6.28)              //reset the theta
               {
                theta = theta- 6.28;
                }
                else if(theta<(-6.28)){
                  theta = theta + 6.28;
                  }
              x[read_ptr]=x[read_ptr-1]+(disp*sin(theta));
              y[read_ptr]=y[read_ptr-1]+(disp*cos(theta));
              read_ptr++;
              if(read_ptr>300)
              {
               read_ptr=0;
              }




        }


    }


}
