/*
 * callback_manager.h
 *
 *  Created on: Oct 1, 2022
 *      Author: Armando Cabrales
 *      brief:
 *      	this source file helps with the callback managment, three callbacks
 *      	call these functions to do their respective work.
 *      	These functions are only accessed by callbacks.
 */

#ifndef CALLBACK_MANAGER_H_
#define CALLBACK_MANAGER_H_

#include <stdint.h>
#include "config.h"

uint8_t get_chronometer_status(void);
void set_chronometer_status(device_status_t status);

void callback_add_msec(uint32_t pit0);
void alarm_pressed(uint32_t config_time);
void change_time(uint32_t hour_or_min);

void callback_time_stopwatch(uint32_t time_stopwatch);

#endif /* CALLBACK_MANAGER_H_ */
