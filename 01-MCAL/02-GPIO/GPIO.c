/************************************************/
/* Author: Alzahraa Elsallakh                   */
/* Version: V01                                 */
/* Date: 17 Feb 2020                            */
/* Layer: MCAL                                  */
/* Component: GPIO                              */
/* File Name: GPIO.c                            */
/************************************************/

#include "STD_TYPES.h"

#include "GPIO.h"

#define MODE_CONFIG_CLEAR 0x0000000F
#define MODE_CONFIG_SIZE 4

#define CONFIG_INPUT_PULL_UP_DOWN		0x00000008

typedef struct {
	uint32_t CRL;
	uint32_t CRH;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t BRR;
	uint32_t LCKR;

} GPIO;


/* 
  Description: This function shall initiate GPIO pin, by setting its number, port, mode and configuration

  Input: 
        1- peri -> Address of GPIO struct of GPIO_t type 

  Output: status_t

 */
status_t GPIO_initPin(GPIO_t * peri)
{
	status_t currentStatus = status_Ok;
	uint32_t temp;
	uint32_t modeConfiguration;
	uint32_t updatedPin;
	uint32_t pinLoopPosition,realPosition,currentPosition;

	uint8_t pullUpFlag = 0;
	uint32_t finalConfiguration;

	GPIO * PORT = (GPIO *) peri->port;

	finalConfiguration = peri->configuration;

	/* Checking if peripheral is connected as pull up or pull down input
	 * CONFIG_INPUT_PULL_UP & CONFIG_INPUT_PULL_DOWN are not mask configurations
	 * if ture, then finalConfiguration should be updated
	 * */
	if  (peri->mode == MODE_INPUT && (peri->configuration == CONFIG_INPUT_PULL_UP || peri->configuration == CONFIG_INPUT_PULL_DOWN))
	{
		if (peri->configuration == CONFIG_INPUT_PULL_UP)
		{
			pullUpFlag = 1;
		}
		/* Setting the right mask for pull up/down configuration */
		finalConfiguration = CONFIG_INPUT_PULL_UP_DOWN;
	}

	/* Setting CRL pins configurations */
	for (pinLoopPosition = 0x00; pinLoopPosition < 0x08; pinLoopPosition++)
	{
		realPosition = (0x01) << pinLoopPosition;
		currentPosition = realPosition & peri->pin;
		/* Extracting the pin number */
		if (currentPosition == realPosition)
		{
			temp = PORT->CRL & ~(MODE_CONFIG_CLEAR << ( pinLoopPosition * MODE_CONFIG_SIZE));
			modeConfiguration = peri->mode | finalConfiguration;
			temp |= modeConfiguration << (pinLoopPosition * MODE_CONFIG_SIZE);
			PORT->CRL = temp;
		}
	}

	/* Setting CRH pins configurations */
	for (pinLoopPosition = 0x08; pinLoopPosition < 0x10; pinLoopPosition++)
	{
		realPosition = (0x01) << pinLoopPosition;
		currentPosition = realPosition & peri->pin;
		/* Extracting the pin number */
		if (currentPosition == realPosition)
		{
			updatedPin = pinLoopPosition - 0x08;
			temp = PORT->CRH & ~(MODE_CONFIG_CLEAR << ( updatedPin * MODE_CONFIG_SIZE));
			modeConfiguration = peri->mode | peri->configuration;
			temp |= modeConfiguration << (updatedPin * MODE_CONFIG_SIZE);
			PORT->CRH = temp;
		}
	}

	/* In case of pull up, the corresponding pin should be set to one in ODR register */
	if (pullUpFlag)
	{
		pullUpFlag = 0;
		PORT->BSRR = peri->pin;
	}

	return currentStatus;
}

/* 
  Description: This function shall write value on pin 

  Input: 
        1- peri -> Address of GPIO struct of GPIO_t type 
        2- value -> The value to be written on pin, options are:
           1) PIN_SET
           2) PIN_RESET

  Output: status_t

 */
status_t GPIO_writePin(GPIO_t * peri, uint8_t value)
{

	status_t currentStatus = status_Ok;

	GPIO * PORT = (GPIO *) peri->port;

	if (value == PIN_SET)
	{
		PORT->BSRR = peri->pin;
	}
	else if (value == PIN_RESET)
	{
		PORT->BRR = peri->pin;
	}
	else
	{
		currentStatus =  status_Nok;
	}
	return currentStatus;
}

/* 
  Description: This function shall write value on pin 

  Input: 
        1- port -> port options are: PORTx where x = A B ... G 
        2- pin -> pin options are: PINx where x = 0 .. 15
        3- value -> The value to be written on pin, options are:
           1) PIN_SET
           2) PIN_RESET

  Output: status_t

 */
status_t GPIO_directWritePin(void * port ,uint32_t pin, uint8_t value)
{
	status_t currentStatus = status_Ok;

	GPIO * PORT = (GPIO *) port;

	if (value == PIN_SET)
	{
		PORT->BSRR = pin;
	}
	else if (value == PIN_RESET)
	{
		PORT->BRR = pin;
	}
	else
	{
		currentStatus =  status_Nok;
	}

	return currentStatus;
}


/* 
  Description: This function shall read value of a pin 

  Input: 
        1- peri -> Address of GPIO struct of GPIO_t type 
        2- value -> pointer to hold value of a pin, return options are:
           1) PIN_SET
           2) PIN_RESET

  Output: status_t

 */
status_t GPIO_readPin(GPIO_t * peri, uint8_t *value)
{
	status_t status = status_Ok;

	uint8_t temp;

	GPIO * PORT = (GPIO *) peri->port;

	temp = PORT->IDR & peri->pin;

	if (temp != 0)
	{
		*value = 1;
	}
	else
	{
		*value = 0;
	}


	return status;
}


/* 
  Description: This function shall write value on pin 

  Input: 
        1- port -> port options are: PORTx where x = A B ... G 
        2- pin -> pin options are: PINx where x = 0 .. 15
        3- value -> pointer to hold value of a pin, return options are:
           1) PIN_SET
           2) PIN_RESET

  Output: status_t

 */
status_t GPIO_directReadPin(void * port ,uint32_t pin, uint8_t * value)
{
	status_t status = status_Ok;

	uint8_t temp;

	GPIO * PORT = (GPIO *) port;

	temp = PORT->IDR & pin;

	if (temp != 0)
	{
		*value = 1;
	}
	else
	{
		*value = 0;
	}


	return status;
}
