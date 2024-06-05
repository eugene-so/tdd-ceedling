/*******************************************************************************
 *    INCLUDED FILES
 ******************************************************************************/
#include "CException.h"
#include "unity.h"

#include <string.h>

#include "cexception_defines.h"

#include "Leds.h"

/*******************************************************************************
 *    DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 *    PRIVATE TYPES
 ******************************************************************************/

/*******************************************************************************
 *    PRIVATE DATA
 ******************************************************************************/
static uint16_t virtualLeds;

/*******************************************************************************
 *    PRIVATE FUNCTIONS
 ******************************************************************************/

/*******************************************************************************
 *    SETUP, TEARDOWN
 ******************************************************************************/

void setUp(void)
{
    /* This runs before every test function on this file */
    Leds_Init(&virtualLeds);
}

void tearDown(void)
{
    /* This runs after every test function on this file */
}

/*******************************************************************************
 *    TESTS
 *    Note: A simple unit test demonstrating setUp/tearDown and hardware dependency
 *    injection, assuming a led driver where each led is memory mapped.
 ******************************************************************************/
void test_leds_LedOffAfterInit(void)
{
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}

void test_leds_TurnOnLedOne(void)
{
    Led_TurnOn(1);
    TEST_ASSERT_EQUAL_HEX16(1, virtualLeds);
}

void test_leds_TurnOffledOne(void)
{
    Led_TurnOn(1);
    Led_TurnOff(1);
    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}
