/*
 * floatcov.c
 *
 *  Created on: 12-Jun-2019
 *      Author: Mayuresh
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
#include "driverlib/uart.h"
//#include "uart_init.h"
#include "send_float.h"
#include "fr_api.h"


div_param store[400];
int m=0;
int i;

void send_float(float w)
{
    if(w<0)
         {
             store[m].identifier='$';
             //store[m].data[0]
         }
    else{
        store[m].identifier='#';
    }

    store[m].data[1]=0;
    store[m].data[0]=(w*1000);

    store[m].data[2] = store[m].data[0] % 255;
    while(abs(store[m].data[0])>255)
    {
        store[m].data[0]=store[m].data[0]/255;
        store[m].data[1]++;
    }

    //for(i=0;i<3;i++)
    //UARTCharPutNonBlocdataing(UART5_BASE,store[m].data[i]);
    fr_api(store[m],0x10,2);

    m++;
    if(m>300){
        m=0;
    }

}
