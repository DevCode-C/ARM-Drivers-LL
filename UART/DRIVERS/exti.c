#include "registers.h"
#include "types.h"
#include "exti.h"

void EXTI_config(EXTI_InitTypeDef *EXTI_config){
    if(EXTI_config->EXTI_MODE == EXTI_Mode_Interrupt){
        EXTI->IMR &= ~EXTI_config->EXTI_Line;
        EXTI->IMR |= EXTI_config->EXTI_Line;
        uint32_t temp = (((uint32_t)0x0FU)<<(0x04U*(EXTI_config->EXTI_GPIO_Line & (uint8_t)0x03U)));
        SYSCFG->EXTICR[EXTI_config->EXTI_GPIO_Line >> 0x2U] &= ~temp;
        SYSCFG->EXTICR[EXTI_config->EXTI_GPIO_Line >> 0x2U] |= (((uint32_t)EXTI_config->EXTI_GPIOx)<<(0x04U * (EXTI_config->EXTI_GPIO_Line & (uint8_t)0x03U)));
        // SYSCFG->EXTICR[4] |= (((uint32_t)EXTI_config->EXTI_GPIOx)<<8);
    }
    else{
        EXTI->EMR &= ~EXTI_config->EXTI_Line;
        EXTI->EMR |= EXTI_config->EXTI_Line;
    }    
}

/*Generate a software event*/
void EXTI_Generate_SW_IT(uint32_t EXTI_Line){
    EXTI->SWIER |= EXTI_Line;
}

/*Clear bit of IT_Pending*/
void EXTI_ClearIT(uint32_t EXTI_Line){
    EXTI->PR = EXTI_Line;
}

/*Return status of IT*/
uint8_t EXTI_Get_StatusIT(uint32_t EXTI_Line){
    if ((EXTI->PR & EXTI_Line) != 0){
        return (uint8_t)1U;
    }
    else{
        return (uint8_t)0U;
    }
}