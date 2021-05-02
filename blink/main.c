typedef unsigned long uint32_t;
int main(void){
    uint32_t *RCC_AHBENR = (uint32_t *)0x40021014;
    uint32_t *PORTA_MODER = (uint32_t *)0x48000000;
    uint32_t *PORTA_ODR =(uint32_t *)0x48000014;
    volatile uint32_t i;
    *RCC_AHBENR |= 1<<17;
    *PORTA_MODER |= 1<<10;
    while (1){
        *PORTA_ODR ^=1<<5;
        for (i = 0; i < 100000; i++){
        }
    }
    return 0;
    
}