/*
 * clock.h
 * brief:
 * 		This source file is an abstraction of a chronometer or stopwatch, it has its own values
 *		it can be stopped and started by different buttons and uses the display to show its values
 *
 *  Created on: Oct 1, 2022
 *      Author: armando Cabrales
 */

#include <stdint.h>
#include "config.h"

#ifndef CHRONOMETER_H_
#define CHRONOMETER_H_

#define CHR_MSEC_UNIT_MAX_VALUE 9
#define CHR_MSEC_TEN_MAX_VALUE 9
#define CHR_SEC_UNIT_MAX_VALUE 9
#define CHR_SEC_TEN_MAX_VALUE 5
#define CHR_MIN_UNIT_MAX_VALUE 9
#define CHR_MIN_TEN_MAX_VALUE 9

void reset_chronometer(void);
void add_one_msec(void);
void show_chronometer(void);

void stop_chronometer(void);
void start_chronometer(void);
void check_chronometer_buttons(void);

uint8_t get_msec_unit_value_chr(void);
uint8_t get_chronometer_status(void);

void set_msec_unit_value_chr(uint8_t new_value);
void set_chronometer_status(device_status_t status);

#endif /* CHRONOMETER_H_ */
