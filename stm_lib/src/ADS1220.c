#include "stm32f10x.h"
#include "ads1220.h"
#include "ads1220_SPI_Init.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include "core_cm3.h"
#include "Delay_us.h"

           int GAIN = 4;
    	   float Vref =2.048;
           float Vout=0;
           float RTD = 0;
           float IDAC = 0.25;
           float temp = 0;
           uint8_t primen_MSB=0;
    	   uint8_t primen_Data=0;
    	   uint8_t primen_LSB=0;
    	   uint32_t bit24=0;        //24 bit vlaue from ADC
    	   uint32_t bit32=0;
    	   float Offset = 0;

void ADS1220_RESTART(){
	SPIx_Transfer(RESTART);
}

void ADS1220_Calibration_Setup(){
           int i=0;
    	   float Offset;
    	   SPIx_Transfer(0x43);   //WREG WRITE ALL 4 config regs
    	   SPIx_Transfer(0xE5);   //config_reg0 AINP and AINN shorted to (AVDD + AVSS) / 2, GAIN 4 PGA bypassed
    	   SPIx_Transfer(0x04);   //config_reg1 20 SPS, NORMAL MODE, SINGLE SHOT MODE, temp sensor diasable, Current source OFF
    	   SPIx_Transfer(0x24);   //config_reg2 Internal 2.048 V reference,50-Hz rejection,Switch is open, IDACs current 250 uA
    	   SPIx_Transfer(0xBA);   //config_reg3 IDAC1->REFP0, IDAC2->REFN0, nDRDY used to detect data ready

    	   Delay_Nus(50);               //Problem need timer start timer come back when finish
    	   SPIx_Transfer(START);	//Start Conversion

}
float ADS1220_Return_Offset(){
      	   
    	   Delay_Nus(100);              //Problem need timer start timer come back when finish
    	   primen_MSB =  SPIx_Receive(0x00);
    	   primen_Data = SPIx_Receive(0x00);
    	   primen_LSB =  SPIx_Receive(0x00);
    	   bit24 = primen_MSB;
    	   bit24 = (bit24 << 8) | primen_Data;
    	   bit24 = (bit24 << 8) | primen_LSB;
    	   bit32 = (bit24 << 8);
    	   bit32 = (bit32 >> 8);
    	   Offset = (float)((bit32 * Vref/GAIN * 1000) / (((long int)1<<23)-1) ); //In mV.  To make better substract offset for each reading
    	   return Offset;

    }

void ADS1220_PT1000_X_Setup(int x){
              
      SPIx_Transfer(0x43);//WREG
      if(x==1)SPIx_Transfer(0x05);//config_reg0 odbran AINO i AIN1, GAIN 4 PGA bypassed
      else SPIx_Transfer(0x55);//config_reg0 odbran AIN2 i AIN3, GAIN 4 PGA bypassed
      SPIx_Transfer(0x04);//config_reg1 20 SPS, NORMAL MODE, SINGLE SHOT MODE, temp sensor diasable, Current source OFF
      SPIx_Transfer(0x24);//config_reg2 Internal 2.048 V reference,50-Hz rejection,Switch is open, IDACs current 250 uA
      SPIx_Transfer(0xBA);//config_reg3 IDAC1->REFP0, IDAC2->REFN0, nDRDY merged with DOUT used to detect data ready

      Delay_Nus(50);
      SPIx_Transfer(START);	//START/SYNC
      }
     

float ADS1220_Return_Temp(float V_Off){
   	 Delay_Nus(100);
   	 primen_MSB = SPIx_Receive(0x00);
   	 primen_Data = SPIx_Receive(0x00);
   	 primen_LSB = SPIx_Receive(0x00);
   	 bit24 = primen_MSB;
   	 bit24 = (bit24 << 8) | primen_Data;
   	 bit24 = (bit24 << 8) | primen_LSB;
   	 bit32 = (bit24 << 8);
     bit32 = (bit32 >> 8);
     Vout = (float)((bit32 * Vref/GAIN * 1000) / (((long int)1<<23)-1) ); //In mV.  To make better substract offset for each reading
   	 Vout-=V_Off;
   	 RTD = Vout/IDAC ;
     temp = (RTD * (255.8723 + RTD * (9.6 + RTD * 0.878)));
     return temp;
   	 }
     
