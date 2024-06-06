#include "Leds.h"

#include <stdbool.h>

#include "assert.h"

enum
{
    LEDS_ALL_ON = ~0,
    LEDS_ALL_OFF = ~LEDS_ALL_ON,
};

static uint16_t* m_ledsAddress;
static uint16_t m_ledsImage;

static uint16_t ConvertLedIdToBit(uint16_t id)
{
    return (1 << (id - 1));
}

static void UpdateHardware(void)
{
    *m_ledsAddress = m_ledsImage;
}

void Leds_Init(uint16_t* address)
{
    m_ledsAddress = address;
    m_ledsImage = LEDS_ALL_OFF;
    *m_ledsAddress = m_ledsImage;
}

void Leds_Deinit(void)
{

}

void Leds_TurnAllOn(void)
{
    m_ledsImage = LEDS_ALL_ON;
    UpdateHardware();
}

void Led_TurnOn(uint16_t id)
{
    assert(id > 0 && id <= 16);

    m_ledsImage |= ConvertLedIdToBit(id);
    UpdateHardware();
}

void Led_TurnOff(uint16_t id)
{
    assert(id > 0 && id <= 16);

    m_ledsImage &= ~ConvertLedIdToBit(id);;
    UpdateHardware();
}


