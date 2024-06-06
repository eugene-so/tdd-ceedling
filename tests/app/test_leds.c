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

void test_leds_TurnOnMultipleLeds(void)
{
    Led_TurnOn(9);
    Led_TurnOn(8);
    TEST_ASSERT_EQUAL_HEX16(0x180, virtualLeds);
}

void test_leds_AllOn(void)
{
    Leds_TurnAllOn();
    TEST_ASSERT_EQUAL_HEX16(0xffff, virtualLeds);
}

void test_leds_TurnOffAnyLed(void)
{
    Leds_TurnAllOn();
    Led_TurnOff(8);
    TEST_ASSERT_EQUAL_HEX16(0xff7f, virtualLeds);
}

void test_leds_LedMemory_IsNotReadable(void)
{
    virtualLeds = 0xffff;
    Led_TurnOn(8);
    TEST_ASSERT_EQUAL_HEX16(0x80, virtualLeds);
}

void test_leds_UpperAndLowerBounds(void)
{
    Led_TurnOn(1);
    Led_TurnOn(16);
    TEST_ASSERT_EQUAL_HEX16(0x8001, virtualLeds);
}

void test_leds_OutOfBoundsTurnOnCausesAssertion(void)
{
    CEXCEPTION_T e;
    Try
    {
        Led_TurnOn(-1);
        Led_TurnOn(0);
        Led_TurnOn(17);
        Led_TurnOn(3141);
        TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
        TEST_FAIL_MESSAGE("Should have thrown CEXCEPTION_ASSERT_FAIL!");
    }
    Catch(e)
    {
        TEST_ASSERT_EQUAL(CEXCEPTION_ASSERT_FAIL, e);
    }
}

void test_leds_OutOfBoundsTurnOffCauseAssertion(void)
{
    CEXCEPTION_T e;
    Try
    {
        Leds_TurnAllOn();
        Led_TurnOff(-1);
        Led_TurnOff(0);
        Led_TurnOff(17);
        Led_TurnOff(3141);
        TEST_ASSERT_EQUAL_HEX16(0xffff, virtualLeds);
        TEST_FAIL_MESSAGE("Should have thrown CEXCEPTION_ASSERT_FAIL!");
    }
    Catch(e)
    {
        TEST_ASSERT_EQUAL(CEXCEPTION_ASSERT_FAIL, e);
    }
}
