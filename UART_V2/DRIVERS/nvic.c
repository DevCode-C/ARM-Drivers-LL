#include "registers.h"
#include "types.h"
#include "nvic.h"

/*Establece la prioridad que tendrá la interrupción.*/
void nvic_SetPriority( IRQ_types irq, uint32_t priority ){
    NVIC->IPR[_Pos_Assignment_IP(irq)]= (((uint32_t)NVIC->IPR[_Pos_Assignment_IP(irq)] & ~(0xFFUL<<_Bit_Shift(irq))) |
    ((priority << 6) & (uint32_t)0xFFUL) << _Bit_Shift(irq));

    // NVIC->IPR[_Pos_Assignment_IP(irq)] &= ~(0xFFUL<<_Bit_Shift(irq)) | (((priority << 6) & (uint32_t)0xFFUL) << _Bit_Shift(irq));
}

/*regresa el valor que tiene la prioridad.*/
uint32_t nvic_GetPriority( IRQ_types irq ){
    return ((uint32_t)(NVIC->IPR[_Pos_Assignment_IP(irq)]>>_Bit_Shift(irq) & ((uint32_t)0xFFUL)>>6));
}

/*habilita la interrupción deseada, esto quiere decir que una interrupción podrá ser activada por una señal*/
void nvic_EnableIrq( IRQ_types irq ){
    NVIC->ISER = (uint32_t)(1U<<((uint32_t)(irq & 0x1FUL)));
}

/*deshabilita la interrupción deseada */
void nvic_DisableIrq( IRQ_types irq ){
    NVIC->ICER = ((uint32_t)(1U<<((uint32_t)(irq & 0x1FUL))));
}

/*Regresa la interrupción que esta activa (esto no implica que el procesador la este atendiendo aun)*/
uint32_t nvic_GetPendingIrq( IRQ_types irq ){
    return ((uint32_t)(NVIC->ISPR & (1U<<((uint32_t)irq & 0x1FUL) != 0) ? 1U : 0U ));
    // if ((NVIC->ISPR & 1U<<((uint32_t)(irq & 0x1FUL))) != 0){
    //     return 1;
    // }
    // else{
    //     return 0;
    // }
}

/*activa la interrupción para que el procesador la atienda.*/
void nvic_SetPendingIrq( IRQ_types irq ){
    NVIC->ISPR = ((uint32_t)1U<<((uint32_t)(irq & 0x1FUL)));
}

/*Indica al procesador que ya no debe atender la interrupción*/
void nvic_ClearPendingIrq( IRQ_types irq ){
    NVIC->ICPR = ((uint32_t)1U<< ((uint32_t)(irq & 0x1FUL)));
}