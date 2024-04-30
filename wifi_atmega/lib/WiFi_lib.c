/*
 * WiFi_lib.c
 *	
 * Created: 4/24/2024 4:27:46 PM
 *  Author: ezou6
 */ 

#define FIRST_CHAR 32
#define LAST_CHAR 126
#define WIFI_X 5
#define WIFI_Y 30
#define BACKSPACE_CODE 0
#define SUBMIT_CODE 1
#define getx(GX) ((GX == -1) ? 2 : (50 + (GX * 8)))
#define gety(GY) (1 + (GY * 9))

#include "WiFi_lib.h"

char current_network[50];
int n = 0;
int f = 0;

int x = -1;
int y = 0;

char debug[20];

volatile bool button_pressed;
bool can_accept_button;
volatile int8_t current_pin = 0;
volatile int8_t x_direction; // -1 l, 0 n, 1 r
volatile int8_t y_direction; // -1 u, 0 n, 1 d

char space[6] = "space";
char done[5] = "done";
char back[5] = "back";
char tilde[6] = "tilde";

void InitializeWifi() {
	InitializeADC();
	ADCSetPin(0);
	DDRD &= ~(1 << DDD3);
	PCICR |= (1<<PCIE2);
	PCMSK2 |= (1 << PCINT19);
	//need to set pin change interrupt
}

void get_wifi_network(int network) {
	request_data(network);
	int i = 0;
	char next_char = read_UART_char_fast();
	while (next_char != '\n') {
		current_network[i] = next_char;
		i++;
		next_char = read_UART_char_fast();
	}
	current_network[i] = '\0';
}
void get_num_wifi_networks() {
	//constantly ping while waiting for char
	while(!UART_available()) {
		request_data('s');
		_delay_ms(1000);
	}
	n = (int) read_UART_char();
}

void select_wifi_network() {
	int selected_network = 0;
	can_accept_button = true;
	get_wifi_network(f);
	LCD_drawBlock(WIFI_X, WIFI_Y, LCD_WIDTH, WIFI_Y + 10, BLACK);
	LCD_drawString(WIFI_X, WIFI_Y, current_network, WHITE, BLACK);
	while (1) {
		if (button_pressed) {
			break;
		}
		int old_f = f;
		if (x_direction != 0) {
			f += x_direction;
			if (f < 0) {
				f = 0;
			} else if (f > n - 1) {
				f = n - 1;
			}
			if (old_f != f) {
				x_direction = 0;
				get_wifi_network(f);
				LCD_drawBlock(WIFI_X, WIFI_Y, LCD_WIDTH, WIFI_Y + 10, BLACK);
				LCD_drawString(WIFI_X, WIFI_Y, current_network, WHITE, BLACK);
			}
		}
		_delay_ms(50);
	}
	can_accept_button = false;
	button_pressed = 0;
	request_data((char) f); //lock in selected network
}

char get_character(int grid_x, int grid_y) {
	if (grid_x == -1) {
		switch (grid_y) {
			case 0: //space
				return ' ';
			case 1: //back
				return BACKSPACE_CODE;
			case 2: //submit
				return SUBMIT_CODE;
			case 3: //tilde
				return '~';
			case 4: //exclaim
				return '!';
			case 5: //quotes
				return '"';
			default: //quotes
				return '"';
		}
	}
	return (char) (grid_x + (grid_y) * 13 + 35);
}

void draw_character(int grid_x, int grid_y, bool selected) {
	uint16_t fg = selected ? BLACK : WHITE;
	uint16_t bg = selected ? WHITE : BLACK;
	char c = get_character(grid_x, grid_y);
	if (grid_x == -1) {
		switch (c) {
			case ' ':
				LCD_drawString(getx(grid_x), gety(grid_y), space, fg, bg);
				break;
			case BACKSPACE_CODE:
				LCD_drawString(getx(grid_x), gety(grid_y), back, fg, bg);
				break;
			case SUBMIT_CODE:
				LCD_drawString(getx(grid_x), gety(grid_y), done, fg, bg);
				break;
			default:
				LCD_drawChar(getx(grid_x), gety(grid_y), c, fg, bg);
				break;
		}
	} else {
		LCD_drawChar(getx(grid_x), gety(grid_y), c, fg, bg);
	}
}

void display_all_characters() {
	LCD_setScreen(BLACK);
	draw_character(-1, 0, true);
	for (int j = 1; j < 6; j++) {
		draw_character(-1, j, false);
	}
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 7; j++) {
			draw_character(i, j, false);
		}
	}
}

void enter_password() {
	char* password = malloc(sizeof(char));
	password[0] = '\0';
	int length = 0;
	display_all_characters();
	can_accept_button = true;
	while (1) {
		if (button_pressed) {
			char c = get_character(x, y);
			if (c == BACKSPACE_CODE) {
				length = (length == 0) ? 0 : length - 1;
				password = realloc(password, (length + 1) * sizeof(char));
				password[length] = '\0';
				LCD_drawBlock(getx(0), gety(7), LCD_WIDTH, gety(7) + 10, BLACK);
				LCD_drawString(getx(0), gety(7), password, WHITE, BLACK);
				button_pressed = false;
				continue;
			} else if (c == SUBMIT_CODE) {
				button_pressed = false;
				break;
			}
			length++;
			password = realloc(password, (length + 1) * sizeof(char));
			password[length - 1] = c;
			password[length] = '\0';
			LCD_drawBlock(getx(0), gety(7), LCD_WIDTH, gety(7) + 10, BLACK);
			LCD_drawString(getx(0), gety(7), password, WHITE, BLACK);
			button_pressed = false;
			continue;
		}
		int old_x = x;
		int old_y = y;
		if (x_direction != 0) {
			x += x_direction;
			x = (x < -1) ? -1: x;
			x = (x > 12) ? 12: x;
		}
		if (y_direction != 0) {
			y += y_direction;
			y = (y < 0) ? 0: y;
			if (x == -1) {
				y = (y > 5) ? 5: y; 
			} else {
				y = (y > 6) ? 6: y;
			}
		}
		x_direction = y_direction = 0;
		if (old_x != x || old_y != y) {
			draw_character(old_x, old_y, false); 
			draw_character(x, y, true);
		}
		_delay_ms(100);
	}
	can_accept_button = false;
	button_pressed = 0;
	UART_put_string(password);
	free(password);
}

void set_up_wifi() {
	get_num_wifi_networks();
	InitializeWifi();
	char status = 'F';
	while (status == 'F') {
		select_wifi_network();
		enter_password();
		status = read_UART_char();
		LCD_drawChar(100, 100, status, WHITE, BLACK);
	}
	FinishADC();
	PCICR &= ~(1<<PCIE2);
	LCD_setScreen(BLACK);
}

ISR(ADC_vect) {
	int direction = 0;
	if (ADC > 676) {
		direction = 1;
	} else if (ADC < 333) {
		direction = -1;
	}
	if (current_pin == 0) {
		y_direction = direction;
	} else {
		x_direction = direction;
	}
	current_pin ^= 1;
	ADCSetPin(current_pin);
}

ISR(PCINT2_vect) { // record button press
	if (PIND & (1 << PIND3)) {
		button_pressed = can_accept_button;
	}
}