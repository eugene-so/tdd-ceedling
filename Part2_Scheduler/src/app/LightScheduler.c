#include <stdbool.h>
#include <stdint.h>

#include "TimeService.h"
#include "LightController.h"
#include "LightScheduler.h"
#include "RandomMinute.h"

enum
{
    TURN_ON,
    TURN_OFF,
    RANDOM_ON,
    RANDOM_OFF,
};

enum
{
    MAX_EVENTS = 128, UNUSED = -1
};

typedef struct
{
    int32_t id;
    Day day;
    int32_t minuteOfDay;
    int32_t event;
    int randomize;
    int randomMinutes;
} ScheduledLightEvent_t;

static ScheduledLightEvent_t scheduledEvent;

static ScheduledLightEvent_t scheduledEvents[MAX_EVENTS];

void LightScheduler_Create(void)
{
    for (uint8_t i = 0; i < MAX_EVENTS; ++i)
        scheduledEvents[i].id = UNUSED;

    TimeService_SetPeriodicAlarmInSeconds(60, LightScheduler_WakeUp);
}

void LightScheduler_Destroy(void)
{
    TimeService_CancelPeriodicAlarmInSeconds(60, LightScheduler_WakeUp);
}

static bool ScheduleEvent(int32_t id, Day day, int32_t minuteOfDay, int32_t event)
{
    if (id < 0 || id >= MAX_LIGHTS)
        return false;

    for (uint8_t i = 0; i < MAX_EVENTS; ++i)
    {
        if (scheduledEvents[i].id == UNUSED)
        {
            scheduledEvents[i].id = id;
            scheduledEvents[i].day = day;
            scheduledEvents[i].event = event;
            scheduledEvents[i].minuteOfDay = minuteOfDay;
            return true;
        }
    }

    return false;
}

bool LightScheduler_ScheduleTurnOn(int32_t id, Day day, int32_t minuteOfDay)
{
    return ScheduleEvent(id, day, minuteOfDay, TURN_ON);
}

bool LightScheduler_ScheduleTurnOff(int32_t id, Day day, int32_t minuteOfDay)
{
    return ScheduleEvent(id, day, minuteOfDay, TURN_OFF);
}

#if 1
void LightScheduler_Randomize(int32_t id, Day day, int32_t minuteOfDay)
{
    for (uint8_t i = 0; i < MAX_EVENTS; i++)
    {
        ScheduledLightEvent_t *event = &scheduledEvents[i];
        if (event->id == id && event->day == day && event->minuteOfDay == minuteOfDay)
        {
            event->randomize = RANDOM_ON;
            event->randomMinutes = RandomMinute_Get();
        }
    }
}
#endif

void LightScheduler_ScheduleRemove(int32_t id, Day day, int32_t minute)
{
    uint8_t i;

    for (i = 0; i < MAX_EVENTS; i++)
    {
        if (scheduledEvents[i].id == id
         && scheduledEvents[i].day == day
         && scheduledEvents[i].minuteOfDay == minute)
         {
             scheduledEvents[i].id = UNUSED;
         }
    }
 }

static void OperateLight(ScheduledLightEvent_t* lightEvent)
{
    if (lightEvent->event == TURN_ON)
        LightController_On(lightEvent->id);
    else if (lightEvent->event == TURN_OFF)
        LightController_Off(lightEvent->id);
}

static bool IsReactionDay(Time* time, Day reactionDay)
{
    Day today = time->dayOfWeek;

    if (reactionDay == EVERYDAY)
        return true;

    if (reactionDay == today)
        return true;

    if (reactionDay == WEEKEND && (SATURDAY == today || SUNDAY == today))
        return true;

    if (reactionDay == WEEKDAY && today >= MONDAY && today <= FRIDAY)
        return true;

    return false;
}

static void ProcessEventDueNow(Time* time, ScheduledLightEvent_t* lightEvent)
{
    if (lightEvent->id == UNUSED)
        return;

    if (!IsReactionDay(time, lightEvent->day))
        return;

    if (lightEvent->minuteOfDay != time->minuteOfDay)
        return;

    OperateLight(lightEvent);
}

void LightScheduler_WakeUp(void)
{
    Time time;
    TimeService_GetTime(&time);

    for (uint8_t i = 0; i < MAX_EVENTS; ++i)
        ProcessEventDueNow(&time, &scheduledEvents[i]);
}
