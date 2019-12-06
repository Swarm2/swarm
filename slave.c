#include <stdint.h>
#include <stdbool.h>
//#include "Tiva_i2c.h"
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"






void slaveinitI2C0(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1);

    //reset I2C module
    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C1);

    //enable GPIO peripheral that contains I2C
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    // Configure the pin muxing for I2C0 functions on port B2 and B3.
    GPIOPinConfigure(GPIO_PA6_I2C1SCL);
    GPIOPinConfigure(GPIO_PA7_I2C1SDA);

    // Select the I2C function for these pins.
    GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6);
    GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_7);
    I2CSlaveAddressSet(I2C1_BASE, 1, 0b0000001);
   // I2CSlaveEnable(I2C1_BASE);
    // Enable and initialize the I2C0 master module.  Use the system clock for
    // the I2C0 module.  The last parameter sets the I2C data transfer rate.
    // If false the data rate is set to 100kbps and if true the data rate will
    // be set to 400kbps.
    //(I2C0_BASE, 0, 0b0000001);
    I2CSlaveInit(I2C1_BASE, 0b1000000);
    //I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);

    //clear I2C FIFOs
    HWREG(I2C1_BASE + I2C_O_FIFOCTL) = 80008000;
}
uint32_t p[100];
int i=0;

int main()
{

       SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
       GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_2);
       slaveinitI2C0();
    while(1)
    {
//        p=I2CSlaveStatus(I2C1_BASE);


        if(I2CSlaveStatus(I2C1_BASE)!=I2C_SLAVE_ACT_NONE)
        {
           p[i++]=I2CSlaveDataGet(I2C1_BASE);

        }
//        {
//            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0xFF);
//        }

//        if(I2CSlaveStatus(I2C1_BASE)==I2C_SLAVE_ACT_RREQ)
//        {
//            I2CSlaveACKOverride(I2C1_BASE, true);
//            I2CSlaveACKValueSet(I2C1_BASE, true);
//
//            if((I2CSlaveDataGet(I2C1_BASE)=='k'))
//                {
//                    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0xFF);
//                }
//        }
    }

}
