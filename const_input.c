

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
#include "driverlib/pwm.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"






float v,e1=0,  r , sum1=0;
float t=0.0001,k1=0.1,k2=0.1,d=0;
float    r = 80;
int v1 = 20;
int main()
{
    while(1)
    {
        e1=2;
        sum1 =sum1+e1;
        d=(k1*e1)+(k2*t*sum1);
        v = v1 + d;
        v1=v;

    }
}
