/*******************************************************************************
 *    INCLUDED FILES
 ******************************************************************************/
#include "CException.h"
#include "unity.h"

#include <string.h>

#include "cexception_defines.h"

#include "FakeTimeService.h"

/*******************************************************************************
 *    DEFINITIONS
 ******************************************************************************/

/*******************************************************************************
 *    PRIVATE TYPES
 ******************************************************************************/

/*******************************************************************************
 *    PRIVATE DATA
 ******************************************************************************/

/*******************************************************************************
 *    PRIVATE FUNCTIONS
 ******************************************************************************/

/*******************************************************************************
 *    SETUP, TEARDOWN
 ******************************************************************************/

void setUp(void)
{
    /* This runs before every test function on this file */
}

void tearDown(void)
{
    /* This runs after every test function on this file */
}

/*******************************************************************************
 *    TESTS
 ******************************************************************************/
void test_fakeTimeService_Create(void)
{
    Time time;
    TimeService_GetTime(&time);
    TEST_ASSERT_EQUAL_INT32(TIME_UNKNOWN, time.minuteOfDay);
    TEST_ASSERT_EQUAL_INT32(TIME_UNKNOWN, time.dayOfWeek);
}

void test_fakeTimeService_Set(void)
{
    Time time;
    FakeTimeService_SetMinute(42);
    FakeTimeService_SetDay(SATURDAY);
    TimeService_GetTime(&time);
    TEST_ASSERT_EQUAL_INT32(42, time.minuteOfDay);
    TEST_ASSERT_EQUAL_INT32(SATURDAY, time.dayOfWeek);

}
