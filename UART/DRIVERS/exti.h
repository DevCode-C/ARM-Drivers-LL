#ifndef EXTI_H
#define EXTI_H
#include "registers.h"
#include "types.h"

#define Reset_EXTI      (0xFUL)

#define EXTI_GPIO_Line0       ((uint8_t)0x0 )           //EXTI_GPIO line 0   GPIOx_IT
#define EXTI_GPIO_Line1       ((uint8_t)0x1 )           //EXTI_GPIO line 1   GPIOx_IT
#define EXTI_GPIO_Line2       ((uint8_t)0x2 )           //EXTI_GPIO line 2   GPIOx_IT
#define EXTI_GPIO_Line3       ((uint8_t)0x3 )           //EXTI_GPIO line 3   GPIOx_IT
#define EXTI_GPIO_Line4       ((uint8_t)0x4 )           //EXTI_GPIO line 4   GPIOx_IT
#define EXTI_GPIO_Line5       ((uint8_t)0x5 )           //EXTI_GPIO line 5   GPIOx_IT
#define EXTI_GPIO_Line6       ((uint8_t)0x6 )           //EXTI_GPIO line 6   GPIOx_IT
#define EXTI_GPIO_Line7       ((uint8_t)0x7 )           //EXTI_GPIO line 7   GPIOx_IT
#define EXTI_GPIO_Line8       ((uint8_t)0x8 )           //EXTI_GPIO line 8   GPIOx_IT
#define EXTI_GPIO_Line9       ((uint8_t)0x9 )           //EXTI_GPIO line 9   GPIOx_IT
#define EXTI_GPIO_Line10      ((uint8_t)0xA )           //EXTI_GPIO line 10  GPIOx_IT
#define EXTI_GPIO_Line11      ((uint8_t)0xB )           //EXTI_GPIO line 11  GPIOx_IT
#define EXTI_GPIO_Line12      ((uint8_t)0xC )           //EXTI_GPIO line 12  GPIOx_IT
#define EXTI_GPIO_Line13      ((uint8_t)0xD )           //EXTI_GPIO line 13  GPIOx_IT
#define EXTI_GPIO_Line14      ((uint8_t)0xE )           //EXTI_GPIO line 14  GPIOx_IT
#define EXTI_GPIO_Line15      ((uint8_t)0xF))           //EXTI_GPIO line 15  GPIOx_IT

#define EXTI_LINE0       ((uint32_t)0x0 | (1<<0))           //EXTI line 0   GPIOx_IT
#define EXTI_LINE1       ((uint32_t)0x0 | (1<<1))           //EXTI line 1   GPIOx_IT
#define EXTI_LINE2       ((uint32_t)0x0 | (1<<2))           //EXTI line 2   GPIOx_IT
#define EXTI_LINE3       ((uint32_t)0x0 | (1<<3))           //EXTI line 3   GPIOx_IT
#define EXTI_LINE4       ((uint32_t)0x0 | (1<<4))           //EXTI line 4   GPIOx_IT
#define EXTI_LINE5       ((uint32_t)0x0 | (1<<5))           //EXTI line 5   GPIOx_IT
#define EXTI_LINE6       ((uint32_t)0x0 | (1<<6))           //EXTI line 6   GPIOx_IT
#define EXTI_LINE7       ((uint32_t)0x0 | (1<<7))           //EXTI line 7   GPIOx_IT
#define EXTI_LINE8       ((uint32_t)0x0 | (1<<8))           //EXTI line 8   GPIOx_IT
#define EXTI_LINE9       ((uint32_t)0x0 | (1<<9))           //EXTI line 9   GPIOx_IT
#define EXTI_LINE10      ((uint32_t)0x0 | (1<<10))          //EXTI line 10  GPIOx_IT
#define EXTI_LINE11      ((uint32_t)0x0 | (1<<11))          //EXTI line 11  GPIOx_IT
#define EXTI_LINE12      ((uint32_t)0x0 | (1<<12))          //EXTI line 12  GPIOx_IT
#define EXTI_LINE13      ((uint32_t)0x0 | (1<<13))          //EXTI line 13  GPIOx_IT
#define EXTI_LINE14      ((uint32_t)0x0 | (1<<14))          //EXTI line 14  GPIOx_IT
#define EXTI_LINE15      ((uint32_t)0x0 | (1<<15))          //EXTI line 15  GPIOx_IT
#define EXTI_LINE16      ((uint32_t)0x0 | (1<<16))          //EXTI line 16 is connected to the PVD output
#define EXTI_LINE17      ((uint32_t)0x0 | (1<<17))          //EXTI line 17 is connected to the RTC Alarm event
#define EXTI_LINE18      ((uint32_t)0x0 | (1<<18))          //EXTI line 18 is connected to the internal USB wakeup event
#define EXTI_LINE19      ((uint32_t)0x0 | (1<<19))          //EXTI line 19 is connected to the RTC Tamper and TimeStamp events
#define EXTI_LINE20      ((uint32_t)0x0 | (1<<20))          //EXTI line 20 is connected to the RTC Wakeup event
#define EXTI_LINE21      ((uint32_t)0x0 | (1<<21))          //EXTI line 21 is connected to the Comparator 1 output
#define EXTI_LINE22      ((uint32_t)0x0 | (1<<22))          //EXTI line 22 is connected to the Comparator 2 output
#define EXTI_LINE23      ((uint32_t)0x0 | (1<<23))          //EXTI line 23 is connected to the internal I2C1 wakeup event
#define EXTI_LINE24      ((uint32_t)0x0 | (1<<24))          //EXTI line 24 is reserved (internally held low)
#define EXTI_LINE25      ((uint32_t)0x0 | (1<<25))          //EXTI line 25 is connected to the internal USART1 wakeup event
#define EXTI_LINE26      ((uint32_t)0x0 | (1<<26))          //EXTI line 26 is connected to the internal USART2 wakeup event
#define EXTI_LINE27      ((uint32_t)0x0 | (1<<27))          //EXTI line 27 is connected to the internal CEC wakeup event
#define EXTI_LINE28      ((uint32_t)0x0 | (1<<28))          //EXTI line 28 USART3 wakeup event (available only onSTM32F09x devices)
#define EXTI_LINE29      ((uint32_t)0x0 | (1<<29))          //EXTI line 29 is reserved (internally held low)
#define EXTI_LINE30      ((uint32_t)0x0 | (1<<30))          //EXTI line 30 is reserved (internally held low)
#define EXTI_LINE31      ((uint32_t)0x0 | (1<<31))          //EXTI line 31 is connected to the VDDIO2 supply comparator output

typedef enum{
    EXTI_GPIOA     =   0UL,
    EXTI_GPIOB     ,
    EXTI_GPIOC     ,
    EXTI_GPIOD     ,
    EXTI_GPIOE     ,
    EXTI_GPIOF     
}EXTI_GPIOx_TypeDef;

typedef enum{
    EXTI_Mode_Interrupt =   0x01U,
    EXTI_Mode_Event    
}EXTI_Mode_TypeDef;

typedef struct {
    volatile uint32_t   EXTI_Line;
    volatile uint8_t    EXTI_GPIO_Line;
    EXTI_Mode_TypeDef   EXTI_MODE;
    EXTI_GPIOx_TypeDef  EXTI_GPIOx;
}EXTI_InitTypeDef;

/*Configura los registros EXTI*/
void EXTI_config(EXTI_InitTypeDef *EXTI_config);

/*Generate a software event*/
void EXTI_Generate_SW_IT(uint32_t EXTI_Line);

/*Clear bit of IT_Pending*/
void EXTI_ClearIT(uint32_t EXTI_Line);

/*Return status of IT*/
uint8_t EXTI_Get_StatusIT(uint32_t Exti_line);
#endif