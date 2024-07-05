#include "Leds.h"

#include <stdbool.h>

#include "assert.h"

enum
{
    LEDS_ALL_ON = ~0,
    LEDS_ALL_OFF = ~LEDS_ALL_ON,
};

enum
{
    LED_FIRST = 1,
    LED_LAST = 16,
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

static bool IsLedInRange(uint16_t id)
{
    return  (id <= LED_LAST);
}

static void SetLedImageBit(uint16_t id)
{
    m_ledsImage |= ConvertLedIdToBit(id);
}

static void ClearLedImageBit(uint16_t id)
{
    m_ledsImage &= ~ConvertLedIdToBit(id);
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

void Leds_TurnAllOff(void)
{
    m_ledsImage = LEDS_ALL_OFF;
    UpdateHardware();
}

void Led_TurnOn(uint16_t id)
{
    assert(IsLedInRange(id));

    SetLedImageBit(id);
    UpdateHardware();
}

void Led_TurnOff(uint16_t id)
{
    assert(IsLedInRange(id));

    ClearLedImageBit(id);
    UpdateHardware();
}

bool Led_IsOn(uint16_t id)
{
    assert(IsLedInRange(id));

    return (m_ledsImage & ConvertLedIdToBit(id));
}

bool Led_IsOff(uint16_t id)
{
    return (!Led_IsOn(id));
}


