/*******************************************************************************
 *    INCLUDED FILES
 ******************************************************************************/
#include "CException.h"
#include "unity.h"

#include <string.h>

#include "cexception_defines.h"

#include "LightScheduler.h"

#include "FakeTimeService.h"
#include "LightControllerSpy.h"

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
void test_lightSchedulerInitAndCleanup_CreateStartsOneMinuteAlarm(void)
{
    LightScheduler_Create();
    TEST_ASSERT_EQUAL_UINT32(LightScheduler_WakeUp, FakeTimeService_GetAlarmCallback());
    TEST_ASSERT_EQUAL_UINT32(60, FakeTimeService_GetAlarmPeriod());
    LightScheduler_Destroy();
}

void test_lightSchedulerInitAndCleanup_DestroyCancelsOneMinuteAlarm(void)
{
    LightScheduler_Create();
    LightScheduler_Destroy();
    TEST_ASSERT_EQUAL_UINT32(0, FakeTimeService_GetAlarmCallback());
    TEST_ASSERT_EQUAL_UINT32(0, FakeTimeService_GetAlarmPeriod());
}
