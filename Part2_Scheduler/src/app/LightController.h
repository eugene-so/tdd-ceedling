#ifndef LIGHT_CONTROLLER_H
#define LIGHT_CONTROLLER_H

#include "common.h"

enum {MAX_LIGHTS = 32};

void LightController_Create(void);
void LightController_Destroy(void);
//BOOL LightController_Add(int id, LightDriver);
void LightController_TurnOn(int id);
void LightController_TurnOff(int id);

#endif  /* LIGHT_CONTROLLER_H */
