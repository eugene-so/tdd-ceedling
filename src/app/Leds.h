#include <stdint.h>
#include <stdbool.h>

void Leds_Init(uint16_t* address);

void Leds_Deinit(void);

void Leds_TurnAllOn(void);

void Leds_TurnAllOff(void);

void Led_TurnOn(uint16_t id);

void Led_TurnOff(uint16_t id);

bool Led_IsOn(uint16_t id);
