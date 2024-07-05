#include "FakeTimeService.h"

static int theMinute;
static int theDay;

void TimeService_Create(void)
{
    theMinute = MINUTE_UNKNOWN;
    theDay = DAY_UNKNOWN;
}

void TimeService_Destroy(void)
{
}

void TimeService_GetTime(Time * time)
{
    time->minuteOfDay = theMinute;
    time->dayOfWeek = theDay;
}


int TimeService_GetMinute(void)
{
    return theMinute;
}

void FakeTimeService_SetMinute(int minute)
{
    theMinute = minute;
}

void FakeTimeService_SetDay(int day)
{
    theDay = day;
}

int TimeService_GetDay(void)
{
    return theDay;
}
