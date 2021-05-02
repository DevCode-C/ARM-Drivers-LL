#include "types.h"
#include "registers.h"
#include "rcc.h"
#include "gpio.h"
#include "nvic.h"
#include <stdio.h>

extern void initialise_monitor_handles(void);
void mostrarBits(uint16_t valor);
int main(void){
    initialise_monitor_handles();
    GPIO_InitTypeDef GPIOA_Init;
    GPIO_InitTypeDef GPIOB_Init;
    
    RCC_GPIOx_enable(RCC_GPIOA);
    GPIOA_Init.MODE = GPIO_MODE_OUTPUT;
    GPIOA_Init.PIN = GPIO_PIN_5; 
    gpio_configPort(GPIOA,&GPIOA_Init);

    RCC_GPIOx_enable(RCC_GPIOB);
    GPIOB_Init.PIN = GPIO_PIN_ALL;
    GPIOB_Init.MODE = GPIO_MODE_OUTPUT;
    gpio_configPort(GPIOB,&GPIOB_Init);

    nvic_EnableIrq(EXTI0_1);
    nvic_SetPriority(EXTI0_1,1);

    nvic_EnableIrq(EXTI2_3);
    nvic_SetPriority(EXTI2_3,3);
    while (1){
        printf("dentro del while\n");
        gpio_setPins(GPIOB,GPIO_PIN_0);
        for (uint8_t i = 0; i < 16; i++){
            mostrarBits((uint16_t)GPIOB->ODR);
            LEFT_SHIFT(GPIOB->ODR,1);
            _delay(100000);
        }
        nvic_SetPendingIrq(EXTI0_1);
        printf("\n");
    }   
}

void EXTI0_1_Handler(void){
    printf("\ndentro de la interrupcion\n");
    for (uint8_t i = 0; i < 20; i++){
        gpio_togglePins(GPIOA,GPIO_PIN_5);
        _delay(100000);
    }
    nvic_SetPendingIrq(EXTI2_3);
} 

void EXTI2_3_Handler(void){
    printf("\nDentro de la segunda interrupcion\n");
     for (uint8_t i = 0; i < 20; i++){
        gpio_togglePins(GPIOA,GPIO_PIN_5);
        _delay(100000/2);
    }
   
}

void mostrarBits(uint16_t valor){
    volatile uint16_t temp ;
    volatile uint16_t shift1 = 1<<15 ;
    temp = valor;
    printf("\nValor asignado al registro ODR en HEX: %x\t\t Valor asignado al registro ODR en BIN: ",valor);
    for (uint8_t i = 0; i < 16; i++){
        putchar(temp & shift1 ? '1':'0');
        temp <<= 1;
    }
    
}