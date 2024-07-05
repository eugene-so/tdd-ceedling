#include <stdint.h>

#include "TimeService.h"
#include "LightScheduler.h"

enum
{
    MAX_EVENTS = 128, UNUSED = -1
};

typedef struct
{
    int32_t id;
    int32_t minuteOfDay;
} ScheduledLightEvent_t;

static ScheduledLightEvent_t scheduledEvent;

void LightScheduler_Create(void)
{
    scheduledEvent.id = UNUSED;
}

void LightScheduler_Destroy(void)
{

}

void LightScheduler_ScheduleTurnOn(int32_t id, Day day, int32_t minuteOfDay)
{
    scheduledEvent.id = id;
    scheduledEvent.minuteOfDay = minuteOfDay;
}

void LightScheduler_WakeUp(void)
{
    Time time;
    TimeService_GetTime(&time);

    if (scheduledEvent.id == UNUSED)
        return;

    if (time.minuteOfDay != scheduledEvent.minuteOfDay)
        return;

}
