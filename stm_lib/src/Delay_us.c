#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "core_cm3.h"
#include "Delay_us.h"

void Delay_Nus(uint32_t micros) {

    	micros *= (SystemCoreClock / 1000000) / 5;
    	/* Wait till done */
    	while (micros--);
    }
    unsigned long msTicks;

    void SysTick_Handler()
    {
    	msTicks++;
    }

    void msInit()
    {
    	msTicks = 0;
    	// Update SystemCoreClock value
    	SystemCoreClockUpdate();
    	// Configure the SysTick timer to overflow every 1 ms
    	SysTick_Config(SystemCoreClock / 1000); //24bit tick counter
    }