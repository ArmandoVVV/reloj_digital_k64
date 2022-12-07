/*
 * state_machine.c
 *brief:
 *		This source file is a button sensitive state machine, it can alternate
 *		between the clock, the alarm and the chronometer.
 *  Created on: Oct 1, 2022
 *      Author: Armando Cabrales
 */

#include "state_machine.h"
#include "fsl_gpio.h"
#include "config.h"
#include "clock.h"
#include "chronometer.h"
#include "nvic.h"
#include "alarm.h"
#include "dac.h"

static State_name_t g_current_state = CLOCK;
static uint8_t g_time_stopwatch = 0;

State_name_t get_current_state(){
	return g_current_state;
}

uint8_t get_time_stopwatch(void){
	return g_time_stopwatch;
}

void set_time_stopwatch(uint8_t value){
	g_time_stopwatch = value;
}

const State_t FSM_Moore[3]=
{		//  state - function to do     -      possible next states
		{ CLOCK,		show_clock,			{ CLOCK, CHRONOMETER, ALARM, CLOCK}},
		{ CHRONOMETER,	show_chronometer,	{ CHRONOMETER, CLOCK, CHRONOMETER, CHRONOMETER}},
		{ ALARM,		show_alarm,			{ CLOCK, CLOCK, ALARM, CLOCK}}
};

void state_machine(void){
	static uint8_t total_input = 0;
	static uint8_t time_alarm = 0;

	check_buttons();

	if(ENABLE == get_alarm_status()){
		set_clock_total_value();
		// si la hora coincide con el valor puesto en la alarma
		if(get_clock_total_value() == get_alarm_total_value()){
			// activa el callback del pit1 generando la señal senoidal
			NVIC_set_basepri_threshold(PRIORITY_10);
		}
	}

	time_alarm = !(GPIO_PinRead(ALARM_GPIO, ALARM_PIN));

	time_alarm = time_alarm << 1;
	total_input = time_alarm | get_time_stopwatch();

	g_current_state = FSM_Moore[get_current_state()].next[total_input];
	FSM_Moore[get_current_state()].fptrPort();

	set_time_stopwatch(0);
	time_alarm = 0;
}

void check_buttons(void){
	if(CHRONOMETER == get_current_state()){
		check_chronometer_buttons();
	}

	// if ALARM ON button is pressed
	if(!(GPIO_PinRead(SW3_GPIO, SW3_PIN))){
		alarm_on();
		set_alarm_total_value();
	}

	// if CLEAR button is pressed
	if(!(GPIO_PinRead(CLEAR_GPIO, CLEAR_PIN))){
		alarm_off();
		// se desactiva el pi1 que genera la señal
		NVIC_set_basepri_threshold(PRIORITY_8);
		DAC_noSignal();
	}
}
