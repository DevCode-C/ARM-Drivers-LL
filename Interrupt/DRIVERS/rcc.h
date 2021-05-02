#ifndef RCC_H
#define RCC_H

#include "registers.h"

#define RCC_GPIOA       17U
#define RCC_GPIOB       18U
#define RCC_GPIOC       19U
#define RCC_GPIOD       20U
#define RCC_GPIOE       21U
#define RCC_GPIOF       22U

#define RCC_SYSCFG_ENA      0U

#define RCC_GPIOx_enable(RCC_GPIOx)     (RCC->AHBENR|= (1<<RCC_GPIOx))
#define RCC_GPIOx_disable(RCC_GPIOx)    (RCC->AHBENR&= (0<<RCC_GPIOx))

#define RCC_SYSCFG()                    (RCC->APB2ENR|= (1<<RCC_SYSCFG_ENA))

/*
#define RCC_GPIOA_enable(X)  (RCC_BASE + (1<<X))
#define RCC_GPIOB_enable(X)  (RCC_BASE + (uint32_t)0x40000)
#define RCC_GPIOC_enable(X)  (RCC_BASE + (uint32_t)0x80000)
#define RCC_GPIOD_enable(X)  (RCC_BASE + (uint32_t)0x100000)
#define RCC_GPIOE_enable(X)  (RCC_BASE + (uint32_t)0x200000)
#define RCC_GPIOF_enable(X)  (RCC_BASE + (uint32_t)0x400000)
//#define RCC_GPIOA_enable2() (RCC_BASE + (1<<17))
*/
#endif