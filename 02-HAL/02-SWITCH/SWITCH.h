/************************************************/
/* Author: Alzahraa Elsallakh                   */
/* Version: V01                                 */
/* Date: 26 Mar 2020                            */
/* Layer: HAL                                   */
/* Component: SWITCH                            */
/* File Name: SWITCH_task.h                     */
/************************************************/

#ifndef SWITCH_H
#define SWITCH_H

#define PULL_UP     1
#define PULL_DOWN   2

#define PRESSED  1
#define RELEASED 0 

#define MAX_COUNTS 5

typedef struct 
{
	GPIO_t  switchElementIO;

} switchmap_t;

/* 
  Description: This function shall initiate the specified switch num by setting its
  pin, port, mode and configuration in a GPIO object and passing it to GPIO module

  Input: switchNum -> holds the index of the switch in the switch array 

  Output: status_t

 */
extern status_t Switch_Init(uint32_t switchNum);


/* 
  Description: This function shall return the specified switch state which can be 
  PRESSED or RELEASED

  Input: 
        1- switchNum which holds the index of the switch in the switch array 
        2- switchValue -> Pointer to hold the switch value

  Output: status_t

 */
extern status_t Switch_GetSwitchState(uint32_t switchNum, uint8_t * switchValue);

/* 
  Description: This function shall return the specified switch state which can be 
  PRESSED or RELEASED by SCHEDULER

  Input: 
        1- switchNum which holds the index of the switch in the switch array 
        2- switchValue -> Pointer to hold the switch value

  Output: status_t

 */
extern status_t SwitchTask_GetSwitchState(uint32_t switchNum, uint8_t * switchValue);

/*
  Description: This function is the switch scheduler task

  Input: void

  Output: void

 */
extern void switchTask (void);

#endif
