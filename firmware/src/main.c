//  ***************************************************************************
/// @file    main.c
/// @author  NeoProg
//  ***************************************************************************
#include "project_base.h"
#include "systimer.h"

static void system_init(void);



/// ***************************************************************************
/// @brief  Program entry point
/// @param  none
/// @return none
/// ***************************************************************************
int main() {
    system_init();
    systimer_init();
    
    delay_ms(1000);
    
    while (true) {
        
        asm("nop");
    }
}

void HardFault_Handler(void) {
    NVIC_SystemReset();
}

/// ***************************************************************************
/// @brief  System initialization
/// @param  none
/// @return none
/// ***************************************************************************
static void system_init(void) {
    // Enable Prefetch Buffer
    FLASH->ACR = FLASH_ACR_PRFTBE;
    
    /*// Enable HSE
    RCC->CR |= RCC_CR_HSEON;
    while ((RCC->CFGR & RCC_CR_HSERDY) == 0);
    
    // Configure PLL (clock source HSI/2 = 4MHz)
    RCC->CFGR |= RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL2;
    RCC->CR |= RCC_CR_PLLON;
    while ((RCC->CR & RCC_CR_PLLRDY) == 0);
    
    // Set FLASH latency
    FLASH->ACR |= FLASH_ACR_LATENCY;
    
    // Switch system clock to PLL
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS_PLL) == 0);*/

    // Enable GPIO clocks
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
    
    // Enable TIM14 clocks
    RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;
}
