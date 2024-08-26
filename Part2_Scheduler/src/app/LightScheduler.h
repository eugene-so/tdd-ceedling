#ifndef LIGHT_SCHEDULER_H
#define LIGHT_SCHEDULER_H

#include <stdbool.h>
#include <stdint.h>

typedef enum Day Day;

void LightScheduler_Create(void);
void LightScheduler_Destroy(void);
bool LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay);
bool LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay);
void LightScheduler_Randomize(int32_t id, Day day, int32_t minuteOfDay);
void LightScheduler_ScheduleRemove(int32_t id, Day day, int32_t minute);
void LightScheduler_WakeUp(void);

#endif /* LIGHT_SCHEDULER_H */
