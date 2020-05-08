/************************************************/
/* Author: Alzahraa Elsallakh                   */
/* Version: V01                                 */
/* Date: 07 Feb 2020                            */
/* Layer: HAL                                   */
/* Component: LED                               */
/* File Name: LED.h                             */
/************************************************/

#ifndef LED_H
#define LED_H

#include "LED_cfg.h"

typedef struct 
{
	GPIO_t  ledElementIO;
	uint8_t ON;
	uint8_t OFF;
} ledmap_t;


/* 
  Description: This function shall initiate the specified led num by setting its
  pin, port, mode and configuration in a GPIO object and passing it to GPIO module

  Input: ledNum which holds the index of the led in the led array 

  Output: status_t

 */
extern status_t LED_init(uint8_t ledNum);

/* 
  Description: This function shall turn on the specified led 

  Input: ledNum which holds the index of the led in the led array 

  Output: status_t

 */
extern status_t LED_SwitchLedOn(uint8_t ledNum);

/* 
  Description: This function shall turn off the specified led 

  Input: ledNum which holds the index of the led in the led array 

  Output: status_t

 */
extern status_t LED_SwitchLedOff(uint8_t ledNum);

/* 
  Description: This function shall return an element of led from ledMap array

  Input: ledNum which holds the index of the led in the led array 

  Output: Address of leds struct that maps the ledNum 

 */
extern ledmap_t * getLedMap (uint8_t ledNum);

#endif
