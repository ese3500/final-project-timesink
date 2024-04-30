/*
 * ADC_lib.c
 *
 * Created: 4/24/2024 4:22:09 PM
 *  Author: ezou6
 */ 

#include "ADC_lib.h"

int muxes[] = {MUX0, MUX1, MUX2, MUX3};

void InitializeADC() {
	cli();
	DDRC &= ~(1<<DDC0);
	DDRC &= ~(1<<DDC1);
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
	ADCSRA |= (1 << ADIE);
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADSC);
	ADCSRA |= (1 << ADATE);
	sei();
}

void FinishADC() {
	cli();
	PRR0 |= (1 << PRADC);
	ADCSRA &= ~(1 << ADIE);
	ADCSRA = 0;
	sei();
}

void ADCSetPin(int pin) {
	for (int i = 0; i < 4; i++) {
		if (pin & (1 << i)) {
			ADMUX |= (1<<muxes[i]);
			} else {
			ADMUX &= ~(1<<muxes[i]);
		}
	}
}