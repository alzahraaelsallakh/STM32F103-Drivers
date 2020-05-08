/************************************************/
/* Author: Alzahraa Elsallakh                   */
/* Version: V01                                 */
/* Date: 07 Feb 2020                            */
/* Layer: HAL                                   */
/* Component: LED                               */
/* File Name: LED_cfg.h                         */
/************************************************/

#ifndef LED_CFG_H
#define LED_CFG_H


#define LEDS_NUM           2

#define LED_ALARM          0
#define LED_ALARM_PIN      PIN2
#define LED_ALARM_PORT     PORTA
#define LED_ALARM_ON       PIN_SET
#define LED_ALARM_OFF      PIN_RESET

#define LED_INDICATOR      1
#define LED_INDICATOR_PIN  PIN7
#define LED_INDICATOR_PORT PORTA
#define LED_INDICATOR_ON   PIN_SET
#define LED_INDICATOR_OFF  PIN_RESET

#endif
