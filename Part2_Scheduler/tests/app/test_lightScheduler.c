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
void SetTimeTo(int32_t day, int32_t minute)
{
    FakeTimeService_SetDay(day);
    FakeTimeService_SetMinute(minute);
}

void TestLightState(int32_t id, int32_t state)
{
    TEST_ASSERT_EQUAL_INT32(id, LightControllerSpy_GetLastId());
    TEST_ASSERT_EQUAL_INT32(state, LightControllerSpy_GetLastState());
}

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
    TestLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

void test_lightScheduler_NoSchedule_NothingHappens(void)
{
    SetTimeTo(MONDAY, 100);
    LightScheduler_WakeUp();
    TestLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

void test_lightScheduler_ScheduleOnEverydayNotTimeYet_success(void)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    SetTimeTo(MONDAY, 1199);

    LightScheduler_WakeUp();

    TestLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

void test_lightScheduler_ScheduleOnEverydayItsTime(void)
{
    LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);
    SetTimeTo(MONDAY, 1200);

    LightScheduler_WakeUp();

    TestLightState(3, LIGHT_ON);
}

void test_lightScheduler_ScheduleOffEverydayItsTime(void)
{
    LightScheduler_ScheduleTurnOff(3, EVERYDAY, 1200);
    SetTimeTo(MONDAY, 1200);

    LightScheduler_WakeUp();

    TestLightState(3, LIGHT_OFF);
}
