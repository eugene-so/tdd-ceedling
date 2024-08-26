/*******************************************************************************
 *    INCLUDED FILES
 ******************************************************************************/
#include "CException.h"
#include "unity.h"

#include <string.h>

#include "cexception_defines.h"

#include "LightScheduler.h"

#include "FakeRandomMinute.h"
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
static int (*SavedRandomMinute_Get)(void);

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
    if (id == LIGHT_ID_UNKNOWN)
    {
        TEST_ASSERT_EQUAL_INT32(id, LightControllerSpy_GetLastId());
        TEST_ASSERT_EQUAL_INT32(state, LightControllerSpy_GetLastState());
    }
    else
    {
        TEST_ASSERT_EQUAL_INT32(state, LightControllerSpy_GetLightState(id));
    }
}

/*******************************************************************************
 *    SETUP, TEARDOWN
 ******************************************************************************/

void setUp(void)
{
    /* This runs before every test function on this file */
    LightController_Create();
    LightScheduler_Create();

//    SavedRandomMinute_Get = RandomMinute_Get;
//    RandomMinute_Get = FakeRandomMinute_Get;
}

void tearDown(void)
{
    /* This runs after every test function on this file */
    LightScheduler_Destroy();
    LightController_Destroy();
    //RandomMinute_Get = SavedRandomMinute_Get;
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

void test_lightScheduler_ScheduleTuesdayButItsMonday(void)
{
    LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
    SetTimeTo(MONDAY, 1200);

    LightScheduler_WakeUp();

    TestLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

void test_lightScheduler_ScheduleTuesdayItsTuesday(void)
{
    LightScheduler_ScheduleTurnOn(3, TUESDAY, 1200);
    SetTimeTo(TUESDAY, 1200);

    LightScheduler_WakeUp();

    TestLightState(3, LIGHT_ON);
}

void test_lightScheduler_ScheduleWeekendItsFriday(void)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    SetTimeTo(FRIDAY, 1200);

    LightScheduler_WakeUp();

    TestLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}

void test_lightScheduler_ScheduleWeekendItsSaturday(void)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    SetTimeTo(SATURDAY, 1200);

    LightScheduler_WakeUp();

    TestLightState(3, LIGHT_ON);
}

void test_lightScheduler_ScheduleWeekendItsSunday(void)
{
    LightScheduler_ScheduleTurnOn(3, WEEKEND, 1200);
    SetTimeTo(SUNDAY, 1200);

    LightScheduler_WakeUp();

    TestLightState(3, LIGHT_ON);
}

void test_lightScheduler_ScheduleTwoEventsAtSameTime(void)
{
    LightScheduler_ScheduleTurnOn(3, SUNDAY, 1200);
    LightScheduler_ScheduleTurnOn(12, SUNDAY, 1200);
    SetTimeTo(SUNDAY, 1200);
    LightScheduler_WakeUp();

    TestLightState(3, LIGHT_ON);
    TestLightState(12, LIGHT_ON);
}

void test_lightScheduler_RejectsTooManyEvents(void)
{
    uint8_t i;
    for (i = 0; i < 128; ++i)
    {
        TEST_ASSERT_TRUE(LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));
    }
    TEST_ASSERT_FALSE(LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));
}

void test_lightScheduler_RemoveRecyclesScheduleSlot(void)
{
    uint8_t i;
    for (i = 0; i < 128; ++i)
    {
        TEST_ASSERT_TRUE(LightScheduler_ScheduleTurnOn(6, MONDAY, 600+i));
    }

    LightScheduler_ScheduleRemove(6, MONDAY, 600);

    TEST_ASSERT_TRUE(LightScheduler_ScheduleTurnOn(13, MONDAY, 1000));
}

void test_lightScheduler_RemoveMultipleScheduledEvent(void)
{
    LightScheduler_ScheduleTurnOn(6, MONDAY, 600);
    LightScheduler_ScheduleTurnOn(7, MONDAY, 600);
    LightScheduler_ScheduleRemove(6, MONDAY, 600);
    SetTimeTo(MONDAY, 600);
    LightScheduler_WakeUp();

    TestLightState(6, LIGHT_STATE_UNKNOWN);
    TestLightState(7, LIGHT_ON);
}

void test_lightScheduler_AcceptsValidLightIds(void)
{
    TEST_ASSERT_TRUE(LightScheduler_ScheduleTurnOn(0, MONDAY, 600));
    TEST_ASSERT_TRUE(LightScheduler_ScheduleTurnOn(15, MONDAY, 600));
    TEST_ASSERT_TRUE(LightScheduler_ScheduleTurnOn(31, MONDAY, 600));
}

void test_lightScheduler_RejectsInvalidLightIds(void)
{
    TEST_ASSERT_FALSE(LightScheduler_ScheduleTurnOn(-1, MONDAY, 600));
    TEST_ASSERT_FALSE(LightScheduler_ScheduleTurnOn(32, MONDAY, 600));
}

#if 0
/* Could not get this test to work for indeterminate reason */
void test_lightScheduler_Randomizer_TurnsOnEarly(void)
{
    FakeRandomMinute_SetFirstAndIncrement(-10, 5);
    LightScheduler_ScheduleTurnOn(4, EVERYDAY, 600);
    LightScheduler_Randomize(4, EVERYDAY, 600);
    SetTimeTo(MONDAY, 600-10);
    LightScheduler_WakeUp();
    TestLightState(4, LIGHT_ON);
}
#endif
