#ifndef _HC05
#define _HC05
//-----------------------------INCLUDE-----------------------
#include "stm32f1xx_hal.h"

//-------------------------------VAR-------------------------
#define TRIG_PIN   GPIO_PIN_9
#define TRIG_PORT  GPIOB


#define ECHO_PIN   GPIO_PIN_8
#define ECHO_PORT  GPIOB


//-------------------------------API-------------------------
void SR05_Init();
void SR05_Trigger();
float SR05_GetDis();
float SR05_Calib();

#endif