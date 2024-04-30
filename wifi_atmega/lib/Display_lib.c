/*
 * Display_lib.c
 *
 * Created: 4/24/2024 4:35:02 PM
 *  Author: ezou6
 */ 
#include "Display_lib.h"

char buffer[20];

void draw_time(volatile int* hours, volatile int* minutes, volatile int* seconds) {
	sprintf(buffer, "%02d:%02d:%02d", *hours, *minutes, *seconds);
	LCD_drawString(X_OFFSET, Y_OFFSET + 20, buffer, WHITE, BLACK);
}

void update_time(volatile int* hours, volatile int* minutes, volatile int* seconds) {
	request_data('t');
	char val;
	val = read_UART_char(); //wait until ready
	if (val == 'F') {
		sprintf(buffer, "FAIL TIME SYNC");
		LCD_drawString(X_OFFSET, E_OFFSET, buffer, RED, BLACK);
		return;
	}
	LCD_drawBlock(X_OFFSET, E_OFFSET, LCD_WIDTH, E_OFFSET + 10, BLACK);
	*hours = (int) val;
	val = read_UART_char();
	*minutes = (int) val;
	val = read_UART_char();
	*seconds = (int) val;
	draw_time(hours, minutes, seconds);
}

void update_weather() {
	signed char temp_char;
	char weather_char;
	request_data('w');
	temp_char = read_UART_char();
	
	if (temp_char == 'F') {
		sprintf(buffer, "FAIL WEATHER GET");
		LCD_drawString(X_OFFSET, E_OFFSET + 10, buffer, RED, BLACK);
		return;
	}
	LCD_drawBlock(X_OFFSET, E_OFFSET + 10, LCD_WIDTH, E_OFFSET + 20, BLACK);
	
	weather_char = read_UART_char();
	
	LCD_drawBlock(X_OFFSET, Y_OFFSET + 40, LCD_WIDTH, E_OFFSET, BLACK);
	
	sprintf(buffer, "%i F", (int) temp_char);
	LCD_drawString(X_OFFSET, Y_OFFSET + 50, buffer, WHITE, BLACK);
	
	switch (weather_char) {
		case 't':
		sprintf(buffer, "Thunder");
		break;
		case 'r':
		sprintf(buffer, "Rainy");
		break;
		case 's':
		sprintf(buffer, "Snowy");
		break;
		case 'a':
		sprintf(buffer, "Air Quality");
		break;
		case 'c':
		sprintf(buffer, "Clear");
		break;
		case 'p':
		sprintf(buffer, "Partly Cloudy");
		break;
		case 'l':
		sprintf(buffer, "Cloudy");
		break;
	}
	LCD_drawString(X_OFFSET, Y_OFFSET + 40, buffer, WHITE, BLACK);
}