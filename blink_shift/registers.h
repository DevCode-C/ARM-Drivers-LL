#ifndef REGISTERS_H
#define REGISTERS_H
#include "types.h"

/*Definicion de las estructuras*/
typedef struct{
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    //Prueba de separar el registro BSRR en BSRRL BSRRH
    volatile uint16_t BSRRL;
    // volatile uint32_t BSRR;
    volatile uint16_t BSRRH;
    //
    volatile uint32_t LCKR;
    volatile uint32_t AFRL;
    volatile uint32_t AFRH;
    volatile uint32_t BRR;
}GPIO_TypeDef;

typedef struct{
    volatile uint32_t CR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t APB1RSTR;
    volatile uint32_t AHBENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t APB1ENR;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
    volatile uint32_t AHBRSTR;
    volatile uint32_t CFGR2;
    volatile uint32_t CFGR3;
    volatile uint32_t CR2;

}RCC_TypeDef;
/*-------------------------------------------*/

/*Definiciones de las bases de direcciones */
#define _AHB2_BASE ((uint32_t)0x48000000U)
#define _AHB1_BASE ((uint32_t)0x40020000U)
#define _APB2_BASE ((uint32_t)0x40010000U)
#define _APB1_BASE ((uint32_t)0x40000000U)

#define GPIOA_BASE  (_AHB2_BASE + 0x00000000)
#define GPIOB_BASE  (_AHB2_BASE + 0x00000400)
#define GPIOC_BASE  (_AHB2_BASE + 0x00000800)
#define GPIOD_BASE  (_AHB2_BASE + 0x00000C00)
#define GPIOE_BASE  (_AHB2_BASE + 0x00001000)
#define GPIOF_BASE  (_AHB2_BASE + 0x00001400)

#define RCC_BASE    (_AHB1_BASE + 0x00001000)
/*--------------------------------------------------------*/

/*Definiciones de los registros inicializados en la direccion de memoria correspondiente*/
#define RCC         ((RCC_TypeDef*) RCC_BASE)

#define GPIOA       ((GPIO_TypeDef*) GPIOA_BASE)
#define GPIOB       ((GPIO_TypeDef*) GPIOB_BASE)
#define GPIOC       ((GPIO_TypeDef*) GPIOC_BASE)
#define GPIOD       ((GPIO_TypeDef*) GPIOD_BASE)
#define GPIOE       ((GPIO_TypeDef*) GPIOE_BASE)
#define GPIOF       ((GPIO_TypeDef*) GPIOF_BASE)


#endif