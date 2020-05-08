/************************************************/
/* Author: Alzahraa Elsallakh                   */
/* Version: V01                                 */
/* Date: 05 Apr 2020                            */
/* Layer: MCAL                                  */
/* Component: FLASH                             */
/* File Name: FLASH.c                           */
/************************************************/

#include "STD_TYPES.h"

#include "FLASH.h"


/* Unlocking FPEC block keys*/
#define KEY1  ((uint32_t)0x45670123)
#define KEY2  ((uint32_t)0xCDEF89AB)


/* Flash status register masks */
#define FLASH_SR_BSY					0x00000001
#define FLASH_SR_PGERR					0x00000004
#define FLASH_SR_WRPRTERR				0x00000010
#define FLASH_SR_EOP					0x00000020

/* Flash control register masks */
#define FLASH_CR_PG						0x00000001
#define FLASH_CR_PER    				0x00000002
#define FLASH_CR_MER  					0x00000004
#define FLASH_CR_OPTPG  				0x00000010
#define FLASH_CR_OPTER 					0x00000020
#define FLASH_CR_STRT   				0x00000040
#define FLASH_CR_LOCK   				0x00000080
#define FLASH_CR_OPTWRE 				0x00000200
#define FLASH_CR_ERRIE  				0x00000400
#define FLASH_CR_EOPIE  				0x00001000

/* Flash base address on AHB bus */
#define FLASH_BASE_ADDRESS ((volatile void*) 0x40022000)

/* FLASH registers */
typedef struct 
{
	uint32_t ACR;
	uint32_t KEYR;
	uint32_t OPTKEYR;
	uint32_t SR;
	uint32_t CR;
	uint32_t AR;
	uint32_t Reserved;
	uint32_t OBR;
	uint32_t WRPR;

} FLASH_t;


FLASH_t * FLASH = (FLASH_t *) FLASH_BASE_ADDRESS;


/*
  Description: This function shall lock FPEC block

  Input:  void

  Output: void

 */
void FLASH_lock (void)
{
	FLASH->CR |= FLASH_CR_LOCK;
}

/* 
  Description: This function shall unlock FPEC block

  Input:  void

  Output: void

 */
void FLASH_unlock (void)
{
	FLASH->KEYR = KEY1;
	FLASH->KEYR = KEY2;
}

/*
  Description: This function shall program page in FLASH

  Input:  
		1- desiredAddress -> Desired address to program
		2- desiredValue -> Desired value to be programmed

  Output: status_t 

 */
status_t FLASH_programPage (uint32_t  desiredAddress, uint16_t desiredValue)
{
	status_t status = status_Ok;
	uint16_t programmedValue;
	uint32_t lockStatus;
	uint32_t programmingErr;

	/* Checking if flash is unlocked */
	lockStatus = FLASH->CR & FLASH_CR_LOCK;
	if (lockStatus == FLASH_CR_LOCK)
	{
		status = status_Nok;
	}
	else
	{
		/* Checking that there is no flash memory operation is ongoing*/
		while ((FLASH->SR & FLASH_SR_BSY) == FLASH_SR_BSY);

		/* Choose flash programming */
		FLASH->CR |= FLASH_CR_PG;

		/* Programming half word */
		*((uint16_t *)desiredAddress) = desiredValue;

		/* Checking if address was erased before or not */
		programmingErr = FLASH->SR & FLASH_SR_PGERR;
		if (programmingErr == FLASH_SR_PGERR)
		{
			status = status_Nok;
		}
		else
		{
			/* Waiting on busy flag */
			while ((FLASH->SR & FLASH_SR_BSY) == FLASH_SR_BSY);

			/* Checking the programmed value */
			programmedValue = *((uint16_t *)desiredAddress);

			if (programmedValue != desiredValue)
			{
				status = status_Nok;
			}
		}

		/* Stopping flash programming */
		FLASH->CR &= ~FLASH_CR_PG;
	}

	return status;
}

/* 
  Description: This function shall erase sector in FLASH

  Input:  
		1- desiredAddress -> Desired address to erase

  Output: status_t 

 */
status_t FLASH_erasePage (uint32_t  desiredAddress)
{
	status_t status = status_Ok;
	uint32_t lockStatus;

	/* Checking if flash is unlocked */
	lockStatus = FLASH->CR & FLASH_CR_LOCK;
	if (lockStatus == FLASH_CR_LOCK)
	{
		status = status_Nok;
	}
	else
	{
		/* Checking that there is no flash memory operation is ongoing*/
		while ((FLASH->SR & FLASH_SR_BSY) == FLASH_SR_BSY);

		/* Choose flash erasing */
		FLASH->CR |= FLASH_CR_PER;

		/* Choosing address to erase */
		FLASH->AR = desiredAddress;

		/* Starting erasing */
		FLASH->CR |= FLASH_CR_STRT;

		/* Waiting on busy flag */
		while ((FLASH->SR & FLASH_SR_BSY) == FLASH_SR_BSY);


		/* Stopping flash erasing */
		FLASH->CR &= ~FLASH_CR_PER;
	}
	return status;
}

/* 
  Description: This function shall erase the FLASH

  Input:  void

  Output: status_t 

 */
status_t FLASH_massErase(void)
{
	status_t status = status_Ok;
	uint32_t lockStatus;

	/* Checking if flash is unlocked */
	lockStatus = FLASH->CR & FLASH_CR_LOCK;
	if (lockStatus == FLASH_CR_LOCK)
	{
		status = status_Nok;
	}
	else
	{
		/* Checking that there is no flash memory operation is ongoing*/
		while ((FLASH->SR & FLASH_SR_BSY) == FLASH_SR_BSY);

		/* Choose flash mass erasing */
		FLASH->CR |= FLASH_CR_MER;

		/* Starting erasing */
		FLASH->CR |= FLASH_CR_STRT;

		/* Waiting on busy flag */
		while ((FLASH->SR & FLASH_SR_BSY) == FLASH_SR_BSY);

		/* Stopping flash erasing */
		FLASH->CR &= ~FLASH_CR_MER;
	}
	return status;
}


