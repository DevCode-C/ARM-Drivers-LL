#ifndef REGISTERS_H
#define REGISTERS_H
#include "types.h"

/*Definicion de las interrucpicones del sistema
  Interrupction definitions of system
*/
typedef enum{
    WWDG                            =   0,  //Window watchdog interrupt
    PVD_VDDIO2                      =   1,  //PVD and VDDIO2 supply comparator interrupt(combined EXTI lines 16 and 31)
    RTC                             =   2,  //RTC interrupts (combined EXTI lines 17, 19 and 20)
    FLASH                           =   3,  //Flash global interrupt
    RCC_CRS                         =   4,  //RCC and CRS global interrupts
    EXTI0_1                         =   5,  //EXTI Line[1:0] interrupts
    EXTI2_3                         =   6,  //EXTI Line[3:2] interrupts
    EXTI4_15                        =   7,  //EXTI Line[15:4] interrupts
    TSC                             =   8,  //Touch sensing interrupt
    DMA_CH1                         =   9,  //DMA channel 1 interrupt
    DMA_CH2_3_DMA2_CH1_2            =   10, //DMA channel 2 and 3 interrupts, DMA2 channel 1 and 2 interrupts
    DMA_CH4_5_6_7_DMA2_CH3_4_5      =   11, //DMA channel 4, 5, 6 and 7 interrupts, DMA2 channel 3, 4 and 5 interrupts
    ADC_COMP                        =   12, //ADC and COMP interrupts (ADC interrupt combined with EXTI lines 21 and 22)
    TIM1_BRK_UP_TRG_COM             =   13, //TIM1 break, update, trigger and commutation interrupt
    TIM1_CC                         =   14, //TIM1 capture compare interrupt
    TIM2                            =   15, //TIM2 global interrupt
    TIM3                            =   16, //TIM3 global interrupt
    TIM6_DAC                        =   17, //TIM6 global interrupt and DAC underrun interrupt
    TIM7                            =   18, //TIM7 global interrupt
    TIM14                           =   19, //TIM14 global interrupt
    TIM15                           =   20, //TIM15 global interrupt
    TIM16                           =   21, //TIM16 global interrupt
    TIM17                           =   22, //TIM17 global interrupt
    I2C1                            =   23, //I2C1 global interrupt (combined with EXTI line 23)
    I2C2                            =   24, //I2C2 global interrupt
    SPI1                            =   25, //SPI1 global interrupt
    SPI2                            =   26, //SPI2 global interrupt
    USART1_IRQ                      =   27, //USART1 global interrupt (combined with EXTI line 25)
    USART2_IRQ                      =   28, //USART2 global interrupt (combined with EXTI line 26)
    USART3_4_5_6_7_8                =   29, //USART3, USART4, USART5, USART6,USART7, USART8 global interrupt (combined with EXTI line 28)
    CEC_CAN                         =   30, //CEC and CAN global interrupts (combined with EXTI line 27)
    USB                             =   31, //USB global interrupt (combined with EXTI line 18)
}IRQ_types;



/*Definicion de las estructuras*/
typedef struct{
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint16_t BSRRL;
    volatile uint16_t BSRRH;
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

/**
* @brief NVIC Configurations Registers
*/
typedef struct{
    volatile uint32_t ISER;
    volatile uint32_t Reserved0[31];
    volatile uint32_t ICER;
    volatile uint32_t Reserved1[31];
    volatile uint32_t ISPR;
    volatile uint32_t Reserved2[31];
    volatile uint32_t ICPR;
    volatile uint32_t Reserved3[95];
    volatile uint32_t IPR[8];
}NVIC_Typedef;

/**
* @brief EXTI Configurations Registers
*/
typedef struct{
    volatile uint32_t IMR;      //Interrupt mask register
    volatile uint32_t EMR;      //Event mask register
    volatile uint32_t RTSR;     //Rising trigger selection register
    volatile uint32_t FTSR;     //Falling trigger selection register
    volatile uint32_t SWIER;    //Software interrupt event register
    volatile uint32_t PR;       //Pending register
}EXTI_TypeDef;


/**
* @brief System Configurations Registers
*/
typedef struct{
    volatile uint32_t CFGR1;        //SYSCFG configuration register 1
    volatile uint32_t Reserved0;    // Reserved
    volatile uint32_t EXTICR[4];    //SYSCFG external interrupt configuration register 
    volatile uint32_t CFGR2;        //SYSCFG configuration register 2
}SYSCFG_TypeDef;

/**
* @brief System Configurations Registers
*/
typedef struct{
    volatile uint32_t CR1;          //Control register 1
    volatile uint32_t CR2;          //Control register 2
    volatile uint32_t CR3;          //Control register 3 
    volatile uint32_t BRR;          //Baud rate register
    volatile uint32_t GTPR;         //Guard time and prescaler register
    volatile uint32_t RTOR;         //Receiver timeout register
    volatile uint32_t RQR;          //Request register
    volatile uint32_t ISR;          //Interrupt and status register
    volatile uint32_t ICR;          //Interrupt flag clear register
    volatile uint32_t RDR;          //Receive data register
    volatile uint32_t TDR;          //Transmit data register
}USART_TypeDef;


/*-------------------------------------------*/

/*Definiciones de las bases de direcciones */
#define _AHB2_BASE ((uint32_t)0x48000000U)
#define _AHB1_BASE ((uint32_t)0x40020000U)
#define _APB2_BASE ((uint32_t)0x40010000U)
#define _APB1_BASE ((uint32_t)0x40000000U)

#define PPS        ((uint32_t)0xE000E000U)

#define GPIOA_BASE  (_AHB2_BASE + 0x00000000U)
#define GPIOB_BASE  (_AHB2_BASE + 0x00000400U)
#define GPIOC_BASE  (_AHB2_BASE + 0x00000800U)
#define GPIOD_BASE  (_AHB2_BASE + 0x00000C00U)
#define GPIOE_BASE  (_AHB2_BASE + 0x00001000U)
#define GPIOF_BASE  (_AHB2_BASE + 0x00001400U)

#define RCC_BASE        (_AHB1_BASE + 0x00001000U)
#define NVIC_BASE       (PPS        + 0x100UL)
#define EXTI_BASE       (_APB2_BASE + 0x00000400U)
#define SYSCFG_BASE     (_APB2_BASE + 0x0U)
#define USART1_BASE     (_APB2_BASE + 0x3800UL)
#define USART2_BASE     (_APB1_BASE + 0x4400UL)
#define USART3_BASE     (_APB1_BASE + 0x4800UL)
#define USART4_BASE     (_APB1_BASE + 0x4C00UL)
/*--------------------------------------------------------*/

/*Definiciones de los registros inicializados en la direccion de memoria correspondiente*/
#define RCC         ((RCC_TypeDef*) RCC_BASE)

#define NVIC        ((NVIC_Typedef*  )     NVIC_BASE)
#define EXTI        ((EXTI_TypeDef*  )     EXTI_BASE)
#define SYSCFG      ((SYSCFG_TypeDef*)   SYSCFG_BASE)
#define USART1      ((USART_TypeDef* )   USART1_BASE)
#define USART2      ((USART_TypeDef* )   USART2_BASE)
#define USART3      ((USART_TypeDef* )   USART3_BASE)
#define USART4      ((USART_TypeDef* )   USART4_BASE)

#define GPIOA       ((GPIO_TypeDef*) GPIOA_BASE)//Registers
#define GPIOB       ((GPIO_TypeDef*) GPIOB_BASE)
#define GPIOC       ((GPIO_TypeDef*) GPIOC_BASE)
#define GPIOD       ((GPIO_TypeDef*) GPIOD_BASE)
#define GPIOE       ((GPIO_TypeDef*) GPIOE_BASE)
#define GPIOF       ((GPIO_TypeDef*) GPIOF_BASE)

#endif