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
    LightController_Create();
    LightScheduler_Create();
}

void tearDown(void)
{
    /* This runs after every test function on this file */
    LightScheduler_Destroy();
    LightController_Destroy();
}

/*******************************************************************************
 *    TESTS
 ******************************************************************************/
void test_lightScheduler_Init_NoChangeToLights_success(void)
{
    TEST_ASSERT_EQUAL_INT32(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL_INT32(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

#if 0
void test_lightScheduler_NoSchedule_NothingHappens(void)
{
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(100);
    LightScheduler_Wakeup();
    TEST_ASSERT_EQUAL_INT32(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL_INT32(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

void test_lightScheduler_ScheduleOnEverydayNotTimeYet_success(void)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1199);

    LightScheduler_WakeUp();

    TEST_ASSERT_EQUAL_INT32(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL_INT32(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

void test_lightScheduler_ScheduleOnEverydayItsTime(void)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1200);

    LightScheduler_WakeUp();

    TEST_ASSERT_EQUAL_INT32(3, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL_INT32(LIGHT_ON, LightControllerSpy_GetLastState());
}

void test_lightScheduler_ScheduleOffEverydayItsTime(void)
{
    LightScheduler_ScheduleTurnOff(3, EVERYDAY, 1200);
    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(1200);

    LightScheduler_WakeUp();

    TEST_ASSERT_EQUAL_INT32(3, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL_INT32(LIGHT_OFF, LightControllerSpy_GetLastState());
}
#endif
