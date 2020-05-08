/************************************************/
/* Author: Alzahraa Elsallakh                   */
/* Version: V01                                 */
/* Date: 07 Feb 2020                            */
/* Layer: HAL                                   */
/* Component: LED                               */
/* File Name: LED_cfg.c                         */
/************************************************/

#include "STD_TYPES.h"

#include "RCC.h"
#include "GPIO.h"

#include "LED.h"
#include "LED_cfg.h"


/*
  Creating an array of led struct that holds leds in the system
 */
const ledmap_t ledMap [LEDS_NUM] = {
		{
				.ledElementIO = {
						.pin = LED_ALARM_PIN,
						.port = LED_ALARM_PORT,
						.mode = MODE_OUTPUT_SPEED_2,
						.configuration = CONFIG_OUTPUT_GENERAL_PUSH_PULL
				},
				.ON = LED_ALARM_ON,
				.OFF = LED_ALARM_OFF
		}
};


/* 
  Description: This function shall return an element of led from ledMap array

  Input: ledNum which holds the index of the led in the led array 

  Output: Address of leds struct that maps the ledNum 

 */
extern ledmap_t * getLedMap (uint8_t ledNum)
{
	return (ledmap_t *)&ledMap[ledNum];
}
