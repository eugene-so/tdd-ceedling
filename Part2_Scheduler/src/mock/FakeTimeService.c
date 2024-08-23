#include "FakeTimeService.h"

static Time m_fakeTime;
static WakeupCallback m_callback;
static int m_period;

void TimeService_Create(void)
{
    m_fakeTime.minuteOfDay = -1;
    m_fakeTime.dayOfWeek = -1;
    m_callback = NULL;
}

void TimeService_Destroy(void)
{
}

void TimeService_GetTime(Time * time)
{
    time->minuteOfDay = m_fakeTime.minuteOfDay;
    time->dayOfWeek = m_fakeTime.dayOfWeek;
}


int TimeService_GetMinute(void)
{
    return m_fakeTime.minuteOfDay;
}

int TimeService_GetDay(void)
{
    return m_fakeTime.dayOfWeek;
}

void TimeService_SetPeriodicAlarmInSeconds(int seconds, WakeupCallback callback)
{
    m_period = seconds;
    m_callback = callback;
}

void TimeService_CancelPeriodicAlarmInSeconds(int seconds, WakeupCallback callback)
{
    if (callback == callback && m_period == seconds)
    {
        m_callback = NULL;
        m_period = 0;
    }
}

void FakeTimeService_SetMinute(int minute)
{
    m_fakeTime.minuteOfDay = minute;
}

void FakeTimeService_SetDay(int day)
{
    m_fakeTime.dayOfWeek = day;
}

WakeupCallback FakeTimeService_GetAlarmCallback(void)
{
    return m_callback;
}

int FakeTimeService_GetAlarmPeriod(void)
{
    return m_period;
}

