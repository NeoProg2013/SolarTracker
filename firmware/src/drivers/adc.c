/// ***************************************************************************
/// @file    adc.c
/// @author  NeoProg
/// ***************************************************************************
#include "adc.h"
#include "project_base.h"
#include "systimer.h"
#define ADC_CHANNEL_0_PIN                 GPIOA, 0
#define ADC_CHANNEL_1_PIN                 GPIOA, 1
#define ADC_CHANNEL_2_PIN                 GPIOA, 2
#define ADC_CHANNEL_3_PIN                 GPIOA, 3
#define ADC_CHANNEL_4_PIN                 GPIOA, 4

static uint32_t adc_data[6] = {0};
static uint32_t adc_ch = 0;


/// ***************************************************************************
/// @brief  ADC initialization
/// ***************************************************************************
void adc_init(void) {
    gpio_set_mode        (ADC_CHANNEL_0_PIN, GPIO_MODE_ANALOG);
    gpio_set_output_speed(ADC_CHANNEL_0_PIN, GPIO_SPEED_HIGH);
    gpio_set_pull        (ADC_CHANNEL_0_PIN, GPIO_PULL_NO);
    
    gpio_set_mode        (ADC_CHANNEL_1_PIN, GPIO_MODE_ANALOG);
    gpio_set_output_speed(ADC_CHANNEL_1_PIN, GPIO_SPEED_HIGH);
    gpio_set_pull        (ADC_CHANNEL_1_PIN, GPIO_PULL_NO);
    
    gpio_set_mode        (ADC_CHANNEL_2_PIN, GPIO_MODE_ANALOG);
    gpio_set_output_speed(ADC_CHANNEL_2_PIN, GPIO_SPEED_HIGH);
    gpio_set_pull        (ADC_CHANNEL_2_PIN, GPIO_PULL_NO);

    gpio_set_mode        (ADC_CHANNEL_3_PIN, GPIO_MODE_ANALOG);
    gpio_set_output_speed(ADC_CHANNEL_3_PIN, GPIO_SPEED_HIGH);
    gpio_set_pull        (ADC_CHANNEL_3_PIN, GPIO_PULL_NO);
    
    gpio_set_mode        (ADC_CHANNEL_4_PIN, GPIO_MODE_ANALOG);
    gpio_set_output_speed(ADC_CHANNEL_4_PIN, GPIO_SPEED_HIGH);
    gpio_set_pull        (ADC_CHANNEL_4_PIN, GPIO_PULL_NO);

    
    // Reset ADC resgisters
    RCC->APB2RSTR |= RCC_APB2RSTR_ADCRST;
    RCC->APB2RSTR &= ~RCC_APB2RSTR_ADCRST;
    
    // ADC calibration
    ADC1->CR |= ADC_CR_ADCAL;
    while (ADC1->CR & ADC_CR_ADCAL);
    
    // Setup ADC
    ADC1->IER = ADC_IER_EOCIE | ADC_IER_EOSEQIE;
    ADC1->CFGR1 = ADC_CFGR1_CONT;
    ADC1->CFGR2 = ADC_CFGR2_CKMODE_1; // PCLK/4 (Synchronous clock mode)
    ADC1->SMPR = ADC_SMPR_SMP_2 | ADC_SMPR_SMP_1 | ADC_SMPR_SMP_0; // 239.5 ADC clock cycles
    ADC1->CHSELR = ADC_CHSELR_CHSEL4 | ADC_CHSELR_CHSEL3 | ADC_CHSELR_CHSEL2 | ADC_CHSELR_CHSEL1 | ADC_CHSELR_CHSEL0;
    NVIC_EnableIRQ(ADC1_IRQn);
    NVIC_SetPriority(ADC1_IRQn, ADC_IRQ_PRIORITY);
                   
    // Enable ADC
    ADC1->CR |= ADC_CR_ADEN;
    while ((ADC1->ISR & ADC_ISR_ADRDY) == 0);
  
    // Delay for ADC stabilization time
    delay_ms(10);
}

/// ***************************************************************************
/// @brief  Start conversion
/// ***************************************************************************
void adc_start(void) {
    ADC1->CR |= ADC_CR_ADSTART;
}

/// ***************************************************************************
/// @brief  Get conversion result
/// @param  channel: channel index
/// @return conversion result
/// ***************************************************************************
uint32_t adc_read(uint32_t ch) {
    return adc_data[ch];
}





/// ***************************************************************************
/// @brief  ADC1 ISR
/// ***************************************************************************
#pragma call_graph_root="interrupt"
void ADC1_IRQHandler(void) {
    uint32_t status = ADC1->ISR;
    if (status & ADC_ISR_EOC) {
        adc_data[adc_ch++] = ADC1->DR;
    }
    if (status & ADC_ISR_EOSEQ) {
        adc_ch = 0;
    }
    ADC1->ISR |= ADC_ISR_EOSEQ | ADC_ISR_EOC | ADC_ISR_OVR;
}
