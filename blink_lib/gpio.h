#ifndef GPIO_H
#define GPIO_H
#include "types.h"
#include "registers.h"

/*Definiciones de la estructura*/
typedef struct{
    volatile uint32_t PIN;
    volatile uint32_t MODE;
    volatile uint32_t PULL;
    volatile uint32_t ALTERNATE;
}GPIO_InitTypeDef;
/*----------------------------*/

/*Definiciones de los pines*/
#define GPIO_PIN_0  ((uint32_t)0x0 |(1<<0))
#define GPIO_PIN_1  ((uint32_t)0x0 |(1<<1))
#define GPIO_PIN_2  ((uint32_t)0x0 |(1<<2))
#define GPIO_PIN_3  ((uint32_t)0x0 |(1<<3))
#define GPIO_PIN_4  ((uint32_t)0x0 |(1<<4))
#define GPIO_PIN_5  ((uint32_t)0x0 |(1<<5))
#define GPIO_PIN_6  ((uint32_t)0x0 |(1<<6))
#define GPIO_PIN_7  ((uint32_t)0x0 |(1<<7))
#define GPIO_PIN_8  ((uint32_t)0x0 |(1<<8))
#define GPIO_PIN_9  ((uint32_t)0x0 |(1<<9))
#define GPIO_PIN_10 ((uint32_t)0x0 |(1<<10))
#define GPIO_PIN_11 ((uint32_t)0x0 |(1<<11))
#define GPIO_PIN_12 ((uint32_t)0x0 |(1<<12))
#define GPIO_PIN_13 ((uint32_t)0x0 |(1<<13))
#define GPIO_PIN_14 ((uint32_t)0x0 |(1<<14))
#define GPIO_PIN_15 ((uint32_t)0x0 |(1<<15))
/*-------------------------*/

#define GPIO_MODE_INPUT         ((uint32_t)0x0)
#define GPIO_MODE_OUTPUT        ((uint32_t)0x1)
#define GPIO_MODE_ALT           ((uint32_t)0x2)
#define GPIO_MODE_ANALOG         ((uint32_t)0x3)

#define GPIO_NOPULL             ((uint32_t)0x0)
#define GPIO_PULLUP             ((uint32_t)0x1)
#define GPIO_PULLDOWN           ((uint32_t)0x2)


/*Configura x número de pines para funcionar como entradas, salidas, modo alterno o análogos,
además de permitir establecer opciones como resistencias de pullup/pulldown. 
La configuración y los pines a configurar estara indicada por las estructura de tipo GPIO_InitTypeDef
 y el puerto a configurar por el puntero a estructura port.
*/
void gpio_configPort( GPIO_TypeDef *port, GPIO_InitTypeDef *config );

/*escribe un valor completo en el puerto indicado.*/
void gpio_writePort( GPIO_TypeDef *port, uint32_t value );

/*regresa el valor del puerto indicado.*/
uint32_t gpio_readPort( GPIO_TypeDef *port );

/*pone en uno aquellos pines indicados en la variable pins, donde cada bit representa un pin 
(los puertos solo tienen 16 pines, asi que solo se usaran los primeros 16 bits).
*/
void gpio_setPins( GPIO_TypeDef *port, uint32_t pins );

/*pone en cero aquellos pines indicados en la variable pins, donde cada bit representa un pin 
(los puertos solo tienen 16 pines, asi que solo se usaran los primeros 16 bits).
*/
void gpio_resetPins( GPIO_TypeDef *port, uint32_t pins );

/*invierte el estado de aquellos pines indicados en la variable pins, 
donde cada bit representa un pin (los puertos solo tienen 16 pines, asi que solo se usaran los primeros 16 bits).
*/
void gpio_togglePins( GPIO_TypeDef *port, uint32_t pins );

/*escribe el valor indicado por value (0 o 1) en el pin indicado por el parámetro pin.
*/
void gpio_writePins( GPIO_TypeDef *port, uint32_t pins, uint32_t value );

/*regresa el valor del pin indicado del puerto indicado por el parámetro pin.
*/
uint32_t gpio_readPin( GPIO_TypeDef *port, uint32_t pin );

#endif 