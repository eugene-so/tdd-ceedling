#ifndef LIGHT_SCHEDULER_H
#define LIGHT_SCHEDULER_H

#if 0
enum Day
{
    NONE=-1,
    EVERYDAY=10,
    WEEKDAY,
    WEEKEND,
    SUNDAY=1,
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY
};
#endif

typedef enum Day Day;

void LightScheduler_Create(void);
void LightScheduler_Destroy(void);
void LightScheduler_ScheduleTurnOn(int id, Day day, int minuteOfDay);
void LightScheduler_ScheduleTurnOff(int id, Day day, int minuteOfDay);
void LightScheduler_WakeUp(void);

#endif /* LIGHT_SCHEDULER_H */
