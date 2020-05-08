/************************************************/
/* Author: Alzahraa Elsallakh                   */
/* Version: V01                                 */
/* Date: 05 Apr 2020                            */
/* Layer: MCAL                                  */
/* Component: FLASH                             */
/* File Name: FLASH.h                           */
/************************************************/


#ifndef FLASH_H
#define FLASH_H

/*
  Description: This function shall lock FPEC block

  Input:  void

  Output: void

*/
extern void FLASH_lock (void);

/*
  Description: This function shall unlock FPEC block

  Input:  void

  Output: void

*/
extern void FLASH_unlock (void);

/*
  Description: This function shall program page in FLASH

  Input:  
		1- desiredAddress -> Desired address to program
		2- desiredValue -> Desired value to be programmed

  Output: status_t 

*/
extern status_t FLASH_programPage (uint32_t  desiredAddress, uint16_t desiredValue);

/* 
  Description: This function shall erase sector in FLASH

  Input:  
		1- desiredAddress -> Desired address to erase

  Output: status_t 

*/
extern status_t FLASH_erasePage (uint32_t  desiredAddress);

/* 
  Description: This function shall erase the FLASH

  Input:  void

  Output: status_t 

*/
extern status_t FLASH_massErase(void);


#endif
