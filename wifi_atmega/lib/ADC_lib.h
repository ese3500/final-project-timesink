/*
 * ADC_lib.h
 *
 * Created: 4/24/2024 4:21:23 PM
 *  Author: ezou6
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef ADC_LIB_H_
#define ADC_LIB_H_

void InitializeADC();
void FinishADC();
void ADCSetPin(int pin);

#endif /* ADC_LIB_H_ */