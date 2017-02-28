#include "stm32f10x_spi.h"


#define SPI_PIN_MOSI  GPIO_Pin_7
#define SPI_PIN_MISO  GPIO_Pin_6
#define SPI_PIN_SCK   GPIO_Pin_5

#define RESTART 0x06                  //Send the RESET command (06h) to make sure the ADS1220 is properly reset after power-up

#define START 0x08                  //Send the START/SYNC command (08h) to start converting in continuous conversion mode
#define WREG  0x43                  //w

float ADS1220_Return_Offset();
void ADS1220_RESTART();
void ADS1220_Calibration_Setup();
float ADS1220_Return_Offset();
void ADS1220_PT1000_X_Setup(int x);
float ADS1220_Return_Temp(float V_Off);
