/*
 * fr_api.c
 *
 *  Created on: 15-Jun-2019
 *      Author: Mayuresh
 */
#include "stdio.h"
#include "string.h"
# include "stdlib.h"
#include "stdint.h"
#include "stdbool.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_gpio.h"
#include "driverlib/uart.h"
#include "send_float.h"

#include "fr_api.h"


unsigned int s=0,r=0;






void fr_api(div_param info, char api ,int xbee)
{
    unsigned char dil=0x7E;
    unsigned int sum= 0x000E + 4;
    int len1=(((sum%16))+((sum/16)%16)*16);
    int len2=((((sum/256)%16))+((sum/4096)%16)*16);
    unsigned char fr_id= 0x01;
    unsigned char macid[8] = {0x00, 0x13, 0xA2, 0x00, 0x41, 0x63, 0xCB, 0xB1};
    if(xbee==2)
    {
   //  macid[5] = 0xDC;
    // macid[6] = 0x85;
     macid[7] = 0xAB;
    }
    unsigned char destadd[2];
     destadd[0]=0xFF;
     destadd[1]=0xFE;
    unsigned char br_rad= 0x00;
    unsigned char opt= 0x00;
    unsigned int datasum=0;
    unsigned char macsum =0;
   // char frame[400]={dil, len2, len1, api, fr_id};
   // char frame[400]={0x01};


    datasum=datasum+info.identifier;

    for( s=0;s<3;s++)
    {
        datasum= datasum+ info.data[s];
    }

    for( s=0;s<8;s++)
    {

        macsum= macsum+ macid[s];
    }

    unsigned int sum1=api + datasum+ fr_id + macsum + 0xFF + 0xFE + br_rad + opt;
    int checksum1=255-(((sum1%16))+((sum1/16)%16)*16);
    unsigned char checksum=checksum1;

    char frame[200]={dil, len2, len1, api, fr_id};


    int j=5;

    for( s=0;s<8;s++)
    {
  frame[j]=macid[s];
  j++;

    }

    frame[j]=destadd[0];
  frame[++j]=destadd[1];

    frame[++j]=br_rad;

    frame[++j]=opt;


    frame[++j]=info.identifier;
    j++;
    for( s=0;s<3;s++)
    {
    frame[j]=info.data[s];
    j++;
    }


    frame[j]=checksum;

   // char frame[23]= {0x7E, 0x00, 0x12,0x10,0x01,0x00,0x13,0xA2,0x00,0x41,0x63,0xCB,0xF7,0xFF,0xFE,0x00,0x00,0x23,0x2B,0x00,0x2B,0x5D};

    for (r=0;r<22;r++)
    {
        UARTCharPut(UART5_BASE,frame[r]);
    }


}

