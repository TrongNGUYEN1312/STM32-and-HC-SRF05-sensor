#include "HCSR05.h"

// use htim2
extern TIM_HandleTypeDef htim2;

void SR05_Init(){
	HAL_TIM_Base_Start(&htim2);
}

void SR05_Trigger(){
	HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, 1);
	HAL_Delay(1);
	HAL_GPIO_WritePin(TRIG_PORT, TRIG_PIN, 0);
}

float SR05_GetDis(){
	uint16_t time;
	float dis;
	SR05_Trigger();
	while(HAL_GPIO_ReadPin(ECHO_PORT, ECHO_PIN) == 0);

	__HAL_TIM_SET_COUNTER(&htim2,0);
	
	while(HAL_GPIO_ReadPin(ECHO_PORT, ECHO_PIN) == 1);
	time = __HAL_TIM_GET_COUNTER(&htim2); 
	dis = (time*1.0) * 0.034/2;
	if(dis > 50){
		dis = 50;
	}
	if(dis <= 0){
		dis = 0;
	}
	return dis;
}

// the: moyen quantity
uint8_t the = 10;
float SR05_Calib(){
	float res = 0 ;
	for(int i = 0 ; i < the ;i++){
		res += SR05_GetDis();
	}
	return res/the;
} 