#include "types.h"
#include "registers.h"
#include "gpio.h"

void gpio_configPort( GPIO_TypeDef *port, GPIO_InitTypeDef *config ){
    uint8_t i;

    if(config->MODE == GPIO_MODE_INPUT){
        for (i = 0; i < 16; i++){
            if (bitcheck(config->PIN,i)){
                // port->MODER |= (0x0<<(2*i));
                port->MODER = Reset_Bit(port->MODER,i*2);
                port->MODER = Reset_Bit(port->MODER,((i*2)+1));

                if(config->PULL==GPIO_NOPULL){
                    port->PUPDR =Reset_Bit(port->PUPDR,i*2);
                    port->PUPDR =Reset_Bit(port->PUPDR,((i*2)+1));
                }
                else if(config->PULL==GPIO_PULLUP){
                    port->PUPDR =Set_Bit(port->PUPDR,i*2);
                }
                else if(config->PULL==GPIO_PULLDOWN){
                    port->PUPDR =Set_Bit(port->PUPDR,((i*2)+1));
                }
                else{
                    port->PUPDR =Reset_Bit(port->PUPDR,i*2);
                    port->PUPDR =Reset_Bit(port->PUPDR,((i*2)+1));
                }
                
            }
        }
        
    }
    else if(config->MODE == GPIO_MODE_OUTPUT){
        for (i = 0; i < 16; i++){
            if (bitcheck(config->PIN,i)){
                port->MODER = Set_Bit(port->MODER,i*2);
                port->OTYPER = Reset_Bit(port->OTYPER,i);
            }
            
        }
    }
    else{
        // port->MODER = (uint32_t)0xFFFFFFFF;
    }
    for (i = 0; i < 16; i++){
        port->OSPEEDR = Set_Bit(port->OSPEEDR,i*2);
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
    if (bitcheck(port->IDR,pin)){
        return 1;
    }else{
        return 0;
    }
}