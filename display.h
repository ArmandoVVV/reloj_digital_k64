/*
 * display.h
 *
 * 		\brief
 * 			This source manages the different displays in our circuit.
 * 			it can show any number, it can turn on/off any display and segment
 * 			and it has a control function to show the given number.
 *
 *  Created on: 28 sep 2022
 *	Author: Laura García
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>

void displays_off(void);
void display_clear(void);
void display_show_0(void);
void display_show_1(void);
void display_show_2(void);
void display_show_3(void);
void display_show_4(void);
void display_show_5(void);
void display_show_6(void);
void display_show_7(void);
void display_show_8(void);
void display_show_9(void);
void display_show_error(void);

void turn_off_displays(void);
void display_5_on(void);
void display_4_on(void);
void display_3_on(void);
void display_2_on(void);
void display_1_on(void);
void display_0_on(void);

void display_ctrl(uint8_t);



#endif /* DISPLAY_H_ */
