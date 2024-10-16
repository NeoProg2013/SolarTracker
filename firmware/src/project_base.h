//  ***************************************************************************
/// @file    project_base.c
/// @author  NeoProg
/// @brief   Contain basic information and declarations. Should be include to all project files
//  ***************************************************************************
#ifndef _PROJECT_BASE_H_
#define _PROJECT_BASE_H_
#include "stm32f0xx.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <math.h>


#define SYSTEM_CLOCK_FREQUENCY              (8000000)
#define AHB_CLOCK_FREQUENCY                 (8000000)
#define APB1_CLOCK_FREQUENCY                (8000000)
#define APB2_CLOCK_FREQUENCY                (8000000)

#define ADC_IRQ_PRIORITY                    (0)



#define GPIO_MODE_INPUT                     (0x00)
#define GPIO_MODE_OUTPUT                    (0x01)
#define GPIO_MODE_AF                        (0x02)
#define GPIO_MODE_ANALOG                    (0x03)
static inline void gpio_set_mode(GPIO_TypeDef* port, uint32_t pin, uint32_t mode) {
    port->MODER &= ~(0x03u << (pin * 2u)); // Clear
    port->MODER |=  (mode  << (pin * 2u)); // Set
}

#define GPIO_TYPE_PUSH_PULL                 (0x00)
#define GPIO_TYPE_OPEN_DRAIN                (0x01)
static inline void gpio_set_output_type(GPIO_TypeDef* port, uint32_t pin, uint32_t type) {
    port->OTYPER &= ~(0x01u << (pin * 1u)); // Clear
    port->OTYPER |=  (type  << (pin * 1u)); // Set
}

#define GPIO_SPEED_LOW                      (0x00)
#define GPIO_SPEED_MEDIUM                   (0x01)
#define GPIO_SPEED_HIGH                     (0x01)
static inline void gpio_set_output_speed(GPIO_TypeDef* port, uint32_t pin, uint32_t speed) {
    port->OSPEEDR &= ~(0x03u << (pin * 2u)); // Clear
    port->OSPEEDR |=  (speed << (pin * 2u)); // Set
}

#define GPIO_PULL_NO                        (0x00)
#define GPIO_PULL_UP                        (0x01)
#define GPIO_PULL_DOWN                      (0x02)
static inline void gpio_set_pull(GPIO_TypeDef* port, uint32_t pin, uint32_t pull) {
    port->PUPDR &= ~(0x03u << (pin * 2u)); // Clear
    port->PUPDR |=  (pull  << (pin * 2u)); // Set
}

static inline void gpio_set_af(GPIO_TypeDef* port, uint32_t pin, uint32_t af) {
    if (pin < 8) {
        port->AFR[0] &= ~(0x0Fu << (pin * 4u)); // Clear
        port->AFR[0] |=  (af    << (pin * 4u)); // Set
    } else {
        port->AFR[1] &= ~(0x0Fu << (pin * 4u - 32u)); // Clear
        port->AFR[1] |=  (af    << (pin * 4u - 32u)); // Set
    }
}

static inline void gpio_set(GPIO_TypeDef* port, uint32_t pin)         { port->BSRR |= 0x01u << pin;        }
static inline void gpio_reset(GPIO_TypeDef* port, uint32_t pin)       { port->BRR  |= 0x01u << pin;        }
static inline void gpio_toggle(GPIO_TypeDef* port, uint32_t pin)      { port->ODR  ^= 0x01u << pin;        }
static inline bool gpio_read_input(GPIO_TypeDef* port, uint32_t pin)  { return port->IDR & (0x01u << pin); }
static inline bool gpio_read_output(GPIO_TypeDef* port, uint32_t pin) { return port->ODR & (0x01u << pin); }


static inline void constrain_u16(uint16_t* v, uint16_t min, uint16_t max) {
    if (*v < min) *v = min;
    if (*v > max) *v = max;
}
static inline void constrain_float(float* v, float min, float max) {
    if (isless(*v, min)) *v = min;
    if (isgreater(*v, max)) *v = max;
}


static inline uint16_t make16(uint8_t high, uint8_t low) {
    uint16_t u16h = high;
    uint16_t u16l = low;
    return ((u16h << 8) & 0xFF00) | ((u16l << 0) & 0x00FF);
}

#endif // _PROJECT_BASE_H_
