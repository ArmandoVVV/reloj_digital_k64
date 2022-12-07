/*
 * alarm.c
 * \brief
 *		This source file is an abstraction of an alarm, it has its own values
 *		it can make sound with the DAC and uses the display to show its values.
 *
 *
 *  Created on: 30 sep 2022
 *		Author: Laura García
 */

#include "fsl_gpio.h"
#include "alarm.h"
#include "DAC.h"
#include "display.h"
#include "callback_manager.h"
#include "nvic.h"

static uint8_t g_hour_ten_value_alm = 1;
static uint8_t g_hour_unit_value_alm = 2;

static uint8_t g_min_ten_value_alm = 3;
static uint8_t g_min_unit_value_alm = 6;

static uint16_t g_alarm_total_value = 0;

static device_status_t g_silent_period = DISABLE;
static device_status_t g_alarm_status = DISABLE;

// getters
uint8_t get_hour_ten_value_alm(void){
	return g_hour_ten_value_alm;
}

uint8_t get_hour_unit_value_alm(void){
	return g_hour_unit_value_alm;
}

uint8_t get_min_ten_value_alm(void){
	return g_min_ten_value_alm;
}

uint8_t get_min_unit_value_alm(void){
	return g_min_unit_value_alm;
}

uint16_t get_alarm_total_value(void){
	return g_alarm_total_value;
}

device_status_t get_silent_period(void){
	return g_silent_period;
}

device_status_t get_alarm_status(void){
	return g_alarm_status;
}


// setters
void set_hour_ten_value_alm(uint8_t new_value){
	g_hour_ten_value_alm = new_value;
}

void set_hour_unit_value_alm(uint8_t new_value){
	if(HOUR_UNIT_RESET_VALUE < new_value && HOUR_TEN_MAX_VALUE == get_hour_ten_value_alm()){
		set_hour_ten_value_alm(0);
		set_hour_unit_value_alm(0);
	}
	else{
		if(HOUR_UNIT_MAX_VALUE < new_value){
			g_hour_unit_value_alm = 0;
			set_hour_ten_value_alm(get_hour_ten_value_alm() + 1);
		}
		else{
			g_hour_unit_value_alm = new_value;
		}
	}

}

void set_min_ten_value_alm(uint8_t new_value){
	if(MIN_TEN_MAX_VALUE < new_value){
		g_min_ten_value_alm = 0;
		set_min_unit_value_alm(0);

	}
	else{
		g_min_ten_value_alm = new_value;
	}
}

void set_min_unit_value_alm(uint8_t new_value){
	if(MIN_UNIT_MAX_VALUE < new_value){
		g_min_unit_value_alm = 0;
		set_min_ten_value_alm(get_min_ten_value_alm() + 1);
	}
	else{
		g_min_unit_value_alm = new_value;
	}
}

void set_alarm_total_value(void){
	g_alarm_total_value = get_hour_ten_value_alm() * 1000;
	g_alarm_total_value = g_alarm_total_value + (get_hour_unit_value_alm() * 100);
	g_alarm_total_value = g_alarm_total_value + (get_min_ten_value_alm() * 10);
	g_alarm_total_value = g_alarm_total_value + get_min_unit_value_alm();
}

void set_silence_period(device_status_t status){
	g_silent_period = status;
}

void set_alarm_status(device_status_t status){
	g_alarm_status = status;
}

void alarm_sound(uint32_t pit_1){
	static uint16_t current_sin_position = 0;
	static uint16_t sin_array[10] = {0, 1024, 2048, 3251, 3673, 4095, 3673, 3251, 2048, 1024};

	GPIO_PortClear(BLUE_LED_GPIO, BLUE_LED_MASK);

	static uint8_t sin_size = (sizeof(sin_array) / sizeof(uint16_t)) - 1;

	if (ENABLE == get_silent_period()){
		DAC_noSignal();
	}
	else{
		DAC_sinusoidal(sin_array[current_sin_position]);
		if(sin_size <= current_sin_position){
			current_sin_position = 0;
		}
		else{
			current_sin_position++;
		}
	}
}


void show_alarm(void){
	displays_off();

	display_ctrl(get_min_unit_value_alm());
	display_2_on();

	displays_off();

	display_ctrl(get_min_ten_value_alm());
	display_3_on();

	displays_off();

	display_ctrl(get_hour_unit_value_alm());
	display_4_on();

	displays_off();

	display_ctrl(get_hour_ten_value_alm());
	display_5_on();
}


void hour_plus_one_alm(void){
	// if hour surpass its maximum value
	if(2 == get_hour_ten_value_alm() && 3 == get_hour_unit_value_alm()){
		set_hour_unit_value_alm(0);
		set_hour_ten_value_alm(0);
	}
	else{
		set_hour_unit_value_alm(get_hour_unit_value_alm() + 1);
	}
}

void min_plus_one_alm(void){
	// if minutes surpass its maximum value
	if(5 == get_min_ten_value_alm() && 9 == get_min_unit_value_alm()){
		set_min_unit_value_alm(0);
		set_min_ten_value_alm(0);
	}
	else{
		set_min_unit_value_alm(get_min_unit_value_alm() + 1);
	}
}

void alarm_on(void){
	GPIO_PortClear(RED_LED_GPIO, RED_LED_MASK);
	set_alarm_status(ENABLE);
}

void alarm_off(void){
	GPIO_PortSet(RED_LED_GPIO, RED_LED_MASK);
	GPIO_PortSet(BLUE_LED_GPIO, BLUE_LED_MASK);
	set_alarm_status(DISABLE);
}

void toggle_alarm_sound(void){
	if(ENABLE == get_silent_period()){
		set_silence_period(DISABLE);
	}
	else{ 	// silence_period == DISABLE
		set_silence_period(ENABLE);
	}
}

