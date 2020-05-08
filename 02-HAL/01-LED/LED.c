/************************************************/
/* Author: Alzahraa Elsallakh                   */
/* Version: V01                                 */
/* Date: 07 Feb 2020                            */
/* Layer: HAL                                   */
/* Component: LED                               */
/* File Name: LED.c                             */
/************************************************/

#include "STD_TYPES.h"


#include "RCC.h"
#include "GPIO.h"

#include "LED.h"
#include "LED_cfg.h"


/* 
  Description: This function shall initiate the specified led num by setting its
  pin, port, mode and configuration in a GPIO object and passing it to GPIO module

  Input: ledNum which holds the index of the led in the led array 

  Output: status_t

 */
status_t LED_init(uint8_t ledNum)
{
	status_t status = status_Ok;

	/* Creating LED element */
	ledmap_t * ledMapElement;
	/* Getting required led configurations */
	ledMapElement = getLedMap(ledNum);

	/* Initiating GPIO element */
	GPIO_initPin(&ledMapElement->ledElementIO);

	return status;
}

/* 
  Description: This function shall turn on the specified led 

  Input: ledNum which holds the index of the led in the led array 

  Output: status_t

 */
status_t LED_SwitchLedOn(uint8_t ledNum)
{
	status_t status = status_Ok;

	/* Creating led element */
	ledmap_t * ledMapElement;
	/* Getting required led configurations */
	ledMapElement = getLedMap(ledNum);

	/* Setting the led on */
	GPIO_writePin(&ledMapElement->ledElementIO,ledMapElement->ON);

	return status;
}

/* 
  Description: This function shall turn off the specified led 

  Input: ledNum which holds the index of the led in the led array 

  Output: status_t

 */
status_t LED_SwitchLedOff(uint8_t ledNum)
{
	status_t status = status_Ok;

	/* Creating led element */
	ledmap_t * ledMapElement;
	/* Getting required led configurations */
	ledMapElement = getLedMap(ledNum);

	/* Setting the led off */
	GPIO_writePin(&ledMapElement->ledElementIO,ledMapElement->OFF);

	return status;
}
