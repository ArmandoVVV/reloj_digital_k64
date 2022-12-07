/*
 * callback_manager.c
 *
 *  Created on: Oct 1, 2022
 *      Author: Armando Cabrales
 *      brief:
 *      	this source file helps with the callback managment, three callbacks
 *      	call these functions to do their respective work.
 *      	These functions are only accessed by callbacks.
 */

#include "callback_manager.h"
#include "chronometer.h"
#include "clock.h"
#include "fsl_gpio.h"
#include "alarm.h"
#include "state_machine.h"
#include "watchdog.h"

void callback_add_msec(uint32_t pit0){
	static uint16_t total_msec = 0;
	if(ENABLE == get_chronometer_status()){
		set_msec_unit_value_chr(get_msec_unit_value_chr() + 1);
	}

	if(100 <= total_msec){
		// refrescar el watchdowg
		refresh_watchdog();

		total_msec = 0;
		set_sec_unit_value(get_sec_unit_value() + 1);
		toggle_alarm_sound();
	}

	total_msec++;
}

void callback_time_stopwatch(uint32_t time_stopwatch){
	if(!GPIO_PinRead(STOPWATCH_GPIO, STOPWATCH_PIN)){
		set_time_stopwatch(1);
		state_machine();
	}
}

void change_time(uint32_t hour_or_min){
	// if config_time is pressed
	if(!GPIO_PinRead(CONFIG_TIME_GPIO, CONFIG_TIME_PIN)){
		// if hour_start is pressed
		if(!GPIO_PinRead(HOUR_START_GPIO, HOUR_START_PIN)){
			hour_plus_one();
		}
		// if min_stop is pressed
		else if(!GPIO_PinRead(MIN_STOP_GPIO, MIN_STOP_PIN)){
			min_plus_one();
		}
	}
	// if alarm is pressed
	if(!GPIO_PinRead(ALARM_GPIO, ALARM_PIN)){
		// if hour_start is pressed
		if(!GPIO_PinRead(HOUR_START_GPIO, HOUR_START_PIN)){
			hour_plus_one_alm();
			// actualiza el valor de la alarma en caso de que se cambie el valor de la alarma
			set_alarm_total_value();
		}
		// if min_stop is pressed
		else if(!GPIO_PinRead(MIN_STOP_GPIO, MIN_STOP_PIN)){
			min_plus_one_alm();
			// actualiza el valor de la alarma en caso de que se cambie el valor de la alarma
			set_alarm_total_value();
		}
	}
}

