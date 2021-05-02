#include "types.h"
#include "registers.h"
#include "rcc.h"
#include "gpio.h"

int main(void){
    GPIO_InitTypeDef GPIOA_Init;
    //RCC_GPIOx_enable(RCC_GPIOA);
    // RCC->AHBENR |=1<<17;
    RCC_GPIOx_enable(RCC_GPIOA);
    GPIOA_Init.MODE = GPIO_MODE_OUTPUT;
    GPIOA_Init.PIN = GPIO_PIN_5;
    // GPIOA->MODER |= 1<<10;
    // volatile uint32_t i;
    gpio_configPort(GPIOA,&GPIOA_Init);
    while (1){
        gpio_togglePins(GPIOA,GPIO_PIN_5);
        // GPIOA->ODR ^=1<<5;
         _delay(100000);
        // for (i = 0; i < 100000; i++){
        // }
    }   
}