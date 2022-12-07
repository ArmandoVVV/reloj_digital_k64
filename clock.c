/*
 * clock.c
 * brief:
 * 		This source file is an abstraction of a clock, it has its own values
 *		this clock has a maximum range of 23:59:59, after this value it resets to
 *		00:00:00
 *		The clock uses the display to show its values.
 *		It has a total_value variable to compare with alarm.
 *
 *  Created on: Sep 29, 2022
 *      Author: armando
 */

#include "clock.h"
#include "config.h"
#include "fsl_gpio.h"
#include "display.h"

static uint8_t g_hour_ten_value = 1;
static uint8_t g_hour_unit_value = 2;

static uint8_t g_min_ten_value = 3;
static uint8_t g_min_unit_value = 5;

static uint8_t g_sec_ten_value = 0;
static uint8_t g_sec_unit_value = 0;

static uint16_t g_clock_total_value = 0;

// getters
uint8_t get_hour_ten_value(void){
	return g_hour_ten_value;
}

uint8_t get_hour_unit_value(void){
	return g_hour_unit_value;
}

uint8_t get_min_ten_value(void){
	return g_min_ten_value;
}

uint8_t get_min_unit_value(void){
	return g_min_unit_value;
}

uint8_t get_sec_ten_value(void){
	return g_sec_ten_value;
}

uint8_t get_sec_unit_value(void){
	return g_sec_unit_value;
}

uint16_t get_clock_total_value(void){
	return g_clock_total_value;
}


// setters
void set_hour_ten_value(uint8_t new_value){
	g_hour_ten_value = new_value;
}

void set_hour_unit_value(uint8_t new_value){
	if((HOUR_UNIT_RESET_VALUE < new_value) && (HOUR_TEN_MAX_VALUE == get_hour_ten_value())){
		reset_clock();
	}
	else{
		if(HOUR_UNIT_MAX_VALUE < new_value){
			g_hour_unit_value = 0;
			set_hour_ten_value(get_hour_ten_value() + 1);
		}
		else{
			g_hour_unit_value = new_value;
		}
	}

}

void set_min_ten_value(uint8_t new_value){
	if(MIN_TEN_MAX_VALUE < new_value){
		g_min_ten_value = 0;
		set_hour_unit_value(get_hour_unit_value() + 1);
	}
	else{
		g_min_ten_value = new_value;
	}
}

void set_min_unit_value(uint8_t new_value){
	if(MIN_UNIT_MAX_VALUE < new_value){
		g_min_unit_value = 0;
		set_min_ten_value(get_min_ten_value() + 1);
	}
	else{
		g_min_unit_value = new_value;
	}
}

void set_sec_ten_value(uint8_t new_value){
	if(SEC_TEN_MAX_VALUE < new_value){
		g_sec_ten_value = 0;
		set_min_unit_value(get_min_unit_value() + 1);
	}
	else{
		g_sec_ten_value = new_value;
	}
}

void set_sec_unit_value(uint8_t new_value){
	if(SEC_UNIT_MAX_VALUE < new_value){
		g_sec_unit_value = 0;
		set_sec_ten_value(get_sec_ten_value() + 1);
	}
	else{
		g_sec_unit_value = new_value;
	}
}

void set_clock_total_value(void){
	g_clock_total_value = get_hour_ten_value() * 1000;
	g_clock_total_value = g_clock_total_value + (get_hour_unit_value() * 100);
	g_clock_total_value = g_clock_total_value + (get_min_ten_value() * 10);
	g_clock_total_value = g_clock_total_value + get_min_unit_value();
}


void show_clock(void){
	displays_off();

	display_ctrl(get_sec_unit_value());
	display_0_on();

	displays_off();

	display_ctrl(get_sec_ten_value());
	display_1_on();

	displays_off();

	display_ctrl(get_min_unit_value());
	display_2_on();

	displays_off();

	display_ctrl(get_min_ten_value());
	display_3_on();

	displays_off();

	display_ctrl(get_hour_unit_value());
	display_4_on();

	displays_off();

	display_ctrl(get_hour_ten_value());
	display_5_on();
}

void add_one_sec(uint32_t pit1){
	set_sec_unit_value(get_sec_unit_value() + 1);
}

void hour_plus_one(void){
	// if hour surpass its maximum value
	if(2 == get_hour_ten_value() && 3 == get_hour_unit_value()){
		set_hour_unit_value(0);
		set_hour_ten_value(0);
	}
	else{
		set_hour_unit_value(get_hour_unit_value() + 1);
	}
}

void min_plus_one(void){
	// if minutes surpass its maximum value
	if(5 == get_min_ten_value() && 9 == get_min_unit_value()){
		set_min_unit_value(0);
		set_min_ten_value(0);
	}
	else{
		set_min_unit_value(get_min_unit_value() + 1);
	}
}

void reset_clock(void){
	set_sec_unit_value(0);
	set_sec_ten_value(0);
	set_min_unit_value(0);
	set_min_ten_value(0);
	set_hour_unit_value(0);
	set_hour_ten_value(0);
}

