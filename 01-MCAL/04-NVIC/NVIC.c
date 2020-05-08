/************************************************/
/* Author: Alzahraa Elsallakh                   */
/* Version: V01                                 */
/* Date: 29 Feb 2020                            */
/* Layer: MCAL                                  */
/* Component: NVIC                              */
/* File Name: NVIC.c                            */
/************************************************/

#include "STD_TYPES.h"

#include "NVIC.h"

#define NVIC_BASE_ADDRESS ((volatile void*) 0xE000E100)

#define NVIC_STIR *((volatile uint32_t*)0xE000EF00)

#define SCB_AIRCR *((volatile uint32_t*)0xE000ED0C) 

#define SCB_CCR *((volatile uint32_t*)0xE000ED14)

#define VECTKEY       0x05FA0000
#define VECTKEY_CLR   0xFFFF0000
#define PRIGROUP_CLR  0x00000700

#define USERSETMPEND 0x00000002 

typedef struct
{
	uint32_t SETENA [8];
	uint32_t dummy1 [24];
	uint32_t CLRENA [8];
	uint32_t dummy2 [24];
	uint32_t SETPEND [8];
	uint32_t dummy3 [24];
	uint32_t CLRPEND [8];
	uint32_t dummy4 [24];
	uint32_t ACTIVE [8];
	uint32_t dummy5 [56];
	uint8_t PRI[240];
}NVIC_t;


NVIC_t * NVIC= (NVIC_t*) NVIC_BASE_ADDRESS;


/* 
  Description: This function shall initiate NVIC by setting default group priority 

  Input:  void

  Output: status_t 

 */
status_t NVIC_init (void)
{
	status_t status = status_Ok;

	uint32_t temp;

	/* Reading old value of register */
	temp = SCB_AIRCR;
	/* Clearing required bits to be set */
	temp &= ~VECTKEY_CLR & ~PRIGROUP_CLR;
	/* Writing key and initial value of grouping as 16 groups and none subgroups */
	temp |= VECTKEY | PRI_GRP16_SUB0;
	/* Stroing value to the original register */
	SCB_AIRCR = temp;

	return status;
}

/* 
  Description: This function shall enable interrupts

  Input: interrupt -> represents interrupt to be enabled, options are INT_x

  Output: status_t

 */
status_t NVIC_enableInterrupt (uint8_t interrupt)
{ 

	status_t status = status_Ok;

	/* NVIC supports only 240 al interrupt */
	if (interrupt >= 240)
	{
		status = status_Nok;
	}

	/* Getting index of SETENA array >> Register number */
	uint32_t registerIndex = interrupt / 32;

	/* Referencing interrupt number to its corresponding bit  */
	interrupt = interrupt - (32 * registerIndex);

	/* Enabling interrupt by setting 1 at required bit */
	NVIC->SETENA[registerIndex] = 1 << interrupt;


	return status;

}

/* 
  Description: This function shall disable interrupts

  Input: interrupt -> represents interrupt to be disabled, options are INT_x

  Output: status_t

 */
status_t NVIC_disableInterrupt (uint32_t interrupt)
{
	status_t status = status_Ok;

	/* NVIC supports only 240 al interrupt */
	if (interrupt >= 240)
	{
		status = status_Nok;
	}

	/* Getting index of CLRENA array >> Register number */
	uint32_t registerIndex = interrupt / 32;

	/* Referencing interrupt number to its corresponding bit  */
	interrupt = interrupt - (32 * registerIndex);

	/* Disabling interrupt by setting 1 at required bit */
	NVIC->CLRENA[registerIndex] = 1 << interrupt;


	return status;
}

/* 
  Description: This function shall set pending flag to specific interrupt

  Input: interrupt -> represents interrupt to set its pending, options are INT_x

  Output: status_t

 */
status_t NVIC_setPending (uint32_t interrupt)
{
	status_t status = status_Ok;

	/* NVIC supports only 240 al interrupt */
	if (interrupt >= 240)
	{
		status = status_Nok;
	}

	/* Getting index of SETPEND array >> Register number */
	uint32_t registerIndex = interrupt / 32;

	/* Referencing interrupt number to its corresponding bit  */
	interrupt = interrupt - (32 * registerIndex);

	/* Setting pending flag by setting 1 at required bit */
	NVIC->SETPEND[registerIndex] = 1 << interrupt;


	return status;
}

/* 
  Description: This function shall clear pending flag to specific interrupt

  Input: interrupt -> represents interrupt to clear its pending, options are INT_x

  Output: status_t

 */
status_t NVIC_clearPending (uint32_t interrupt)
{
	status_t status = status_Ok;

	/* NVIC supports only 240 al interrupt */
	if (interrupt >= 240)
	{
		status = status_Nok;
	}

	/* Getting index of CLRPEND array >> Register number */
	uint32_t registerIndex = interrupt / 32;

	/* Referencing interrupt number to its corresponding bit  */
	interrupt = interrupt - (32 * registerIndex);

	/* Clearing pending flag by setting 1 at required bit */
	NVIC->CLRPEND[registerIndex] = 1 << interrupt;


	return status;
}

/* 
  Description: This function shall get active status of specific interrupt

  Input: interrupt -> represents interrupt to get its active flag, options are INT_x

  Output: status_t

 */
status_t NVIC_getActiveStatus (uint32_t interrupt, uint32_t * activeValue)
{
	status_t status = status_Ok;

	/* NVIC supports only 240 al interrupt */
	if (interrupt >= 240)
	{
		status = status_Nok;
	}

	/* Getting index of ACTIVE array >> Register number */
	uint32_t registerIndex = interrupt / 32;

	/* Referencing interrupt number to its corresponding bit  */
	interrupt = interrupt - (32 * registerIndex);

	/* Reading active bit corresponding to interrupt number */
	*activeValue  = ((NVIC->ACTIVE[registerIndex]>>interrupt)&1);


	return status;
}

/* 
  Description: This function shall set priority for each interrupt

  Input:  interrupt -> represents interrupt to set its priority, options are INT_x
          priority -> represents the value of priority

  Output: status_t

 */
status_t NVIC_setPriority (uint32_t interrupt, uint8_t priority)
{
	status_t status = status_Ok;

	/* NVIC supports only 240 al interrupt */
	if (interrupt >= 240)
	{
		status = status_Nok;
	}

	/* Setting interrupt priority */
	NVIC->PRI[interrupt] = priority;

	return status;
}

/* 
  Description: This function shall get priority for specific interrupt

  Input:  interrupt -> represents interrupt to get its priority, options are INT_x
          priorityValue -> pointer to hold the value of priority

  Output: status_t

 */
status_t NVIC_getPriority (uint32_t interrupt,uint32_t * priorityValue)
{
	status_t status = status_Ok;

	/* NVIC supports only 240 al interrupt */
	if (interrupt >= 240)
	{
		status = status_Nok;
	}

	/* Setting interrupt priority */
	*priorityValue = NVIC->PRI[interrupt];

	return status;
}

/* 
  Description: This function shall set the priority grouping 

  Input:  groupPriority -> represents the required value of priority grouping
          Options are:
              1- PRI_GRP16_SUB0
              2- PRI_GRP8_SUB2 
              3- PRI_GRP4_SUB4 
              4- PRI_GRP2_SUB8 
              5- PRI_GRP0_SUB16
  Output: status_t

 */
status_t NVIC_setGroupBits(uint32_t groupPriority)
{
	status_t status = status_Ok;

	uint32_t temp;

	/* Reading old value of register */
	temp = SCB_AIRCR;
	/* Clearing required bits to be set */
	temp &= ~VECTKEY_CLR & ~PRIGROUP_CLR;
	/* Writing key and the required priority */
	temp |= VECTKEY | groupPriority;
	/* Stroing value to the original register */
	SCB_AIRCR = temp;

	return status;
}

/* 
  Description: This function shall generate interrupt by software

  Input:  interrupt -> represents interrupt to be generated by software, options are INT_x

  Output: status_t

 */
status_t NVIC_generateSoftwareInterrupt(uint32_t interrupt)
{
	status_t status = status_Ok;

	/* Enabling unprivileged software access to the STIR*/
	SCB_CCR |= USERSETMPEND;
	/* Generating software interrupt */
	NVIC_STIR = interrupt;

	return status;
}

/* 
  Description: This function shall enable PRIMASK

  Input:  void

  Output: status_t

 */
status_t NVIC_enablePRIMASK(void)
{
	status_t status = status_Ok;

	/* Disable all interrupts */
	asm ("MOV R0, #1");
	asm("MSR PRIMASK, R0");

	return status;
}

/* 
  Description: This function shall disable PRIMASK

  Input:  void

  Output: status_t

 */
status_t NVIC_disablePRIMASK(void)
{
	status_t status = status_Ok;

	/* Allow all interrupts */
	asm ("MOV R0, #0");
	asm("MSR PRIMASK, R0");

	return status;
}

/* 
  Description: This function shall enable FAULTMASK

  Input:  void

  Output: status_t

 */
status_t NVIC_enableFAULTMASK(void)
{
	status_t status = status_Ok;

	/* Disable all interrupts and hard fault handlers*/
	asm ("MOV R0, #1");
	asm("MSR FAULTMASK, R0");

	return status;
}

/* 
  Description: This function shall disable FAULTMASK

  Input:  void

  Output: status_t

 */
status_t NVIC_disableFAULTMASK(void)
{
	status_t status = status_Ok;

	/* Allow all interrupts*/
	asm ("MOV R0, #0");
	asm("MSR FAULTMASK, R0");

	return status;
}

/* 
  Description: This function shall enable filter based priority 

  Input:  levelValue -> represents the priority value where all interrupts with the same priority or lower are disabled

  Output: status_t

 */

status_t NVIC_enableFilterBasedPriority(uint32_t levelValue)
{
	status_t status = status_Ok;

	/* Disable all interrupts with priority equal to or lower than levelValue*/
	asm ("MOV R0, %0" : : "r" (levelValue));
	asm("MSR BASEPRI, R0");


	return status;
}

/* 
  Description: This function shall disable filter based priority

  Input:  void

  Output: status_t

 */
status_t NVIC_disableFilterBasedPriority(void)
{
	status_t status = status_Ok;

	/* Disable filter based priority */
	asm ("MOV R0, #0x0");
	asm("MSR BASEPRI, R0");


	return status;
}