/************************************************/
/* Author: Alzahraa Elsallakh                   */
/* Version: V01                                 */
/* Date: 21 Mar 2020                            */
/* Layer: OS                                    */
/* Component: SCHEDULER                         */
/* File Name: SCHEDULER_cfg.c                   */
/************************************************/

#include "STD_TYPES.h"

#include "SCHEDULER.h"
#include "SCHEDULER_cfg.h"


task_t task1;
task_t task2;

const sysTasksInfo_t sysTasksInfo [MAX_TASKS_NUMBER] = {
		{&task1,0},
		{&task2,0}
};

extern sysTasksInfo_t * getSysTasksInfo (void)
{
	return &sysTasksInfo;
}
