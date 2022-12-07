/*
 * display.c
 *
 * 		\brief
 * 			This source manages the different displays in our circuit.
 * 			it can show any number, it can turn on/off any display and segment
 * 			and it has a control function to show the given number.
 *
 *  Created on: 28 sep 2022
 *	Author: Laura García
 */

#include <display.h>
#include "fsl_gpio.h"
#include "config.h"

void display_clear(void)
{
	GPIO_PortSet(SEGMENT_A_GPIO, SEGMENT_A_MASK);
	GPIO_PortSet(SEGMENT_B_GPIO, SEGMENT_B_MASK);
	GPIO_PortSet(SEGMENT_C_GPIO, SEGMENT_C_MASK);
	GPIO_PortSet(SEGMENT_D_GPIO, SEGMENT_D_MASK);
	GPIO_PortSet(SEGMENT_E_GPIO, SEGMENT_E_MASK);
	GPIO_PortSet(SEGMENT_F_GPIO, SEGMENT_F_MASK);
	GPIO_PortSet(SEGMENT_G_GPIO, SEGMENT_G_MASK);
}

void display_show_0(void)
{
	display_clear();
	GPIO_PortClear(SEGMENT_A_GPIO, SEGMENT_A_MASK);
	GPIO_PortClear(SEGMENT_B_GPIO, SEGMENT_B_MASK);
	GPIO_PortClear(SEGMENT_C_GPIO, SEGMENT_C_MASK);
	GPIO_PortClear(SEGMENT_D_GPIO, SEGMENT_D_MASK);
	GPIO_PortClear(SEGMENT_E_GPIO, SEGMENT_E_MASK);
	GPIO_PortClear(SEGMENT_F_GPIO, SEGMENT_F_MASK);
}

void display_show_1(void)
{
	display_clear();
	GPIO_PortClear(SEGMENT_B_GPIO, SEGMENT_B_MASK);
	GPIO_PortClear(SEGMENT_C_GPIO, SEGMENT_C_MASK);
}

void display_show_2(void)
{
	display_clear();
	GPIO_PortClear(SEGMENT_A_GPIO, SEGMENT_A_MASK);
	GPIO_PortClear(SEGMENT_B_GPIO, SEGMENT_B_MASK);
	GPIO_PortClear(SEGMENT_D_GPIO, SEGMENT_D_MASK);
	GPIO_PortClear(SEGMENT_E_GPIO, SEGMENT_E_MASK);
	GPIO_PortClear(SEGMENT_G_GPIO, SEGMENT_G_MASK);

}

void display_show_3(void)
{
	display_clear();
	GPIO_PortClear(SEGMENT_A_GPIO, SEGMENT_A_MASK);
	GPIO_PortClear(SEGMENT_B_GPIO, SEGMENT_B_MASK);
	GPIO_PortClear(SEGMENT_C_GPIO, SEGMENT_C_MASK);
	GPIO_PortClear(SEGMENT_D_GPIO, SEGMENT_D_MASK);
	GPIO_PortClear(SEGMENT_G_GPIO, SEGMENT_G_MASK);
}

void display_show_4(void)
{
	display_clear();
	GPIO_PortClear(SEGMENT_B_GPIO, SEGMENT_B_MASK);
	GPIO_PortClear(SEGMENT_C_GPIO, SEGMENT_C_MASK);
	GPIO_PortClear(SEGMENT_F_GPIO, SEGMENT_F_MASK);
	GPIO_PortClear(SEGMENT_G_GPIO, SEGMENT_G_MASK);
}

void display_show_5(void)
{
	display_clear();
	GPIO_PortClear(SEGMENT_A_GPIO, SEGMENT_A_MASK);
	GPIO_PortClear(SEGMENT_C_GPIO, SEGMENT_C_MASK);
	GPIO_PortClear(SEGMENT_D_GPIO, SEGMENT_D_MASK);
	GPIO_PortClear(SEGMENT_F_GPIO, SEGMENT_F_MASK);
	GPIO_PortClear(SEGMENT_G_GPIO, SEGMENT_G_MASK);
}

void display_show_6(void)
{
	display_clear();
	GPIO_PortClear(SEGMENT_C_GPIO, SEGMENT_C_MASK);
	GPIO_PortClear(SEGMENT_D_GPIO, SEGMENT_D_MASK);
	GPIO_PortClear(SEGMENT_E_GPIO, SEGMENT_E_MASK);
	GPIO_PortClear(SEGMENT_F_GPIO, SEGMENT_F_MASK);
	GPIO_PortClear(SEGMENT_G_GPIO, SEGMENT_G_MASK);
}

void display_show_7(void)
{
	display_clear();
	GPIO_PortClear(SEGMENT_A_GPIO, SEGMENT_A_MASK);
	GPIO_PortClear(SEGMENT_B_GPIO, SEGMENT_B_MASK);
	GPIO_PortClear(SEGMENT_C_GPIO, SEGMENT_C_MASK);
}

void display_show_8(void)
{
	display_clear();
	GPIO_PortClear(SEGMENT_A_GPIO, SEGMENT_A_MASK);
	GPIO_PortClear(SEGMENT_B_GPIO, SEGMENT_B_MASK);
	GPIO_PortClear(SEGMENT_C_GPIO, SEGMENT_C_MASK);
	GPIO_PortClear(SEGMENT_D_GPIO, SEGMENT_D_MASK);
	GPIO_PortClear(SEGMENT_E_GPIO, SEGMENT_E_MASK);
	GPIO_PortClear(SEGMENT_F_GPIO, SEGMENT_F_MASK);
	GPIO_PortClear(SEGMENT_G_GPIO, SEGMENT_G_MASK);
}

void display_show_9(void)
{
	display_clear();
	GPIO_PortClear(SEGMENT_A_GPIO, SEGMENT_A_MASK);
	GPIO_PortClear(SEGMENT_B_GPIO, SEGMENT_B_MASK);
	GPIO_PortClear(SEGMENT_C_GPIO, SEGMENT_C_MASK);
	GPIO_PortClear(SEGMENT_F_GPIO, SEGMENT_F_MASK);
	GPIO_PortClear(SEGMENT_G_GPIO, SEGMENT_G_MASK);
}

void display_show_error(void)
{
	display_clear();
	GPIO_PortClear(SEGMENT_G_GPIO, SEGMENT_G_MASK);
}

void displays_off(void){
	GPIO_PortClear(DISPLAY_5_GPIO, DISPLAY_5_MASK);
	GPIO_PortClear(DISPLAY_4_GPIO, DISPLAY_4_MASK);

	GPIO_PortClear(DISPLAY_3_GPIO, DISPLAY_3_MASK);
	GPIO_PortClear(DISPLAY_2_GPIO, DISPLAY_2_MASK);

	GPIO_PortClear(DISPLAY_1_GPIO, DISPLAY_1_MASK);
	GPIO_PortClear(DISPLAY_0_GPIO, DISPLAY_0_MASK);
}

void display_ctrl(uint8_t value){
	switch(value){
		case 0:
			display_show_0();
			break;

		case 1:
			display_show_1();
			break;

		case 2:
			display_show_2();
			break;

		case 3:
			display_show_3();
			break;

		case 4:
			display_show_4();
			break;

		case 5:
			display_show_5();
			break;

		case 6:
			display_show_6();
			break;

		case 7:
			display_show_7();
			break;

		case 8:
			display_show_8();
			break;

		case 9:
			display_show_9();
			break;
	}
}

void display_5_on(void){
	displays_off();
	GPIO_PortSet(DISPLAY_5_GPIO, DISPLAY_5_MASK);
}

void display_4_on(void){
	displays_off();
	GPIO_PortSet(DISPLAY_4_GPIO, DISPLAY_4_MASK);
}

void display_3_on(void){
	displays_off();
	GPIO_PortSet(DISPLAY_3_GPIO, DISPLAY_3_MASK);
}

void display_2_on(void){
	displays_off();
	GPIO_PortSet(DISPLAY_2_GPIO, DISPLAY_2_MASK);
}

void display_1_on(void){
	displays_off();
	GPIO_PortSet(DISPLAY_1_GPIO, DISPLAY_1_MASK);
}

void display_0_on(void){
	displays_off();
	GPIO_PortSet(DISPLAY_0_GPIO, DISPLAY_0_MASK);
}
