/************************************************/
/* Author: Alzahraa Elsallakh                   */
/* Version: V01                                 */
/* Date: 29 Feb 2020                            */
/* Layer: MCAL                                  */
/* Component: NVIC                              */
/* File Name: NVIC.h                            */
/************************************************/

#ifndef NVIC_H
#define NVIC_H

#define INT_WWD                 0
#define INT_PVD                 1
#define INT_TAMPE               2
#define INT_RTC                 3
#define INT_FLASH               4
#define INT_RCC                 5
#define INT_EXTI0               6
#define INT_EXTI1               7
#define INT_EXTI2               8
#define INT_EXTI3               9
#define INT_EXTI4               10
#define INT_DMA1_Channel1       11
#define INT_DMA1_Channel2       12
#define INT_DMA1_Channel3       13
#define INT_DMA1_Channel4       14
#define INT_DMA1_Channel5       15
#define INT_DMA1_Channel6       16
#define INT_DMA1_Channel7       17
#define INT_ADC1_2              18
#define INT_USB_HP_CAN_TX       19
#define INT_USB_HP_CAN_Rx0      20
#define INT_CANRX1              21
#define INT_CAN_SCE             22
#define INT_EXTI9_5             23
#define INT_TIM1_BRK            24
#define INT_TIM1_UP             25
#define INT_TIM1_TRG_COM        26
#define INT_TIM1_CC             27
#define INT_TIM2                28
#define INT_TIM3                29
#define INT_TIM4                30
#define INT_I2C1_EV             31
#define INT_I2C1_ER             32
#define INT_I2C2_EV             33
#define INT_I2C2_ER             34
#define INT_SPI1                35
#define INT_SPI2                36
#define INT_USART1              37
#define INT_USART2              38
#define INT_USART3              39
#define INT_EXTI15_10           40
#define INT_RTCAlarm            41
#define INT_USBWakeup           42
#define INT_TIM8_BRK            43
#define INT_TIM8_UP             44
#define INT_TIM8_TRG_COM        45
#define INT_TIM8_CC             46
#define INT_ADC3                47
#define INT_FSMC                48
#define INT_SDIO                49
#define INT_TIM5                50
#define INT_SPI3                51
#define INT_UART4               52
#define INT_UART5               53
#define INT_TIM6                54
#define INT_TIM7                55
#define INT_DMA2_Channel1       56
#define INT_DMA2_Channel2       57
#define INT_DMA2_Channel3       58
#define INT_DMA2_Channel4_5     59


#define PRI_GRP16_SUB0  0x00000300
#define PRI_GRP8_SUB2   0x00000400
#define PRI_GRP4_SUB4   0x00000500
#define PRI_GRP2_SUB8   0x00000600
#define PRI_GRP0_SUB16  0x00000700


/* 
  Description: This function shall initiate NVIC by setting default priority 
  
  Input:  void
  
  Output: status_t 

 */
extern status_t NVIC_init (void);

/* 
  Description: This function shall enable interrupts
  
  Input: interrupt -> represents interrupt to be enabled, options are INT_x
  
  Output: status_t

 */
extern status_t NVIC_enableInterrupt (uint8_t interrupt);

/* 
  Description: This function shall disable interrupts
  
  Input: interrupt -> represents interrupt to be disabled, options are INT_x
  
  Output: status_t

 */
extern status_t NVIC_disableInterrupt (uint32_t interrupt);

/* 
  Description: This function shall set pending flag to specific interrupt
  
  Input: interrupt -> represents interrupt to set its pending, options are INT_x
  
  Output: status_t

 */
extern status_t NVIC_setPending (uint32_t interrupt);

/* 
  Description: This function shall clear pending flag to specific interrupt
  
  Input: interrupt -> represents interrupt to clear its pending, options are INT_x
  
  Output: status_t

 */
extern status_t NVIC_clearPending (uint32_t interrupt);

/* 
  Description: This function shall get active status of specific interrupt
  
  Input: interrupt -> represents interrupt to get its active flag, options are INT_x
         activeValue -> pointer to hold the value of active flag
  
  Output: status_t

 */
extern status_t NVIC_getActiveStatus (uint32_t interrupt, uint32_t * activeValue);

/* 
  Description: This function shall set priority for each interrupt
  
  Input:  interrupt -> represents interrupt to set its priority, options are INT_x
          priority -> represents the value of priority
  
  Output: status_t

 */
extern status_t NVIC_setPriority (uint32_t interrupt, uint8_t priority);

/* 
  Description: This function shall get priority for specific interrupt
  
  Input:  interrupt -> represents interrupt to get its priority, options are INT_x
          priorityValue -> pointer to hold the value of priority
  
  Output: status_t

 */
extern status_t NVIC_getPriority (uint32_t interrupt,uint32_t * priorityValue);

/* 
  Description: This function shall set the priority grouping 
  
  Input:  groupPriority -> represents the required value of priority grouping
          Options are:
              1- PRI_GRP16_SUB0
              2- PRI_GRP8_SUB2 
              3- PRI_GRP4_SUB4 
              4- PRI_GRP2_SUB8 
              5- PRI_GRP0_SUB16
  Output: status_t

 */
extern status_t NVIC_setGroupBits(uint32_t groupPriority);

/* 
  Description: This function shall generate interrupt by software
  
  Input:  interrupt -> represents interrupt to be generated by software, options are INT_x
  
  Output: status_t

 */
extern status_t NVIC_generateSoftwareInterrupt(uint32_t interrupt);

/* 
  Description: This function shall enable PRIMASK
  
  Input:  void
  
  Output: status_t

 */
extern status_t NVIC_enablePRIMASK(void);

/* 
  Description: This function shall disable PRIMASK
  
  Input:  void
  
  Output: status_t

 */
extern status_t NVIC_disablePRIMASK(void);

/* 
  Description: This function shall enable FAULTMASK
  
  Input:  void
  
  Output: status_t

 */
extern status_t NVIC_enableFAULTMASK(void);

/* 
  Description: This function shall disable FAULTMASK
  
  Input:  void
  
  Output: status_t

 */
extern status_t NVIC_disableFAULTMASK(void);

/* 
  Description: This function shall enable filter based priority 
  
  Input:  levelValue -> represents the priority value where all interrupts with the same priority or lower are disabled
  
  Output: status_t

 */
extern status_t NVIC_enableFilterBasedPriority(uint32_t levelValue);

/* 
  Description: This function shall disable filter based priority
  
  Input:  void
  
  Output: status_t

 */
extern status_t NVIC_disableFilterBasedPriority(void);

#endif
