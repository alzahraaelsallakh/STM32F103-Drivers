/************************************************/
/* Author: Alzahraa Elsallakh                   */
/* Version: V01                                 */
/* Date: 19 Jan 2020                            */
/* Layer: MCAL                                  */
/* Component: RCC                               */
/* File Name: RCC.h                             */
/************************************************/


#ifndef RCC_H
#define RCC_H


#define SYSTEM_CLOCK_HSI 0x00000000
#define SYSTEM_CLOCK_HSE 0x00000001
#define SYSTEM_CLOCK_PLL 0x00000002

#define STATE_ENABLE  1
#define STATE_DISABLE 2

#define SWS_HSI_SELECTED    0x00000000
#define SWS_HSE_SELECTED    0x00000004
#define SWS_PLL_SELECTED    0x00000008

#define SET_HSI_STATUS 0x00000001
#define SET_HSE_STATUS 0x00010000
#define SET_PLL_STATUS 0x01000000

#define MCO_SYS_CLK 0x04000000
#define MCO_HSI_CLK 0x05000000
#define MCO_HSE_CLK 0x06000000
#define MCO_PLL_CLK 0x07000000

#define PLL_SRC_HSI 1
#define PLL_SRC_HSE 2

#define PLLXTPRE_HSE_CLK_NOT_DIVIDED 1
#define PLLXTPRE_HSE_CLK_DIVIDED     2

#define SCALER_USB_PLL_DIVIDED     1
#define SCALER_USB_PLL_NOT_DIVIDED 2

#define PLL_MUL_2   0x00000000
#define PLL_MUL_3   0x00040000
#define PLL_MUL_4   0x00080000
#define PLL_MUL_5   0x000C0000
#define PLL_MUL_6   0x00100000
#define PLL_MUL_7   0x00140000
#define PLL_MUL_8   0x00180000
#define PLL_MUL_9   0x001C0000
#define PLL_MUL_10  0x00200000
#define PLL_MUL_11  0x00240000
#define PLL_MUL_12  0x00280000
#define PLL_MUL_13  0x002C0000
#define PLL_MUL_14  0x00300000 
#define PLL_MUL_15  0x00340000
#define PLL_MUL_16  0x00380000

#define SCALER_AHB_2   0x00000080 
#define SCALER_AHB_4   0x00000090 
#define SCALER_AHB_8   0x000000A0 
#define SCALER_AHB_16  0x000000B0 
#define SCALER_AHB_64  0x000000C0 
#define SCALER_AHB_128 0x000000D0 
#define SCALER_AHB_256 0x000000E0 
#define SCALER_AHB_512 0x000000F0 

#define SCALER_APB1_2   0x00000400
#define SCALER_APB1_4   0x00000500
#define SCALER_APB1_8   0x00000600
#define SCALER_APB1_16  0x00000700

#define SCALER_APB2_2   0x00002000   
#define SCALER_APB2_4   0x00002800    
#define SCALER_APB2_8   0x00003000   
#define SCALER_APB2_16  0x00003800   

#define SCALER_ADC_2   0x00000000    
#define SCALER_ADC_4   0x00004000
#define SCALER_ADC_6   0x00008000
#define SCALER_ADC_8   0x0000C000

#define AHBENR_DMA1	      0x00000001
#define AHBENR_DMA2	      0x00000002
#define AHBENR_SRAM       0x00000004
#define AHBENR_FLITFE     0x00000010
#define AHBENR_CRCEN      0x00000040
#define AHBENR_OTGFSEN    0x00001000
#define AHBENR_ETHMACEN   0x00004000
#define AHBENR_ETHMACTXE  0x00008000
#define AHBENR_ETHMACRXE  0x00010000

#define APB2ENR_AFIO   0x00000001  
#define APB2ENR_IOPA   0x00000004
#define APB2ENR_IOPB   0x00000008
#define APB2ENR_IOPC   0x00000010
#define APB2ENR_IOPD   0x00000020
#define APB2ENR_IOPE   0x00000040
#define APB2ENR_IOPF   0x00000080
#define APB2ENR_IOPG   0x00000100
#define APB2ENR_ADC1   0x00000200
#define APB2ENR_ADC2   0x00000400
#define APB2ENR_TIM1   0x00000800
#define APB2ENR_SPI1   0x00001000
#define APB2ENR_TIM8   0x00002000
#define APB2ENR_USART1 0x00004000
#define APB2ENR_ADC3   0x00008000
#define APB2ENR_TIM9   0x00080000
#define APB2ENR_TIM10  0x00100000
#define APB2ENR_TIM11  0x00200000


/* This function takes system_clock_x and selects it as system clock */
extern status_t RCC_selectSystemClock (uint32_t clock);

/* This function takes pointer to hold the clock status as SWS_X_SELECTED*/
extern status_t RCC_getSystemClock(uint32_t *clockStatus);

/* This function shall return system frequency */
extern status_t RCC_getSystemFrequency (uint32_t * systemFreq);

/* This function takes set_x_status and sets its state Enabled or Disabled, it takes state_x */
extern status_t RCC_setClockStatus (uint32_t clock, uint32_t state);

/* This functuin selects MCO clock , it takes MCO_x_Clk and returns Ok/Nok */
extern status_t RCC_selectMCO_Clock (uint32_t clock);

/* This function enables/disables CSS clock and takes state_x*/
extern status_t RCC_setClockSecurity_system (uint32_t state);

/* This function selects pll source clock as PLL_SRC_x */
extern status_t RCC_selectPLL_Source (uint32_t pll_src);

/* This function enables /disables HSE divider for PLL entry, it takes PLLXTPRE_HSE_Clk_x */
extern status_t RCC_setPLL_HSE_Divider (uint32_t PLLXTPRE);

/* This function takes value of PLL MUL as PLL_MUL_x */
extern status_t RCC_setPLL_Multiplication (uint32_t mul_value);

/* This function takes value of HSI trimming */
extern status_t RCC_setHSI_Trimming (uint32_t trim_value);

/* This function sets External high-speed clock bypass state as Enable or Disable, it takes state_x */
extern status_t RCC_setHSE_Bypass (uint32_t state);


/* This function sets the division factor of AHB clock, it takes SCALER_AHB_x and return Ok/Nok */
extern status_t RCC_setAHB_Prescaler (uint32_t scale);

/* This function sets the division factor of APB1 clock, it takes SCALER_APB1_x and return Ok/Nok */
extern status_t RCC_setAPB1_Prescaler (uint32_t scale);

/* This function sets the division factor of APB2 clock, it takes SCALER_APB2_x and return Ok/Nok */
extern status_t RCC_setAPB2_Prescaler (uint32_t scale);

/* This function selects the frequency of the clock to ADC, it takes SCALER_ADC_x and return Ok/Nok */
extern status_t RCC_setADC_Prescaler (uint32_t scale);


/* This function selects if PLL clock is divided or not for UBS, it takes SCALER_USB_PLL_x and return Ok/Nok */
extern status_t RCC_setUBS_Prescaler (uint32_t scale);

/* This function enables and disables peripherals on AHB Bus, it takes AHBENR_x and state_x */
extern status_t RCC_setAHB_PeripheralState (uint32_t peripheral, uint32_t state);

/* This function enables and disables peripherals on APB2 Bus, it takes APB2ENR_x and state_x */
extern status_t RCC_setAPB2_PeripheralState (uint32_t peripheral, uint32_t state);

#endif
