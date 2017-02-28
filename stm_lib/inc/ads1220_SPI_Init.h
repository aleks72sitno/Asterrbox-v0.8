#include "stm32f10x_spi.h"
//#include "ads1220.h"

#define SPIx_RCC      RCC_APB2Periph_SPI1
#define SPIx          SPI1
#define SPI_GPIO_RCC  RCC_APB2Periph_GPIOA
#define SPI_GPIO      GPIOA
#define SPI_PIN_MOSI  GPIO_Pin_7
#define SPI_PIN_MISO  GPIO_Pin_6
#define SPI_PIN_SCK   GPIO_Pin_5
#define SPI_PIN_SS    GPIO_Pin_4
#define ADS1220_nDRDY GPIO_Pin_8

void SPIx_Init();
void SPIx_Transfer(uint8_t data);
uint8_t SPIx_Receive(uint8_t data);

