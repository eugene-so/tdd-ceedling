#include <stdbool.h>
#include <stdint.h>

#include "TimeService.h"
#include "LightScheduler.h"

enum
{
    TURN_ON,
    TURN_OFF,
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
} ScheduledLightEvent_t;

static ScheduledLightEvent_t scheduledEvent;

void LightScheduler_Create(void)
{
    scheduledEvent.id = UNUSED;
}

void LightScheduler_Destroy(void)
{

}

static void ScheduleEvent(int32_t id, Day day, int32_t minuteOfDay, int32_t event)
{
    scheduledEvent.id = id;
    scheduledEvent.day = day;
    scheduledEvent.event = event;
    scheduledEvent.minuteOfDay = minuteOfDay;
}

void LightScheduler_ScheduleTurnOn(int32_t id, Day day, int32_t minuteOfDay)
{
    ScheduleEvent(id, day, minuteOfDay, TURN_ON);
}

void LightScheduler_ScheduleTurnOff(int32_t id, Day day, int32_t minuteOfDay)
{
    ScheduleEvent(id, day, minuteOfDay, TURN_OFF);
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

    ProcessEventDueNow(&time, &scheduledEvent);
}
