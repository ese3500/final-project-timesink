/*
 * uart.c
 *	Adapted from code used in Labs
 * Created: 4/24/2024 4:30:48 PM
 *  Author: ezou6
 */ 
#include "uart.h"

void InitializeUART() {
	UBRR0H = (unsigned char) (BAUD_PRESCALER >> 8); // speed high bits
	UBRR0L = (unsigned char) (BAUD_PRESCALER); // ^ but low bits
	UCSR0C |= (1 << USBS0); // 2 stop bits
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00); // 8 bit char
	UCSR0B = (1 << RXEN0) | (1 << TXEN0); // send and receive
}

void clear_UART_buffer() {
	while (UCSR0A & (1<<RXC0)) {
		char stuff = UDR0;
	}
}

bool UART_available() {
	return (UCSR0A & (1<<RXC0));
}

char read_UART_char() {
	uint8_t counter = 0;
	while(!(UCSR0A & (1<<RXC0)) && counter <= 120) {
		_delay_ms(1000);
		counter++; //2min timeout
	};
	return UDR0;
}

char read_UART_char_fast() {
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}

char* read_string(char* destination) {
	char str[100]; //max length is 30
	char c;
	uint8_t i = 0;
	do {
		while (!(UCSR0A & (1<<RXC0)));
		c = UDR0;
		str[i] = c;
		i++;
	} while (c!='\n');
	str[i] = '\0';
	char* dest = (char*) malloc((strlen(str) + 1) * sizeof(char));
	strcpy(dest, str);
	return dest;
}

void request_data(char code) {
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = code;
}

void UART_put_string(char* s) {
	while(*s != 0x00) {
		while(!(UCSR0A & (1 << UDRE0)));
		UDR0 = *s;
		s++;
	}
}