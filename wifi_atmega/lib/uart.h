/*
 * uart.h
 * Adapted from code used in labs
 * Created: 4/24/2024 4:31:02 PM
 *  Author: ezou6
 */ 
#ifndef F_CPU
	#define F_CPU 16000000UL
#endif
#define BAUD_RATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <util/delay.h>
#include "LCD_GFX.h"
#include "ST7735.h"

#ifndef UART_H_
#define UART_H_

void InitializeUART();

void request_data(char code);

bool UART_available();

char read_UART_char();

char read_UART_char_fast();

void clear_UART_buffer();

char* read_string();

void UART_put_string(char* s);

#endif /* UART_H_ */