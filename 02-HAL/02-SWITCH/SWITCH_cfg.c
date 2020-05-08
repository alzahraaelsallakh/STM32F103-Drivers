/************************************************/
/* Author: Alzahraa Elsallakh                   */
/* Version: V01                                 */
/* Date: 07 Feb 2020                            */
/* Layer: HAL                                   */
/* Component: SWITCH                            */
/* File Name: SWITCH_cfg.c                      */
/************************************************/

#include "STD_TYPES.h"

#include "RCC.h"
#include "GPIO.h"

#include "SWITCH.h"
#include "SWITCH_cfg.h"

/*
  Creating an array of switch type that holds switches in the system
 */
const switchmap_t switchMap [SWITCH_NUM] = {
		{
				.switchElementIO = {
						.pin = SWITCH_ALARM_PIN,
						.port = SWITCH_ALARM_PORT,
						.mode = MODE_INPUT,
						.configuration = SWITCH_ALARM_PULL_STATE
				}
		}
};


/* 
  Description: This function shall return an element of switch from switchMap array

  Input: 
        1- switchNum -> holds the index of the switch in the switch array 

  Output: Address of switch struct that maps the switchNum 

 */
extern switchmap_t * getSwitchMap (uint32_t switchNum)
{
	return (switchmap_t *)&switchMap[switchNum];
}
