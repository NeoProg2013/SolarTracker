/// ***************************************************************************
/// @file    adc.h
/// @author  NeoProg
/// @brief   Interface for ADC driver
/// ***************************************************************************
#ifndef _ADC_H_
#define _ADC_H_
#include <stdint.h>
#include <stdbool.h>


extern void adc_init(void);
extern void adc_start(void);
extern uint32_t adc_read(uint32_t ch);


#endif // _ADC_H_

