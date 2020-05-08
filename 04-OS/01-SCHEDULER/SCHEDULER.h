/************************************************/
/* Author: Alzahraa Elsallakh                   */
/* Version: V01                                 */
/* Date: 16 Mar 2020                            */
/* Layer: OS                                    */
/* Component: SCHEDULER                         */
/* File Name: SCHEDULER.h                       */
/************************************************/

#ifndef SCHEDULER_H
#define SCHEDULER_H


typedef void (*taskRunnable_t)(void);

typedef struct {
  
  taskRunnable_t runnable;
  uint32_t periodicTime;
} task_t;


typedef struct
{
  const task_t * appTask;
  uint32_t delayTicks;
}sysTasksInfo_t;


/* 
  Description: This function shall initiate scheduler by setting timer and setting callback function
  
  Input: void
        
  Output: status_t

 */
extern status_t SCHED_init(void);


/* 
  Description: This function shall start scheduler
  
  Input: void
        
  Output: status_t

 */
extern status_t SCHED_start(void);


#endif
