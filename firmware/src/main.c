//  ***************************************************************************
/// @file    main.c
/// @author  NeoProg
//  ***************************************************************************
#include "project_base.h"
#include "systimer.h"
#include "adc.h"

static void system_init(void);

// 0 - Left Bottom
// 1 - Right Bottom
// 2 - Right top
// 3 - Left top
// 4 - VIN

// 861 -- base line
// 0 - -66
// 1 - -270
// 2 - 203
// 3 - 131


static float ch[4] = {0};


/// ***************************************************************************
/// @brief  Program entry point
/// @param  none
/// @return none
/// ***************************************************************************
int main() {
    system_init();
    systimer_init();
    
    adc_init();
    adc_start();
    delay_ms(100);
    
    ch[0] = adc_read(0) + -66;
    ch[1] = adc_read(1) + -270;
    ch[2] = adc_read(2) + 203;
    ch[3] = adc_read(3) + 131;
    
    gpio_reset(GPIOA, 0);
    gpio_set_mode(GPIOA, 0, GPIO_MODE_INPUT);
    gpio_set_pull(GPIOA, 0, GPIO_PULL_NO);
    gpio_reset(GPIOA, 1);
    gpio_set_mode(GPIOA, 1, GPIO_MODE_INPUT);
    gpio_set_pull(GPIOA, 1, GPIO_PULL_NO);
    gpio_reset(GPIOA, 2);
    gpio_set_mode(GPIOA, 2, GPIO_MODE_INPUT);
    gpio_set_pull(GPIOA, 2, GPIO_PULL_NO);
    gpio_reset(GPIOA, 3);
    gpio_set_mode(GPIOA, 3, GPIO_MODE_INPUT);
    gpio_set_pull(GPIOA, 3, GPIO_PULL_NO);
    
    
    gpio_reset(GPIOB, 1);
    gpio_set_mode(GPIOB, 1, GPIO_MODE_OUTPUT);
    gpio_set_output_type(GPIOB, 1, GPIO_TYPE_PUSH_PULL);
    
    gpio_reset(GPIOA, 7);
    gpio_set_mode(GPIOA, 7, GPIO_MODE_OUTPUT);
    gpio_set_output_type(GPIOA, 7, GPIO_TYPE_PUSH_PULL);
    
    gpio_reset(GPIOA, 6);
    gpio_set_mode(GPIOA, 6, GPIO_MODE_OUTPUT);
    gpio_set_output_type(GPIOA, 6, GPIO_TYPE_PUSH_PULL);
    
    gpio_reset(GPIOA, 5);
    gpio_set_mode(GPIOA, 5, GPIO_MODE_OUTPUT);
    gpio_set_output_type(GPIOA, 5, GPIO_TYPE_PUSH_PULL);
    

    while (true) {
        
        ch[0] = ch[0] * 0.99f + (adc_read(0) + -66 ) * 0.01f;
        ch[1] = ch[1] * 0.99f + (adc_read(1) + -270) * 0.01f;
        ch[2] = ch[2] * 0.99f + (adc_read(2) + 203 ) * 0.01f;
        ch[3] = ch[3] * 0.99f + (adc_read(3) + 131 ) * 0.01f;
 
        
        int32_t acc_top = roundf(ch[2] + ch[3]);
        int32_t acc_bottom = roundf(ch[0] + ch[1]);
        int32_t diff = acc_top - acc_bottom;
        if (abs(diff) > 100) {
            if (diff > 0) {
                gpio_reset(GPIOB, 1); // M1
                gpio_set(GPIOA, 7);   // M1
            } else {
                gpio_set(GPIOB, 1);   // M1
                gpio_reset(GPIOA, 7); // M1
            }
        } else {
            gpio_reset(GPIOB, 1); // M1
            gpio_reset(GPIOA, 7); // M1
        }
        
        
        
        int32_t acc_left = roundf(ch[0] + ch[3]);
        int32_t acc_right = roundf(ch[1] + ch[2]);
        diff = acc_left - acc_right;
        if (abs(diff) > 100) {
            if (diff > 0) {
                gpio_set(GPIOA, 6);   // M2
                gpio_reset(GPIOA, 5); // M2
            } else {
                gpio_reset(GPIOA, 6); // M2
                gpio_set(GPIOA, 5);   // M2
            }
        } else {
            gpio_reset(GPIOA, 6); // M2
            gpio_reset(GPIOA, 5); // M2
        }
        
        
        /*diff = adc_read(2) - adc_read(3);
        if (abs(diff) > 400) {
            if (diff > 0) {
                gpio_set(GPIOA, 6);   // M2
                gpio_reset(GPIOA, 5); // M2
            } else {
                gpio_reset(GPIOA, 6); // M2
                gpio_set(GPIOA, 5);   // M2
            }
        } else {
            gpio_reset(GPIOA, 6); // M2
            gpio_reset(GPIOA, 5); // M2
        }*/
        
        /*diff = ch(0) - ch(1);
        if (abs(diff) > 100) {
            if (diff > 0) {
                gpio_set(GPIOA, 6);   // M2
                gpio_reset(GPIOA, 5); // M2
            } else {
                gpio_reset(GPIOA, 6); // M2
                gpio_set(GPIOA, 5);   // M2
            }
        } else {
            gpio_reset(GPIOA, 6); // M2
            gpio_reset(GPIOA, 5); // M2
        }*/
        
        
        
            
            
        
        
        //gpio_reset(GPIOA, 6); // M2
            //gpio_reset(GPIOA, 5); // M2
        
        
        
        /*delay_ms(100);
        
        gpio_set(GPIOB, 1);   // M1
        gpio_reset(GPIOA, 7); // M1
        gpio_set(GPIOA, 6);   // M2
        gpio_reset(GPIOA, 5); // M2
        delay_ms(10000);
        
        gpio_reset(GPIOB, 1); // M1
        gpio_reset(GPIOA, 7); // M1
        gpio_reset(GPIOA, 6); // M2
        gpio_reset(GPIOA, 5); // M2
        delay_ms(100);
        
        gpio_reset(GPIOB, 1); // M1
        gpio_set(GPIOA, 7);   // M1
        gpio_reset(GPIOA, 6); // M2
        gpio_set(GPIOA, 5);   // M2
        delay_ms(10000);
        
        asm("nop");*/
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
    RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN;
    
    // Enable TIM14 clocks
    //RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;
    
    // Enable ADC clocks
    RCC->APB2ENR |= RCC_APB2ENR_ADCEN;
}
