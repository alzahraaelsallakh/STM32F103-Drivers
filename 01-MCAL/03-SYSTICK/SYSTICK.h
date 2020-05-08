/************************************************/
/* Author: Alzahraa Elsallakh                   */
/* Version: V01                                 */
/* Date: 31 Mar 2020                            */
/* Layer: MCAL                                  */
/* Component: SYSTICK                           */
/* File Name: SYSTICK.h                         */
/************************************************/



#ifndef SYSTICK_H
#define SYSTICK_H


#define CLOCK_PRE_AHB_NO_DIV    1
#define CLOCK_PRE_AHB_WITH_DIV  2


typedef void (*systickCBF_t)(void);


/* 
  Description: This function shall initiate systick driver
  
  Input: void
        
  Output: status_t

 */
extern status_t SYSTICK_init (void);

/* 
  Description: This function shall start timer 
  
  Input: void
  
  Output: status_t

 */
extern status_t SYSTICK_start (void);

/* 
  Description: This function shall stop timer 
  
  Input: void
  
  Output: status_t

 */
extern status_t SYSTICK_stop (void);

/* 
  Description: This function shall set time for timer 
  
  Input: 
        1- timeUs -> the value of time represented in micro seconds
        2- AHB_clockMHz -> represents the system clock in mega hertz
        
  Output: status_t

 */
extern status_t SYSTICK_setTimeUs (uint32_t timeUs, uint32_t AHB_clockMHz);

/* 
  Description: This function shall set callback function on interrupt occurance
  
  Input: 
        1- callbackFn -> pointer to callback function, set by application
        
  Output: status_t

 */
extern status_t SYSTICK_setCallback (systickCBF_t callbackFn);

#endif
