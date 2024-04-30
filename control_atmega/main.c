#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define LED_DURATION 20
#define MOTOR_DURATION 3
#define BAUD_RATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE *16UL)))-1)

char String[25]; //buffer
int muxes[] = {MUX0, MUX1, MUX2, MUX3};
	
volatile bool led_on = false;
volatile int led_counter = 0;

volatile bool motor_on = false;
volatile int motor_counter = 0;

void Initialize() {
	cli();
	DDRB |= (1<<DDB2); // LED
	DDRD |= (1<<DDD5); // Motor
	
	DDRC &= ~(1<<DDC0); // Motion
	DDRC &= ~(1<<DDC1); // External Brightness
	DDRC &= ~(1<<DDC2); // Soap Trigger
	
	// 1024 prescaler: 
	TCCR0B |= (1<< CS00);
	TCCR0B &= ~(1<< CS01);
	TCCR0B |= (1<<CS02);
	
	TCCR0A |= (1<<WGM00);
	TCCR0A &= ~(1<<WGM01);
	TCCR0B |= (1<<WGM02); 
	
	TCCR0A &= ~(1 << COM1A0);
	TCCR0A &= ~(1 << COM1A0);
	TCCR0A &= ~(1 << COM1B0);
	TCCR0A &= ~(1 << COM1B0);
	TIMSK0 |= (1 << OCIE0A);
	 
	OCR0A = 125; 
	
	// ADC
	PRR0 &= ~(1 << PRADC);
	ADMUX |= (1 << REFS0);
	ADMUX &= ~(1 << REFS1);
	
	ADCSRA |= (1 << ADPS0);
	ADCSRA |= (1 << ADPS1);
	ADCSRA |= (1 << ADPS2);
		
	ADCSRB &= ~(1 << ADTS0);
	ADCSRB &= ~(1 << ADTS1);
	ADCSRB &= ~(1 << ADTS2);
	DIDR0 |= (1 << ADC0D);
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADSC);
	ADCSRA |= (1 << ADATE);
	sei();
}

uint16_t ADCReadPin(int pin) {
	for (int i = 0; i < 4; i++) {
		if (pin & (1 << i)) {
			ADMUX |= (1<<muxes[i]);
		} else {
			ADMUX &= ~(1<<muxes[i]);
		}
	}
	_delay_ms(10);
	return ADC;
}


void trigger_led(int motion, int ext_b) {
	if (motion > 10 && ext_b < 300) {
		PORTB |= (1 << PORTB2);
		led_on = true;
	}
}

void trigger_motor(int trigger) {
	if (trigger < 50) {
		PORTD |= (1 << PORTD5);
		motor_on = true;
	}
}


int main(void) {
	Initialize();
	UART_init(BAUD_PRESCALER);
	while (1) {
		int motion = (int) ADCReadPin(0);
		int ext_b = (int) ADCReadPin(1);
		int pin2 = (int) ADCReadPin(2);
		char buffer[20];
		sprintf(buffer, "%d %d\n", motion, ext_b);
		UART_putstring(buffer);
		if (!led_on) {
			trigger_led(motion, ext_b); //checks
		}
		if (!motor_on) {
			trigger_motor(pin2);
		}
		_delay_ms(50);
	}
}

ISR(TIMER0_COMPA_vect) {
	if (led_on) {
		led_counter++;
	}
	if (motor_on) {
		motor_counter++;
	}
	if (led_counter == 125 * LED_DURATION / 2) {
		PORTB &= ~(1 << PORTB2);
		led_on = false;
		led_counter = 0;
	}
	if (motor_counter == 125 * MOTOR_DURATION / 2) {
		PORTD &= ~(1 << PORTD5);
		motor_on = false;
		motor_counter = 0;
	}
}

