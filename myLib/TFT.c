#include "TFT.h"

// use hspi1
extern SPI_HandleTypeDef hspi1;
 
void writeCMDTFT(uint8_t cmd){
	HAL_GPIO_WritePin(PORT_CS, PIN_CS, 0); // CS = 0
	HAL_GPIO_WritePin(PORT_A0, PIN_A0, 0); // A0 = 0 -> CMD
	HAL_SPI_Transmit(&hspi1, &cmd,1,1000);
	HAL_GPIO_WritePin(PORT_CS, PIN_CS, 1); // CS = 1
}

void writeDataTFT(uint8_t data){
	HAL_GPIO_WritePin(PORT_CS, PIN_CS, 0);
	HAL_GPIO_WritePin(PORT_A0, PIN_A0, 1); // A0 = 1 -> DATA
	HAL_SPI_Transmit(&hspi1, &data,1,1000);
	HAL_GPIO_WritePin(PORT_CS, PIN_CS, 1);
}

void sendCMDList(const uint8_t* cmdList){
	uint8_t index = 0;
	uint8_t cmd = 0;
	uint8_t num = 0;
	
	while(1){
		cmd = *cmdList++;
		num = *cmdList++;
		if(cmd == LCD_CMD_END){
			break;
		}else{
			writeCMDTFT(cmd);
			for(index = 0; index < num ; index++){
				writeDataTFT(*cmdList++);
			}
		}
	}
}

void setPos(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2){
	writeCMDTFT(0x2A);
	writeDataTFT(0x00);
	writeDataTFT(x1);
	writeDataTFT(0x00);
	writeDataTFT(x2);
	writeCMDTFT(0x2B);
	writeDataTFT(0x00);
	writeDataTFT(y1);
	writeDataTFT(0x00);
	writeDataTFT(y2);
}
//RGB 16bit 565
void fullDisplay(uint16_t color){
	writeCMDTFT(0x2C);
	int i;
	for(i = 0 ; i < 128*160;i++){
		writeDataTFT(color & 0xFF);
		writeDataTFT(color >> 8);
	}
}


void drawPixel(uint8_t x, uint8_t y, uint16_t color){
	if(x >= 128 || y >= 160){
		return ;
	}
	setPos(x,y,x+1,y+1);
	writeCMDTFT(0x2C);
	writeDataTFT(color & 0xFF);
	writeDataTFT(color >> 8);
}

void initTFT(){
	// HW RESET
	HAL_GPIO_WritePin(PORT_RESET, PIN_RESET,0);
	HAL_Delay(20);
	HAL_GPIO_WritePin(PORT_RESET, PIN_RESET,1);
	HAL_Delay(150);
	//SW RESET
	writeCMDTFT(0x01);
	HAL_Delay(150);
	// Sleep out
	writeCMDTFT(0x11);
	HAL_Delay(255);
	
	sendCMDList(u8InitCmdList);
	
	writeCMDTFT(0x36); // Memory Data Access Control 
	writeDataTFT(0x08);
	
	writeCMDTFT(0x3A); // Interface Pixel Format
	writeDataTFT(0x05);
	
	writeCMDTFT(0x20); // Display inversion off 
	
	setPos(0,0,128,160);
	
	// EN DISPLAY
	writeCMDTFT(0x29);
	HAL_Delay(100);

}



void drawMap(){
	// Vien xanh duong
	for(uint8_t x = 0 ; x < 128;x++){
		drawPixel(x,0,0x001F);
		drawPixel(x,159,0x001F);
	}
	
	for(uint8_t y = 0 ; y < 160;y++){
		drawPixel(0,y,0x001F);
		drawPixel(127,y,0x001F);
	}
	
	for(uint8_t x = 1; x < 127 ;x++){
		for(uint8_t y = 1 ; y < 159 ; y++){
			if(x < 64){
				drawPixel(x,y,0x0000);
			}else{
				drawPixel(x,y,0xFFFF);
			}
		}
	}
	
}


void drawBlinkingPoint(uint8_t x, uint8_t y){
	static uint8_t lastX = 2;
	static uint8_t lastY = 80;
	if(x == 0 || x == 127 || y == 0 || y == 159){
		return;
	}
	uint16_t oldColor = (lastX < 64) ? 0x0000 : 0xFFFF;
	
	for(int dx = -2; dx <= 2; dx++){
		for(int  dy = -2; dy <= 2 ; dy++){
			 drawPixel(lastX+dx,lastY+dy,oldColor);
		}
	}
	
	for(int dx = -2; dx <= 2; dx++){
		for(int  dy = -2; dy <= 2 ; dy++){
			 drawPixel(x+dx,y+dy,0xF800);// 565 5 RED 6 GREEN 6 BLUE
		}
	}
	
	if(x <= 64){
		HAL_GPIO_WritePin(PORT_LED, PIN_LED, 1);
	}else{
		HAL_GPIO_WritePin(PORT_LED, PIN_LED, 0);
	}
	
	lastX = x;
	lastY = y;
}
