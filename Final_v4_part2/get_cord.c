/*
 * get_cord.c
 *
 *  Created on: 13-Jun-2019
 *      Author: mayuresh
 */
#include "stdint.h"
#include "stdbool.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"

#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/uart.h"
#include "driverlib/pin_map.h"
//#include "uart_init.h"

float k;
int a;
char b;

typedef struct {
    char identifier;
    int k[3];
}div_param;

 float get_cord(div_param milja){
    //uart_init();


    //b = UARTCharGetNonBlocking(UART5_BASE);
    if(milja.identifier=='$'){
       // b = UARTCharGetNonBlocking(UART5_BASE);

        k=255*((milja.k[0]-256));
        a=milja.k[1];

        if(a){
                    while((a-1)>0){

                    k=k*255;
                    a--;
                }

                }
                else
                    k=0;
        //b = UARTCharGetNonBlocking(UART5_BASE);

        k=(k+(milja.k[2]-256))/1000;
    }
    else if(milja.identifier=='#')
    {
        k=255*(milja.k[0]);
        a=milja.k[1];
        if(a){
            while((a-1)>0){

            k=k*255;
            a--;
        }

        }
        else
            k=0;

       /* while((a-1)>0){
                    k=k*255;
                    a--;
                }
        if(a==0)
            k=(in)b;*/
        //b = milja.k[3]

        k=(k+milja.k[2])/1000;
    }

        return k;


}


