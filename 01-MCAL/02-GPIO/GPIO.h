/************************************************/
/* Author: Alzahraa Elsallakh                   */
/* Version: V01                                 */
/* Date: 17 Feb 2020                            */
/* Layer: MCAL                                  */
/* Component: GPIO                              */
/* File Name: GPIO.h                            */
/************************************************/

#ifndef GPIO_H
#define GPIO_H

#define PIN_SET   1
#define PIN_RESET 0

#define CONFIG_INPUT_ANALOG                           0x00000000
#define CONFIG_INPUT_FLOATING                         0x00000004
#define CONFIG_INPUT_PULL_UP						  0x00000010
#define CONFIG_INPUT_PULL_DOWN					      0x00000020
#define CONFIG_OUTPUT_GENERAL_PUSH_PULL               0x00000000
#define CONFIG_OUTPUT_GENERAL_OPEN_DRAIN              0x00000004
#define CONFIG_OUTPUT_ALTERNATE_FUNCTION_OPEN_DRAIN   0x0000000C
#define CONFIG_OUTPUT_ALTERNATE_FUNCTION_PUSH_PULL    0x00000008


#define MODE_INPUT            0x00000000
#define MODE_OUTPUT_SPEED_10  0x00000001
#define MODE_OUTPUT_SPEED_2   0x00000002
#define MODE_OUTPUT_SPEED_50  0x00000003

#define PIN0    0x00000001
#define PIN1    0x00000002
#define PIN2    0x00000004
#define PIN3    0x00000008
#define PIN4    0x00000010
#define PIN5    0x00000020 
#define PIN6    0x00000040 
#define PIN7    0x00000080 
#define PIN8    0x00000100
#define PIN9    0x00000200 
#define PIN10   0x00000400 
#define PIN11   0x00000800 
#define PIN12   0x00001000
#define PIN13   0x00002000
#define PIN14   0x00004000
#define PIN15   0x00008000
#define PIN_All 0x0000FFFF

#define PORTA (void *) 0x40010800 
#define PORTB (void *) 0x40010C00
#define PORTC (void *) 0x40011000
#define PORTD (void *) 0x40011400
#define PORTE (void *) 0x40011800
#define PORTF (void *) 0x40011C00
#define PORTG (void *) 0x40012000


/*
    GPIO_t options are:
    - pin: PINx, where x = 0 .. 15
    - mode: 1) MODE_INPUT
            2) MODE_OUTPUT_SPEED_10
            3) MODE_OUTPUT_SPEED_2
            4) MODE_OUTPUT_SPEED_50
    - configuration:
      for input mode:
            1) CONFIG_INPUT_ANALOG
            2) CONFIG_INPUT_FLOATING
            3) CONFIG_INPUT_PULL_UP_DOWN
      for output mode:
            1) CONFIG_OUTPUT_GENERAL_PUSH_PULL  
            2) CONFIG_OUTPUT_GENERAL_OPEN_DRAIN           
            3) CONFIG_OUTPUT_ALTERNATE_FUNCTION_PUSH_PULL
            4) CONFIG_OUTPUT_ALTERNATE_FUNCTION_OPEN_DRAIN
    - port: PORTx where x = A B ... G
*/
typedef struct {
  
  uint32_t pin;
  uint32_t mode;
  uint32_t configuration;
  void * port;
  
}GPIO_t;


/* 
  Description: This function shall initiate GPIO pin, by setting its number, port, mode and configuration
  
  Input: 
        1- peri -> Address of GPIO struct of GPIO_t type 
  
  Output: status_t

 */
extern status_t GPIO_initPin(GPIO_t * peri);

/* 
  Description: This function shall write value on pin 
  
  Input: 
        1- peri -> Address of GPIO struct of GPIO_t type 
        2- value -> The value to be written on pin, options are:
           1) PIN_SET
           2) PIN_RESET
  
  Output: status_t

 */
extern status_t GPIO_writePin(GPIO_t * peri, uint8_t value);

/* 
  Description: This function shall write value on pin 
  
  Input: 
        1- port -> port options are: PORTx where x = A B ... G 
        2- pin -> pin options are: PINx where x = 0 .. 15
        3- value -> The value to be written on pin, options are:
           1) PIN_SET
           2) PIN_RESET
  
  Output: status_t

 */
extern status_t GPIO_directWritePin(void * port ,uint32_t pin, uint8_t value);

/* 
  Description: This function shall read value of a pin 
  
  Input: 
        1- peri -> Address of GPIO struct of GPIO_t type 
        2- value -> pointer to hold value of a pin, return options are:
           1) PIN_SET
           2) PIN_RESET
  
  Output: status_t

 */
extern status_t GPIO_readPin(GPIO_t * peri, uint8_t *value);

/* 
  Description: This function shall write value on pin 
  
  Input: 
        1- port -> port options are: PORTx where x = A B ... G 
        2- pin -> pin options are: PINx where x = 0 .. 15
        3- value -> pointer to hold value of a pin, return options are:
           1) PIN_SET
           2) PIN_RESET
  
  Output: status_t

 */
extern status_t GPIO_directReadPin(void * port ,uint32_t pin, uint8_t * value);

#endif
