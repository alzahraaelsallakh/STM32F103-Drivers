/************************************************/
/* Author: Alzahraa Elsallakh                   */
/* Version: V01                                 */
/* Date: 31 Mar 2020                            */
/* Layer: MCAL                                  */
/* Component: SYSTICK                           */
/* File Name: SYSTICK_cfg.c                     */
/************************************************/


#ifndef SYSTICK_CFG_H
#define SYSTICK_CFG_H

/*
  Select timer prescaler
  Options are:
  1- CLOCK_PRE_AHB_NO_DIV
  2- CLOCK_PRE_AHB_WITH_DIV
*/
#define SYSTICK_TIMER_PRESCALER  CLOCK_PRE_AHB_NO_DIV


#endif