#ifndef FAKE_TIME_SERVICE_H
#define FAKE_TIME_SERVICE_H

#include <stdint.h>

#include "TimeService.h"

enum
{
    TIME_UNKNOWN,
};

void FakeTimeService_SetMinute(int32_t);
void FakeTimeService_SetDay(int32_t);
WakeupCallback FakeTimeService_GetAlarmCallback(void);
int32_t FakeTimeService_GetAlarmPeriod(void);

#endif /* FAKE_TIME_SERVICE_H */
