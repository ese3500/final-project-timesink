/*
 * Display_lib.h
 *
 * Created: 4/24/2024 4:34:50 PM
 *  Author: ezou6
 */ 

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "uart.h"
#include "LCD_GFX.h"
#include "ST7735.h"

#define X_OFFSET 40
#define Y_OFFSET 30
#define E_OFFSET 90

#ifndef DISPLAY_LIB_H_
#define DISPLAY_LIB_H_

void draw_time(volatile int* hours, volatile int* minutes, volatile int* seconds);
void update_time(volatile int* hours, volatile int* minutes, volatile int* seconds);
void update_weather();

#endif /* DISPLAY_LIB_H_ */