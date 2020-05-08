/************************************************/
/* Author: Alzahraa Elsallakh                   */
/* Version: V01                                 */
/* Date: 16 Mar 2020                            */
/* Layer: OS                                    */
/* Component: SCHEDULER                         */
/* File Name: SCHEDULER.c                       */
/************************************************/


#include "STD_TYPES.h"

#include "RCC.h"
#include "SYSTICK.h"

#include "SCHEDULER.h"
#include "SCHEDULER_cfg.h"

typedef struct 
{
	task_t * appTask;
	uint32_t remainTicksToExec;
	uint32_t periodTicks;

}sysTask_t;

static uint8_t OSFlag;

static sysTask_t sysTasks[MAX_TASKS_NUMBER];

/* This function shall be the callback function of the scheduler */
static void setOSFlag (void)
{
	/* Setting flag to start the scheduler */
	OSFlag = 1;
}

/* 
  Description: This function shall be the scheduler itself

  Input: void

  Output: void

 */
static void SCHED_scheduler (void)
{
	uint32_t local_taskLoop;

	/* Looping on existed tasks */
	for (local_taskLoop = 0; local_taskLoop < MAX_TASKS_NUMBER ; local_taskLoop ++)
	{
		/* Task should be executed at current tick */
		if (sysTasks[local_taskLoop].remainTicksToExec == 0)
		{
			/* Calling task runnable */
			sysTasks[local_taskLoop].appTask->runnable();
			/* Updating remain ticks to execute with the initial value to start again */
			sysTasks[local_taskLoop].remainTicksToExec = sysTasks[local_taskLoop].periodTicks;
		}
		/* Decrementing remain ticks to execute each tick */
		sysTasks[local_taskLoop].remainTicksToExec--;
	}
}


/* 
  Description: This function shall initiate scheduler by:
                1- Assigning tasks' array required fields
                2- Setting Timer
                3- Setting callback function

  Input: void

  Output: status_t

 */
status_t SCHED_init(void)
{
	status_t status = status_Ok;


	/* Assigning tasks' array required fields */
	uint32_t local_taskLoop;

	sysTasksInfo_t * sysTasksInfo = getSysTasksInfo();

	for (local_taskLoop = 0; local_taskLoop < MAX_TASKS_NUMBER; local_taskLoop ++)
	{
		sysTasks[local_taskLoop].appTask = sysTasksInfo[local_taskLoop].appTask;
		sysTasks[local_taskLoop].remainTicksToExec = sysTasksInfo[local_taskLoop].delayTicks;
		sysTasks[local_taskLoop].periodTicks = (sysTasksInfo[local_taskLoop].appTask->periodicTime / TICK_USEC);
	}

	/* Setting Timer */
	uint32_t currentClock;
	RCC_getSystemFrequency(&currentClock);
	SYSTICK_init();
	SYSTICK_setTimeUs(TICK_USEC,currentClock/1000000);

	/* Setting callback function */
	SYSTICK_setCallback(setOSFlag);


	return status;
}
/* 
  Description: This function shall start scheduler

  Input: void

  Output: status_t

 */
status_t SCHED_start(void)
{
	/* Starting timer */
	SYSTICK_start();

	while (1)
	{
		if (OSFlag)
		{
			OSFlag = 0;
			SCHED_scheduler();
		}
	}
}
