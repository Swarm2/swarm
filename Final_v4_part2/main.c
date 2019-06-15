

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
#include "driverlib/uart.h"
#include "encoder_init.h"
//#include "timer_init.h"
#include "uart_init.h"
#include "get_cord.h"

uint32_t store_ptr=0;
uint32_t timestamp[100];

encoder_parameters wh1,wh2;
int l=0,n=0;
char j;
char B;
uint32_t *Tx,*Rx;
coordinate cord[400];

typedef struct {
    char identifier;
    int k[3];
}div_param;

div_param store[400];

int i=0,m=0;
/*void Tim_ISR(void)
{


    wh1.pos[store_ptr]=QEIPositionGet(QEI0_BASE);
    wh2.pos[store_ptr]=QEIPositionGet(QEI1_BASE);
    wh1.direction[store_ptr]=QEIDirectionGet(QEI0_BASE);
    wh2.direction[store_ptr]=QEIDirectionGet(QEI1_BASE);
    wh1.velocity[store_ptr]=QEIVelocityGet(QEI0_BASE);
    wh2.velocity[store_ptr]=QEIVelocityGet(QEI1_BASE);
    //timestamp[store_ptr]=12500*(store_ptr+1);
    store_ptr++;
    if(store_ptr>80)
    store_ptr=0;
    QEIPositionSet(QEI1_BASE,0);
    QEIPositionSet(QEI0_BASE,0);

   // GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_1,0xFF);
    TimerIntClear(TIMER3_BASE,TIMER_TIMA_TIMEOUT);

}*/
void Uart_ISR(void)
{
    static int i=0;
    uint32_t ui32Status;
        ui32Status = UARTIntStatus(UART5_BASE, true); //get interrupt status
        UARTIntClear(UART5_BASE, ui32Status); //clear the asserted interrupts
        while(UARTCharsAvail(UART5_BASE)) //loop while there are chars
        {
        //store[m].identifier=UARTCharGetNonBlocking(UART5_BASE);
        store[m].k[i]=UARTCharGetNonBlocking(UART5_BASE);
        i++;
        if(i==3)
        {
            i=0;
            m++;

        }

            if(m==400)
            {
                m=0;
            }

        }




    /*

    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART5_BASE, true); //get interrupt status
    UARTIntClear(UART5_BASE, ui32Status); //clear the asserted interrupts
    while(UARTCharsAvail(UART5_BASE)) //loop while there are chars
    {
    //store[m].identifier=UARTCharGetNonBlocking(UART5_BASE);
    store[m].k[0]=UARTCharGetNonBlocking(UART5_BASE);
    store[m].k[1]=UARTCharGetNonBlocking(UART5_BASE);
    store[m].k[2]=UARTCharGetNonBlocking(UART5_BASE);

    m++;
        if(m==400)
        {
            m=0;
        }

    }

       //UARTIntClear(UART5_BASE,UART_INT_RX );

*/


/*
   cord[m].x= get_cord();
   cord[m].y= get_cord();
    m++;
    if(m==400)
    {
        m=0;
    }
    UARTIntClear(UART5_BASE,UART_INT_RX | UART_INT_RT);
*/

  //get.k[i]=UARTCharGetNonBlockingNonBlocking(UART5_BASE);
 /* k[2] = k[0] % 255;
  while(k[0]>255)
  {
      k[0]=(k[0])/255;
      k[1]++;
  }

  for(i=0;i<3;i++)*/
    //UARTCharPutNonBlocking(UART0_BASE,a);
    //UARTCharPut(UART0_BASE,UARTCharGetNonBlocking(UART5_BASE));
   // a=UARTCharGetNonBlocking(UART5_BASE);
   // UARTCharPut(UART0_BASE,a);


}

void Uart0_ISR(void)
{
    while(UARTCharsAvail(UART0_BASE)){


   l=UARTCharGetNonBlocking(UART0_BASE);

    UARTCharPutNonBlocking(UART5_BASE,l);
    }
    //UARTCharPut(UART0_BASE,UARTCharGetNonBlocking(UART5_BASE));
    //a=UARTCharGetNonBlocking(UART5_BASE);
   // UARTCharPut(UART0_BASE,a);


}


int main(void)
{
    //SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_XTAL_16MHZ | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN);
    //int h=SysCtlClockGet();
    encoder_init();
        uart_init();
        //Timer_init();
//UARTFIFOLevelGet(UART5_BASE, Tx, Rx);
        while(1){

            while(m==n);
            cord[n].x= get_cord(store[m]);
               cord[n].y= get_cord(store[m]);
                n++;
                if(n==400)
                {
                    n=0;
                }
        }







}
