

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
#include "send_float.h"



#define WIDTH 12.00                //distance between the two wheels
#define CIRCUM 8.00                //circumference of wheel
#define PPR 400.00                 //pulses per revoluton
#define L(x) ((x*CIRCUM)/PPR)     //expression for distance covered by wheel




float lL=0,lR=0,dtheta=0,theta=0,disp=0,x[400],y[400];
uint32_t store_ptr=0,read_ptr=0,send_ptr=0;
uint32_t timestamp[400];
encoder_parameters wh1,wh2;
bool state1;

int j[3]={1,1,247};
int i;
char a;
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
    if(store_ptr>300 )
    {
    store_ptr=0;
    }
    QEIPositionSet(QEI1_BASE,97);
    QEIPositionSet(QEI0_BASE,45);
   // GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,0xFF);


   //GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,0xFF);
    TimerIntClear(TIMER5_BASE,TIMER_TIMA_TIMEOUT);

}
void Uart_ISR(void)
{


//a=UARTCharGetNonBlocking(UART5_BASE);

//UARTCharPut(UART0_BASE,a);
    if(UARTCharGetNonBlocking(UART0_BASE)=='0')
    {

        while(send_ptr!=read_ptr)
        {

            send_float(x[send_ptr]);
            send_float(y[send_ptr]);

            send_ptr++;
        }
        //for(i=0;i<3;i++)
        //UARTCharPutNonBlocking(UART5_BASE,j[i]);





    }


}
int main(void)

      {

    encoder_init();
    uart_init();
    Timer_init();

    while(1){


   //GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,0x00);
          if(read_ptr != store_ptr)
        {

       lL = L(wh1.pos[read_ptr]);
                  lR = L(wh2.pos[read_ptr]);
                  dtheta = (lL-lR)/WIDTH;
                  theta = theta + dtheta; // update of theta to calculate the x and y displacement
                  disp=(lL+lR)/2 ;
                  x=x+(disp*sin(theta));
                  y=y+(disp*cos(theta));
                  read_ptr++;
                  if(read_ptr>100)
                  {
                   read_ptr=0;
                  }


        }


    }


}
