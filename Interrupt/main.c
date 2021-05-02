#include "types.h"
#include "registers.h"
#include "rcc.h"
#include "gpio.h"
#include "nvic.h"
#include "exti.h"
#include <stdio.h>
uint8_t contador=0;
extern void initialise_monitor_handles(void);
void mostrarBits(uint16_t valor);
int main(void){
    initialise_monitor_handles();
    GPIO_InitTypeDef GPIOA_Init;
    GPIO_InitTypeDef GPIOC_Init;
    EXTI_InitTypeDef EXTI_Init;
    
    RCC_GPIOx_enable(RCC_GPIOA);
    GPIOA_Init.MODE = GPIO_MODE_OUTPUT;
    GPIOA_Init.PIN = GPIO_PIN_5; 
    gpio_configPort(GPIOA,&GPIOA_Init);

    RCC_GPIOx_enable(RCC_GPIOC);
    GPIOC_Init.PIN = GPIO_PIN_13;
    GPIOC_Init.MODE = GPIO_MODE_IT_RISING;
    GPIOC_Init.PULL = GPIO_PULLUP;
    gpio_configPort(GPIOC,&GPIOC_Init);
  
    
    RCC_SYSCFG();
    EXTI_Init.EXTI_MODE = EXTI_Mode_Interrupt;
    EXTI_Init.EXTI_Line = EXTI_LINE13;
    EXTI_Init.EXTI_GPIO_Line= EXTI_GPIO_Line13;
    EXTI_Init.EXTI_GPIOx = EXTI_GPIOC;
    EXTI_config(&EXTI_Init);

    nvic_EnableIrq(EXTI4_15);
    nvic_SetPriority(EXTI4_15,1);

    while (1){
        printf("dentro del while\n");
        if(gpio_readPin(GPIOC,GPIO_PIN_13)){
            printf("Button funcionando\n");
        }
        if (contador ==1){
            gpio_togglePins(GPIOA,GPIO_PIN_5);
        }
        else if(contador ==2){
            gpio_resetPins(GPIOA,GPIO_PIN_5);
            contador=0;
        }
        
        printf("\n");
        _delay(10000);
    }   
}

void EXTI4_15_Handler(void){
    printf("\ndentro de la interrupcion\n");
    gpio_isrHandler(EXTI_LINE13);
} 

void gpio_isrCallback(uint32_t pin){
    contador++;
    //gpio_togglePins(GPIOA,GPIO_PIN_5);
}


