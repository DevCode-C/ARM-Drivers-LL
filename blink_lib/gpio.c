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
    
    // switch (config->MODE)
    // {
    //     case GPIO_MODE_INPUT:
    //         for(uint16_t i = 0; i < 16;i++){
    //             if(bitcheck(config->PIN,i)){
    //                 port->MODER = Reset_Bit(port->MODER,i); 
    //             }
    //         }
    //         break;
    //     case GPIO_MODE_OUTPUT:
    //         break;
    //     case GPIO_MODE_ALT:
    //         break;
    //     case GPIO_MODE_ANALOG:
    //         break;
        
    //     default:
    //         break;
    // }
}

void gpio_writePort( GPIO_TypeDef *port, uint32_t value ){
    value =(uint16_t) ((uint32_t)0x0000FFFF & value);

    for (uint8_t i = 0; i < 16; i++){
        if (bitcheck(value,i)){
            port->ODR = Set_Bit(port->ODR,i); 
        }
        else{
            port->ODR = Reset_Bit(port->ODR,i); 
        }   
    }
    
}

uint32_t gpio_readPort( GPIO_TypeDef *port ){
    uint16_t salida = 0;
    for (uint8_t i = 0; i < 16; i++){
        if(bitcheck(port->IDR,i)){
            salida |= 1<<i;
        }
        else{
            salida &= ~1<<i;
        }
        
    }
    
    return salida;
}

void gpio_setPins( GPIO_TypeDef *port, uint32_t pins ){
    for (uint8_t i = 0; i < 16; i++){
        if (bitcheck(pins,i)){
            port->ODR = Set_Bit(port->ODR,i);
        }
    }
    
    
}

void gpio_resetPins( GPIO_TypeDef *port, uint32_t pins ){
    for (uint8_t i = 0; i < 16; i++){
        if (bitcheck(pins,i)){
            port->ODR = Reset_Bit(port->ODR,i);
        }
    }
}

void gpio_togglePins( GPIO_TypeDef *port, uint32_t pins ){
    for (uint8_t i = 0; i < 16; i++){
        if (bitcheck(pins,i)){
            port->ODR = Toogle_Bit(port->ODR,i);
        }
    }
}

void gpio_writePins( GPIO_TypeDef *port, uint32_t pins, uint32_t value ){
    for (uint8_t i = 0; i < 16; i++){
        if (bitcheck(pins,i)){
            if (value!= 0){
                 port->ODR = Set_Bit(port->ODR,i);
            }
            else{
                port->ODR = Reset_Bit(port->ODR,i);
            }
        }
    }
}

uint32_t gpio_readPin( GPIO_TypeDef *port, uint32_t pin ){
    if (bitcheck(port->IDR,pin)){
        return 1;
    }else{
        return 0;
    }
}