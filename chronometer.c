/*
 * clock.c
 * brief:
 * 		This source file is an abstraction of a chronometer or stopwatch, it has its own values
 *		it can be stopped and started by different buttons and uses the display to show its values
 *
 *  Created on: Oct 1, 2022
 *      Author: armando Cabrales
 */

#include "chronometer.h"
#include "fsl_gpio.h"
#include "display.h"
#include "nvic.h"

static uint8_t g_min_ten_value_chr = 0;
static uint8_t g_min_unit_value_chr = 0;

static uint8_t g_sec_ten_value_chr = 0;
static uint8_t g_sec_unit_value_chr = 0;

static uint8_t g_msec_ten_value_chr = 0;
static uint8_t g_msec_unit_value_chr = 0;

static device_status_t g_chronometer_status = DISABLE;

// getters
uint8_t get_min_ten_value_chr(void){
	return g_min_ten_value_chr;
}

uint8_t get_min_unit_value_chr(void){
	return g_min_unit_value_chr;
}

uint8_t get_sec_ten_value_chr(void){
	return g_sec_ten_value_chr;
}

uint8_t get_sec_unit_value_chr(void){
	return g_sec_unit_value_chr;
}

uint8_t get_msec_ten_value_chr(void){
	return g_msec_ten_value_chr;
}

uint8_t get_msec_unit_value_chr(void){
	return g_msec_unit_value_chr;
}

uint8_t get_chronometer_status(void){
	return g_chronometer_status;
}

// setters
void set_min_ten_value_chr(uint8_t new_value){
	g_min_ten_value_chr = new_value;
}

void set_min_unit_value_chr(uint8_t new_value){
	if(CHR_MIN_UNIT_MAX_VALUE < new_value && CHR_MIN_TEN_MAX_VALUE == get_min_ten_value_chr()){
		reset_chronometer();
	}
	else{
		if(CHR_MIN_UNIT_MAX_VALUE < new_value){
			g_min_unit_value_chr = 0;
			set_min_ten_value_chr(get_min_ten_value_chr() + 1);
		}
		else{
			g_min_unit_value_chr = new_value;
		}
	}

}

void set_sec_ten_value_chr(uint8_t new_value){
	if(CHR_SEC_TEN_MAX_VALUE < new_value){
		g_sec_ten_value_chr = 0;
		set_min_unit_value_chr(get_min_unit_value_chr() + 1);
	}
	else{
		g_sec_ten_value_chr = new_value;
	}
}

void set_sec_unit_value_chr(uint8_t new_value){
	if(CHR_SEC_UNIT_MAX_VALUE < new_value){
		g_sec_unit_value_chr = 0;
		set_sec_ten_value_chr(get_sec_ten_value_chr() + 1);
	}
	else{
		g_sec_unit_value_chr = new_value;
	}
}

void set_msec_ten_value_chr(uint8_t new_value){
	if(CHR_MSEC_TEN_MAX_VALUE < new_value){
		g_msec_ten_value_chr = 0;
		set_sec_unit_value_chr(get_sec_unit_value_chr() + 1);
	}
	else{
		g_msec_ten_value_chr = new_value;
	}
}

void set_msec_unit_value_chr(uint8_t new_value){
	if(CHR_MSEC_UNIT_MAX_VALUE < new_value){
		g_msec_unit_value_chr = 0;
		set_msec_ten_value_chr(get_msec_ten_value_chr() + 1);
	}
	else{
		g_msec_unit_value_chr = new_value;
	}
}

void set_chronometer_status(device_status_t status){
	g_chronometer_status = status;
}


void show_chronometer(void){
	displays_off();

	display_ctrl(get_msec_unit_value_chr());
	display_0_on();

	displays_off();

	display_ctrl(get_msec_ten_value_chr());
	display_1_on();

	displays_off();

	display_ctrl(get_sec_unit_value_chr());
	display_2_on();

	displays_off();

	display_ctrl(get_sec_ten_value_chr());
	display_3_on();

	displays_off();

	display_ctrl(get_min_unit_value_chr());
	display_4_on();

	displays_off();

	display_ctrl(get_min_ten_value_chr());
	display_5_on();
}

void add_one_msec(void){
	set_msec_unit_value_chr(get_msec_unit_value_chr() + 1);
}

void reset_chronometer(void){
	set_msec_unit_value_chr(0);
	set_msec_ten_value_chr(0);
	set_sec_unit_value_chr(0);
	set_sec_ten_value_chr(0);
	set_min_unit_value_chr(0);
	set_min_ten_value_chr(0);
}

void stop_chronometer(void){
	set_chronometer_status(DISABLE);
}

void start_chronometer(void){
	set_chronometer_status(ENABLE);
}

void check_chronometer_buttons(void){
	if(!(GPIO_PinRead(MIN_STOP_GPIO, MIN_STOP_PIN))){
		stop_chronometer();
	}
	else if(!(GPIO_PinRead(HOUR_START_GPIO, HOUR_START_PIN))){
		start_chronometer();
	}
	else if(!(GPIO_PinRead(CLEAR_GPIO, CLEAR_PIN))){
		reset_chronometer();
	}
}
