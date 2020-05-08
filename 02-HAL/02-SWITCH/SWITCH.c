/************************************************/
/* Author: Alzahraa Elsallakh                   */
/* Version: V01                                 */
/* Date: 26 MAR 2020                            */
/* Layer: HAL                                   */
/* Component: SWITCH                            */
/* File Name: SWITCH_task.c                     */
/************************************************/

#include "STD_TYPES.h"

#include "RCC.h"
#include "GPIO.h"

#include "SWITCH.h"
#include "SWITCH_cfg.h"


uint8_t switchState[SWITCH_NUM];

switchmap_t * switchMapElement;

/* 
  Description: This function shall initiate the specified switch num by setting its
  pin, port, mode and configuration in a GPIO object and passing it to GPIO module

  Input: switchNum -> holds the index of the switch in the switch array 

  Output: status_t

 */
extern status_t Switch_Init(uint32_t switchNum)
{
	status_t status = status_Ok;

	/* Creating switch element */
	switchmap_t * switchMapElement;

	/* Getting required switch configurations */
	switchMapElement = getSwitchMap(switchNum);

	/* Initiating GPIO element */
	GPIO_initPin(&switchMapElement->switchElementIO);

	return status;
}


/* 
  Description: This function shall return the specified switch state which can be 
  PRESSED or RELEASED

  Input: 
        1- switchNum which holds the index of the switch in the switch array 
        2- switchValue -> Pointer to hold the switch value

  Output: status_t

 */
extern status_t Switch_GetSwitchState(uint32_t switchNum, uint8_t * switchValue)
{
	status_t status = status_Ok;

	/* Creating switch element */
	switchmap_t * switchMapElement;
	/* Getting required switch configurations */
	switchMapElement = getSwitchMap(switchNum);

	/* Reading GPIO value */
	GPIO_readPin(&switchMapElement->switchElementIO,switchValue);

	if (switchMapElement->switchElementIO.configuration == CONFIG_INPUT_PULL_UP)
	{
		* switchValue = * switchValue ^ 0x01;
	}

	return status;

}

/* 
  Description: This function shall return the specified switch state which can be 
  PRESSED or RELEASED by SCHEDULER

  Input: 
        1- switchNum which holds the index of the switch in the switch array 
        2- switchValue -> Pointer to hold the switch value

  Output: status_t

 */
extern status_t SwitchTask_GetSwitchState(uint32_t switchNum, uint8_t * switchValue)
{

	status_t status = status_Ok;

	*switchValue = switchState[switchNum];

	return status;

}

/*
  Description: This function is the switch scheduler task

  Input: void

  Output: void

 */
extern void switchTask (void)
{
	static uint8_t prevState[SWITCH_NUM];
	static uint8_t currState;
	static uint8_t counter[SWITCH_NUM];

	uint8_t localSwitchLoop;

	/* Looping on existed switches */
	for (localSwitchLoop = 0; localSwitchLoop < SWITCH_NUM; localSwitchLoop ++)
	{

		/* Getting required switch configurations */
		switchMapElement = getSwitchMap(localSwitchLoop);

		/* Reading GPIO value */
		GPIO_readPin(&switchMapElement->switchElementIO,&currState);

		if (switchMapElement->switchElementIO.configuration == CONFIG_INPUT_PULL_UP)
		{
			currState = currState ^ 0x01;
		}

		if (currState == prevState[localSwitchLoop])
		{
			counter[localSwitchLoop]++;
		}
		else
		{
			counter[localSwitchLoop] =0;
		}

		/* If the state is the same for fixed number of counts, then the recent current state is the actual state*/
		if (counter[localSwitchLoop] == MAX_COUNTS)
		{
			switchState[localSwitchLoop] = currState;
			counter[localSwitchLoop] =0;
		}

		prevState[localSwitchLoop] = currState;
	}



}
