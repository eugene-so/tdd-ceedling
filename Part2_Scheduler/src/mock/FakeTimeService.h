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

#endif /* FAKE_TIME_SERVICE_H */
