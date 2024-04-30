/*
 * LCD_GFX.c
 * Taken from lab 4
 * Created: 9/20/2021 6:54:25 PM
 *  Author: You
 */ 

#include "LCD_GFX.h"
#include "ST7735.h"
#include <stdbool.h>

/******************************************************************************
* Local Functions
******************************************************************************/

//draws a vertical line of a certain color within bounds
void linearUziVert(uint8_t x, uint8_t y0, uint8_t y1, uint16_t color) {
	LCD_setAddr(x,y0,x,y1);
	for(int i = y0; i <= y1; i++) {
		SPI_ControllerTx_16bit(color);
	}
}

void horizLine(uint8_t x0, uint8_t x1, uint8_t y, uint16_t color) {
	LCD_setAddr(x0,y,x1,y);
	for(int i = x0; i <= x1; i++) {
		SPI_ControllerTx_16bit(color);
	}
}

void drawLineLower(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint16_t color) {
	int xDiff = x1 - x0;
	int yDiff = y1 - y0;
	int increment = yDiff >= 0 ? 1: -1;
	yDiff *= increment;
	int needs_increase = 2 * yDiff - xDiff;
	uint8_t y = y0;
	uint8_t top = (x1 > LCD_HEIGHT - 1) ? LCD_HEIGHT - 1 : x1;
	for(uint8_t x = x0; x <= top; x++) {
		LCD_setAddr(x,y,x,y);
		SPI_ControllerTx_16bit(color);
		if (needs_increase > 0) {
			y++;
			needs_increase += 2 * (yDiff - xDiff);
		} else {
			needs_increase += 2 * yDiff;
		}
	}
}

void drawLineHigher(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint16_t color) {
	int xDiff = x1 - x0;
	int yDiff = y1 - y0;
	int increment = xDiff >= 0 ? 1: -1;
	xDiff *= increment;
	int needs_increase = 2 * xDiff - yDiff;
	uint8_t x = x0;
	uint8_t top = (y1 > LCD_HEIGHT - 1) ? LCD_HEIGHT - 1 : y1;
	for(uint8_t y = y0; y <= top; y++) {
		LCD_setAddr(x,y,x,y);
		SPI_ControllerTx_16bit(color);
		if (needs_increase > 0) {
			y++;
			needs_increase += 2 * (xDiff - yDiff);
			} else {
			needs_increase += 2 * xDiff;
		}
	}
}

/******************************************************************************
* Global Functions
******************************************************************************/

/**************************************************************************//**
* @fn			uint16_t rgb565(uint8_t red, uint8_t green, uint8_t blue)
* @brief		Convert RGB888 value to RGB565 16-bit color data
* @note
*****************************************************************************/
uint16_t rgb565(uint8_t red, uint8_t green, uint8_t blue)
{
	return ((((31*(red+4))/255)<<11) | (((63*(green+2))/255)<<5) | ((31*(blue+4))/255));
}

/**************************************************************************//**
* @fn			void LCD_drawPixel(uint8_t x, uint8_t y, uint16_t color)
* @brief		Draw a single pixel of 16-bit rgb565 color to the x & y coordinate
* @note
*****************************************************************************/
void LCD_drawPixel(uint8_t x, uint8_t y, uint16_t color) {
	LCD_setAddr(x,y,x,y);
	SPI_ControllerTx_16bit(color);
}

/**************************************************************************//**
* @fn			void LCD_drawChar(uint8_t x, uint8_t y, uint16_t character, uint16_t fColor, uint16_t bColor)
* @brief		Draw a character starting at the point with foreground and background colors
* @note
*****************************************************************************/
void LCD_drawChar(uint8_t x, uint8_t y, uint16_t character, uint16_t fColor, uint16_t bColor){
	uint16_t row = character - 0x20;		//Determine row of ASCII table starting at space
	int i, j;
	if ((LCD_WIDTH-x>7)&&(LCD_HEIGHT-y>7)){
		for(i=0;i<5;i++){
			uint8_t pixels = ASCII[row][i]; //Go through the list of pixels
			for(j=0;j<8;j++){
				if (((pixels>>j)&1)==1){
					LCD_drawPixel(x+i,y+j,fColor);
				}
				else {
					LCD_drawPixel(x+i,y+j,bColor);
				}
			}
		}
	}
}


/******************************************************************************
* LAB 4 TO DO. COMPLETE THE FUNCTIONS BELOW.
* You are free to create and add any additional files, libraries, and/or
*  helper function. All code must be authentically yours.
******************************************************************************/

/**************************************************************************//**
* @fn			void LCD_drawCircle(uint8_t x0, uint8_t y0, uint8_t radius,uint16_t color)
* @brief		Draw a colored circle of set radius at coordinates
* @note
*****************************************************************************/
void LCD_drawCircle(uint8_t x0, uint8_t y0, uint8_t radius,uint16_t color)
{
	int radsq = radius * radius;
	int j = radius;
	int i = 0;
	uint8_t low_y = 0;
	uint8_t high_y = 0;
	uint8_t low_x = 0;
	uint8_t high_x = 0;
	for (i = 0; i <= radius; i++) {
		while (j * j > radsq - i * i) {
			j--;
		}
		//low_y = j > y0 ? 0 : y0 - j;
		//high_y = (y0 + j) < LCD_HEIGHT ? y0 + j : LCD_HEIGHT - 1;
		//if (x0 + i < LCD_WIDTH) {
			//linearUziVert(x0 + i, low_y, high_y, color);
		//}
		//if (x0 > i) {
			//linearUziVert(x0 - i, low_y, high_y, color);
		//}
		low_x = j > x0 ? 0 : x0 - j;
		high_x = (x0 + j) < LCD_WIDTH ? x0 + j : LCD_WIDTH - 1;
		if (y0 + i < LCD_HEIGHT) {
			horizLine(low_x, high_x, y0 + i, color);
		}
		if (y0 > i) {
			horizLine(low_x, high_x, y0 - i, color);
		}
	}
}


/**************************************************************************//**
* @fn			void LCD_drawLine(short x0,short y0,short x1,short y1,uint16_t c)
* @brief		Draw a line from and to a point with a color
* @note
*****************************************************************************/
void LCD_drawLine(short x0,short y0,short x1,short y1,uint16_t c)
{
	//Wikipedia page in the lab insns
	bool x0_greater = x0 > x1;
	bool y0_greater = x0 > x1;
	uint8_t x_diff = (x0_greater) ? x0 - x1 : x1 - x0;
	uint8_t y_diff = (y0_greater) ? y0 - y1 : y1 - y0;
	if (x_diff > y_diff) {
		if (x0_greater) {
			drawLineLower(x1, y1, x0, y0, c);
		} else {
			drawLineLower(x0, y0, x1, y1, c);
		}
	} else {
		if (y0_greater) {
			drawLineHigher(x1, y1, x0, y0, c);
		} else {
			drawLineHigher(x0, y0, x1, y1, c);
		}
	}
}



/**************************************************************************//**
* @fn			void LCD_drawBlock(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1,uint16_t color)
* @brief		Draw a colored block at coordinates
* @note
*****************************************************************************/
void LCD_drawBlock(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1,uint16_t color)
{
	uint8_t x_max = x0 > x1 ? x0 : x1;
	uint8_t x_min = x0 < x1 ? x0 : x1;
	x_max = x_max > LCD_WIDTH ? LCD_WIDTH : x_max;
	uint8_t y_max = y0 > y1 ? y0 : y1;
	uint8_t y_min = y0 < y1 ? y0 : y1;
	y_max = y_max > LCD_HEIGHT ? LCD_HEIGHT : y_max;
	LCD_setAddr(x_min, y_min, x_max - 1, y_max - 1);
	for (int i = 0; i < (x_max - x_min) * (y_max - y_min); i++) {
		SPI_ControllerTx_16bit(color);
	}
}

/**************************************************************************//**
* @fn			void LCD_setScreen(uint16_t color)
* @brief		Draw the entire screen to a color
* @note
*****************************************************************************/
void LCD_setScreen(uint16_t color) 
{
	LCD_setAddr(0, 0, LCD_WIDTH - 1, LCD_HEIGHT - 1);
	for (int i = 0; i < LCD_SIZE; i++) {
		SPI_ControllerTx_16bit(color);
	}
}

/**************************************************************************//**
* @fn			void LCD_drawString(uint8_t x, uint8_t y, char* str, uint16_t fg, uint16_t bg)
* @brief		Draw a string starting at the point with foreground and background colors
* @note
*****************************************************************************/
void LCD_drawString(uint8_t x, uint8_t y, char* str, uint16_t fg, uint16_t bg)
{
	for (char* s = str; *s != '\0'; s++) {
		LCD_drawChar(x, y, *s, fg, bg);
		x += 7;
	}
}