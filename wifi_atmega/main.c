/*
 * main.c
 *
 * Created: 4/11/2024 12:20:06 PM
 *  Author: ezou6
 */ 
#ifndef F_CPU
	#define F_CPU 16000000UL
#endif

#include "avr/io.h"
#include "avr/interrupt.h"
#include "stdbool.h"
#include "lib/uart.h"
#include "lib/WiFi_lib.h"
#include "lib/Display_lib.h"

volatile int hours = 0;
volatile int minutes = 0;
volatile int seconds = 0;
volatile bool should_refresh = false;
volatile bool should_redraw = false;

char buffer[50];

void Initialize();

void refresh_all();

void draw_time();

int main(void) {
	Initialize();
	refresh_all();
    while(1) {
		if (should_redraw) {
			should_redraw = false;
			draw_time(&hours, &minutes, &seconds);
		}
		if (!should_refresh) { //update time
			continue;
		}
		refresh_all();
    }
}

void Initialize() {
	cli();
	InitializeUART();
	lcd_init();
	LCD_setScreen(BLACK);
	
	sei();
	set_up_wifi();
	cli();
	
	TCCR1B &= ~(1 << CS10);
	TCCR1B &= ~(1 << CS11);
	TCCR1B |= (1 << CS12);
	
	TCCR1A &= ~(1 << COM1A0);
	TCCR1A &= ~(1 << COM1A0);
	
	TCCR1A &= ~(1 << COM1B0);
	TCCR1A &= ~(1 << COM1B0);

	// interrupt settings
	TIMSK1 |= (1 << OCIE1A);
	OCR1A = 15625;
	sei();
}

void start_internal_clock() {
	TIMSK1 |= (1 << OCIE1A);
	TCNT1 = 0;
}

void freeze_internal_clock() {
	TIMSK1 &= ~(1 << OCIE1A);
}

void refresh_all() {
	freeze_internal_clock();
	clear_UART_buffer();
	update_weather();
	should_refresh = 0;
	update_time(&hours, &minutes, &seconds);
	start_internal_clock();
}

ISR (TIMER1_COMPA_vect) { //time it out
	seconds = (seconds + 1) % 60;
	should_redraw = true;
	if (seconds == 0) {
		minutes = (minutes + 1) % 60;
		if (minutes == 0) {
			hours = (hours + 1) % 24;
			should_refresh = true;
		}
	}
}