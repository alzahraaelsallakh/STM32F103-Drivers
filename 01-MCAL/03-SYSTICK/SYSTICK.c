/************************************************/
/* Author: Alzahraa Elsallakh                   */
/* Version: V01                                 */
/* Date: 31 Mar 2020                            */
/* Layer: MCAL                                  */
/* Component: SYSTICK                           */
/* File Name: SYSTICK.c                         */
/************************************************/

#include "STD_TYPES.h"

#include "SYSTICK.h"
#include "SYSTICK_cfg.h"


#define CLKSOURCE_AHB             0x00000004
#define EXCEPTION_REQUEST_ENABLE  0x00000002
#define COUNTER_ENABLE            0x00000001

#define SYSTICK_CLOCK_PRESCALER		8

#define SYSTICK_BASE_ADDRESS   ((volatile void*)0xE000E010)


typedef struct
{
	uint32_t CTRL;
	uint32_t LOAD;
	uint32_t VAL;
	uint32_t CALIB;

} SYSTICK_t;

SYSTICK_t * SYSTICK = (SYSTICK_t *) SYSTICK_BASE_ADDRESS;

systickCBF_t ApplicationCBF;

/*
  Description: This function shall initiate systick by setting prescaler and enabling timer interrupt

  Input: void

  Output: status_t

 */
status_t SYSTICK_init (void)
{
	status_t status = status_Ok;
	/* Set timer prescaler */
#if SYSTICK_TIMER_PRESCALER == CLOCK_PRE_AHB_NO_DIV
	SYSTICK->CTRL |= CLKSOURCE_AHB;
#elif SYSTICK_TIMER_PRESCALER == CLOCK_PRE_AHB_WITH_DIV
	SYSTICK->CTRL &= ~CLKSOURCE_AHB;
#endif

	/* Enable exception request */
	SYSTICK->CTRL |= EXCEPTION_REQUEST_ENABLE;

	return status;
}

/*
  Description: This function shall start timer

  Input: void

  Output: status_t

 */
status_t SYSTICK_start (void)
{
	status_t status = status_Ok;

	/* Clearing value register */
	SYSTICK->VAL = 0;

	/* Start Timer */
	SYSTICK->CTRL |= COUNTER_ENABLE;

	return status;
}

/*
  Description: This function shall stop timer

  Input: void

  Output: status_t

 */
status_t SYSTICK_stop (void)
{
	status_t status = status_Ok;

	/* Stop Timer */
	SYSTICK->CTRL &= ~COUNTER_ENABLE;

	return status;
}

/*
  Description: This function shall set time for timer

  Input:
        1- timeUs -> the value of time represented in micro seconds
        2- AHB_clockMHz -> represents the system clock in mega hertz

  Output: status_t

 */
status_t SYSTICK_setTimeUs (uint32_t timeUs, uint32_t AHB_clockMHz)
{
	uint32_t status = status_Ok;

	uint32_t frequency;
	uint32_t load;
#if SYSTICK_TIMER_PRESCALER == CLOCK_PRE_AHB_NO_DIV
	frequency = AHB_clockMHz;
#elif SYSTICK_TIMER_PRESCALER == CLOCK_PRE_AHB_WITH_DIV
	frequency = AHB_clockMHz / SYSTICK_CLOCK_PRESCALER;
#endif
	load = timeUs * frequency;

	/* Load required value */
	SYSTICK->LOAD = load;

	return status;
}

/*
  Description: This function shall set callback function on interrupt occurance

  Input:
        1- callbackFn -> pointer to callback function, set by application

  Output: status_t

 */
status_t SYSTICK_setCallback (systickCBF_t callbackFn)
{
	status_t status = status_Ok;
	/* Checking if callback function has valid value or NuLL */
	if (callbackFn)
	{
		/* Setting application callback function with passed value */
		ApplicationCBF = callbackFn;
	}
	else
	{
		/* If callback function is NULL */
		status = status_Nok;
	}
	return status;
}

/* SYSTICK exception handler */
void SysTick_Handler (void)
{
	if (ApplicationCBF)
	{
		ApplicationCBF();
	}
}
