#include "types.h"
#include "registers.h"
#include "gpio.h"
#include "exti.h"

void gpio_configPort( GPIO_TypeDef *port, GPIO_InitTypeDef *config ){
    for (volatile uint8_t i = 0; i < 16; i++){
        if(bitcheck(config->PIN,i)){
            port->MODER &= ~(GPIO_RESET << (i*2));
            port->MODER |= ((uint32_t)((config->MODE & 0xFU)) <<(i*2));

            port->PUPDR &= ~(GPIO_RESET <<(i*2));
            port->PUPDR |= ((uint32_t)(config->PULL)<<(i*2));

            if (config->MODE == GPIO_MODE_INPUT){
                port->PUPDR &= ~(GPIO_RESET <<(i*2));
                port->PUPDR |= ((uint32_t)(config->PULL)<<(i*2));
            }
            else if(config->MODE == GPIO_MODE_OUTPUT){
                port->OSPEEDR &= ~(GPIO_RESET<<(i*2));
                port->OSPEEDR = Set_Bit(port->OSPEEDR,i*2);
                port->OTYPER = Reset_Bit(port->OTYPER,i);
            }

            else if(config->MODE == GPIO_MODE_IT_BOTH){

                EXTI->RTSR &= ~(config->PIN);
                EXTI->FTSR &= ~(config->PIN);
                EXTI->RTSR |= (config->PIN);
                EXTI->FTSR |= (config->PIN);
            }
            else if(config->MODE == GPIO_MODE_IT_FALLING){
                EXTI->FTSR &= ~(config->PIN);
                EXTI->FTSR |= (config->PIN);
            }
            else if(config->MODE == GPIO_MODE_IT_RISING){
                
                EXTI->RTSR &= ~(config->PIN);
                EXTI->RTSR |= (config->PIN);
            }
        }
    }
}


void gpio_writePort( GPIO_TypeDef *port, uint32_t value ){
    value =(uint16_t) ((uint32_t)0x0000FFFF & value);
    port->ODR = value;
}

uint32_t gpio_readPort( GPIO_TypeDef *port ){
    return ((uint16_t)port->IDR);
}

void gpio_setPins( GPIO_TypeDef *port, uint32_t pins ){
    pins &= (uint32_t)0xFFFF;
    port->BSRRL =pins;
}

void gpio_resetPins( GPIO_TypeDef *port, uint32_t pins ){
    pins &= (uint32_t)0xFFFF;
    port->BSRRH = pins;
}

void gpio_togglePins( GPIO_TypeDef *port, uint32_t pins ){
    pins &= (uint32_t)0xFFFF;
    port->ODR ^= pins;
}

void gpio_writePins( GPIO_TypeDef *port, uint32_t pins, uint32_t value ){
    if (value > 0){
        gpio_setPins(port,pins);
    }
    else{
        gpio_resetPins(port,pins);
    }
}

uint32_t gpio_readPin( GPIO_TypeDef *port, uint32_t pin ){
    if ((port->IDR & pin)!= 0UL){
        return 1UL;
    }else{
        return 0UL;
    }
}
void gpio_isrHandler(uint32_t pin){
    EXTI_ClearIT(pin);
    gpio_isrCallback(pin);
    // EXTI_ClearIT(pin);
}