#include "Leds.h"

static uint16_t* m_ledsAddress;
void Leds_Init(uint16_t* address)
{
    m_ledsAddress = address;
    *address = 0;
}

void Leds_Deinit(void)
{

}

void Led_TurnOn(uint16_t id)
{
    /* This is purposefully coded poorly */
    *m_ledsAddress = 1;
}

void Led_TurnOff(uint16_t id)
{
    /* This is purposefully coded poorly */
    *m_ledsAddress = 0;
}
