#include "stm32f10x_spi.h"
#include "stm32f10x.h"
#include "ads1220_SPI_Init.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "core_cm3.h"
#include <stm32f10x_usart.h>
#include "UART_Init.h"



void SPIx_Init()
{
	// Initialization struct
    SPI_InitTypeDef SPI_InitStruct;
    GPIO_InitTypeDef GPIO_InitStruct;

    // Step 1: Initialize SPI
    RCC_APB2PeriphClockCmd(SPIx_RCC, ENABLE);
    SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
    SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;         // CPH1=1 Second Edge on the SCK pin is the MSBit capture strobe
    SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;           //CPOL=0 low level idle state on SCK pin CPOL=1 High level idle state on SCK pin
    SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
    //SPI_InitStruct.SPI_NSS = SPI_NSS_Soft | SPI_NSSInternalSoft_Set;
    SPI_Init(SPIx, &SPI_InitStruct); // Initializes the SPIx peripheral according to the specified parameters in the SPI_InitStruct.
    SPI_Cmd(SPIx, ENABLE); // Enables SPIx peripheral.

    // Step 2: Initialize GPIO
    RCC_APB2PeriphClockCmd(SPI_GPIO_RCC, ENABLE);

    // GPIO pins for MOSI, and SCK
    GPIO_InitStruct.GPIO_Pin = SPI_PIN_MOSI | SPI_PIN_SCK;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(SPI_GPIO, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = SPI_PIN_MISO;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(SPI_GPIO, &GPIO_InitStruct);

    // GPIO pin for SS
//    GPIO_InitStruct.GPIO_Pin = SPI_PIN_SS;
//    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
//    GPIO_Init(SPI_GPIO, &GPIO_InitStruct);

    //GPIO pin for nDRDY
    GPIO_InitStruct.GPIO_Pin = ADS1220_nDRDY;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);


    }

void SPIx_Transfer(uint8_t data)
    {

    // Write data to be transmitted to the SPI data register
	  SPIx->DR = data;
	send_char('t');
    // Wait until transmit complete
    while (!(SPIx->SR & (SPI_I2S_FLAG_TXE)));
    send_char('r');
    // Wait until receive complete
    while (!(SPIx->SR & (SPI_I2S_FLAG_RXNE)));
    send_char('b');
    // Wait until SPI is not busy anymore
    while (SPIx->SR & (SPI_I2S_FLAG_BSY));

    }

uint8_t SPIx_Receive(uint8_t data)
      {

      // Write data to be transmitted to the SPI data register
  	  SPIx->DR = data;
  	 send_char('T');
      // Wait until transmit complete
      while (!(SPIx->SR & (SPI_I2S_FLAG_TXE)));
      send_char('R');
      // Wait until receive complete
      while (!(SPIx->SR & (SPI_I2S_FLAG_RXNE)));
      send_char('B');
      send_char('\t');
      // Wait until SPI is not busy anymore
      while (SPIx->SR & (SPI_I2S_FLAG_BSY));
      //Return received data from SPI data register

      return SPIx->DR;

      }
