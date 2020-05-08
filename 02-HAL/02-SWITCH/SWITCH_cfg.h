/************************************************/
/* Author: Alzahraa Elsallakh                   */
/* Version: V01                                 */
/* Date: 07 Feb 2020                            */
/* Layer: HAL                                   */
/* Component: SWITCH                            */
/* File Name: SWITCH_cfg.h                      */
/************************************************/

#ifndef SWITCH_CFG_H
#define SWITCH_CFG_H

#define SWITCH_NUM                   2

#define SWITCH_ALARM                 0
#define SWITCH_ALARM_PIN             PIN1
#define SWITCH_ALARM_PORT            PORTA
#define SWITCH_ALARM_PULL_STATE      CONFIG_INPUT_PULL_DOWN


#define SWITCH_INDICATOR              1
#define SWITCH_INDICATOR_PIN          PIN9
#define SWITCH_INDICATOR_PORT         PORTA
#define SWITCH_INDICATOR_PULL_STATE   CONFIG_INPUT_PULL_UP

#endif
