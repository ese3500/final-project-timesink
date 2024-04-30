/*
 * WiFi_lib.h
 *  Wifi driver designed to handle wifi setup process on arduino
 * Created: 4/24/2024 4:27:20 PM
 *  Author: ezou6
 */ 

#define F_CPU 16000000UL

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "uart.h"
#include "ADC_lib.h"

#ifndef WIFI_LIB_H_
#define WIFI_LIB_H_

void set_up_wifi();

#endif /* WIFI_LIB_H_ */