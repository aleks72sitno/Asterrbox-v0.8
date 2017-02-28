#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include "core_cm3.h"
#include "ADS1220.h"
#include "ads1220_SPI_Init.h"
#include <stm32f10x_usart.h>
#include "UART_Init.h"

int ADS1220_Calibrating = 0;
int ADS1220_Measuring = 0;
int ADS1220_Calibrating_Done = 0;

float temp = 0;
float temp_avg = 0;
int temp_measured = 0;
int pt;
int pt_count = 0;
float Vout_Offset = 0;
float Vout_Offset_dummy = 0; //first reading of the calibration offset is wrong
int offset_counter = 0;
float measure_counter = 0;
float pt1_temp = 0;
float pt2_temp = 0;
float pt1_temp_dummy = 0;
float pt2_temp_dummy = 0;
float pt1_temp_avg = 0;
float pt2_temp_avg = 0;


float tempc = 0;
float temp1 = 0;
float temp2 = 0;
float temp3 = 0;
float temp4 = 0;
float temp5 = 0;

unsigned char c;
unsigned char c1;
unsigned char c2;
unsigned char c3;
unsigned char c4;
unsigned char c5;
unsigned char c6;
unsigned int x1;
unsigned int x2;
unsigned int x3;
unsigned int x4;
unsigned int x5;
unsigned int x6;


int main(void)
{
uart_init();

SPIx_Init();


ADS1220_RESTART();

    while(1)
    {
    	if(ADS1220_Calibrating == 0 && ADS1220_Measuring == 0 && ADS1220_Calibrating_Done == 0){
    	   Delay_Nus(200);

    	   Delay_Nus(200);
    	   ADS1220_Calibration_Setup();
    	   ADS1220_Calibrating = 1;
    	   }
    	if( ADS1220_Measuring == 0 && ADS1220_Calibrating_Done == 1){
    	   if(pt_count < 9) pt=0;
    	   else pt=1;
    	   SPIx_Transfer(RESTART);
    	   ADS1220_PT1000_X_Setup(pt);
           ADS1220_Calibrating_Done = 0;
           ADS1220_Measuring = 1;
           pt_count++;
    	   }
    	if(ADS1220_Calibrating == 1 && GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6) == 0){
           if(offset_counter < 1) {
        	   Vout_Offset_dummy = ADS1220_Return_Offset();
               offset_counter++;
           }
           else { Vout_Offset = ADS1220_Return_Offset();
    	          ADS1220_Calibrating_Done = 1;
    	          ADS1220_Calibrating = 0;
    	          offset_counter = 0;
                }
           }
        if(ADS1220_Measuring == 1 && GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6) == 0){
            measure_counter++;
        	if(pt == 0){
        		if(measure_counter==1)pt1_temp_dummy = ADS1220_Return_Temp(Vout_Offset); //first reading is wrong
        		else   {
        			    pt1_temp = ADS1220_Return_Temp(Vout_Offset);
                        pt1_temp_avg += pt1_temp;

//                        if(measure_counter>21) pt1_temp_avg/=(measure_counter-1);
        		       }
        		}

           else if(pt == 1){
        	 pt2_temp_dummy = ADS1220_Return_Temp(Vout_Offset); //first reading is wrong
        	 pt2_temp = ADS1220_Return_Temp(Vout_Offset);
             pt2_temp_avg=+temp;
             }
            if(measure_counter>21){
            	if(pt == 0) {tempc=pt1_temp_avg/(measure_counter--);
           	 x1=tempc/10;
           	 c1=x1+'0';
           	 temp1=(tempc - (x1*10));
           	 x2=temp1;
           	 c2=x2+'0';
           	 temp2=(temp1 - x2)*10;
           	 x3=temp2;
           	 c3=x3+'0';
           	 temp3=(temp2 - x3)*10;
           	 x4=temp3;
           	 c4=x4+'0';
           	 temp4=(temp3 - x4)*10;
           	 x5=temp4;
           	 c5=x5+'0';
           	 temp5=(temp4 - x5)*10;
           	 x6=temp5;
           	 c6=x6+'0';

           	 c= pt_count + '0';
           	 send_char('\n');
           	 send_char('\n');
          	 send_char(c);
           	 send_char('\t');
           	 send_char(c1);
           	 send_char(c2);
           	 send_char('.');
           	 send_char(c3);
           	 send_char(c4);
           	 send_char(c5);
           	 send_char(c6);
           	 send_char('\n');
           	 ADS1220_Measuring = 0;
           	 measure_counter = 0;
           	 pt1_temp_avg = 0;
            	}
            	else {
//            	pt1_temp_avg = pt1_temp_avg/measure_counter;

            	ADS1220_Measuring = 0;
            	measure_counter = 0;
            	pt1_temp_avg = 0;
            	pt_count = 0;}
                }
            }
    }
}
