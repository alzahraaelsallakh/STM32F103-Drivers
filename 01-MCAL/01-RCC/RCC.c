/************************************************/
/* Author: Alzahraa Elsallakh                   */
/* Version: V01                                 */
/* Date: 19 Jan 2020                            */
/* Layer: MCAL                                  */
/* Component: RCC                               */
/* File Name: RCC.c                             */
/************************************************/

#include "STD_TYPES.h"

#include "RCC.h"

#define RCC_BASE_ADDRESS (uint32_t)0x40021000

#define SELECT_SYSTEM_CLOCK_CLEAR 0xFFFFFFFC
#define GET_SYSTEM_CLOCK_CLEAR    0x0000000C
#define MCO_CLEAR                 0xF8FFFFFF
#define PLL_MUL_CLEAR             0xFFC3FFFF
#define AHB_SCALER_CLEAR          0xFFFFFF0F
#define APB1_SCALER_CLEAR         0xFFFFF8FF
#define APB2_SCALER_CLEAR         0xFFFFC7FF
#define ADC_SCALER_CLEAR          0xFFFF3FFF

#define CLOCK_SECURITY_SYSTEM            0x00080000
#define AL_HIGH_SPEED_CLOCK_BYPASS 0x00040000

#define USB_PRESCALER 0x00400000

#define PLL_SRC   0x00010000
#define PLL_XTPRE 0x00020000
#define PLL_MUL   0x003C0000

#define AHB_PRESCALER   0x000000F0

#define PLL_SRC_POS     16
#define PLL_XTPRE_POS   17
#define PLL_MUL_POS     18

#define PLL_MUL_BIN_DEC_DIFFERENCE  2

#define READY_STATE_HSI 0x00000002
#define READY_STATE_HSE 0x00020000
#define READY_STATE_PLL 0x02000000

#define HSI_TRIMMING 3

#define HSI_VALUE           ((uint32_t)8000000)
#define HSE_VALUE           ((uint32_t)8000000)

typedef struct {
	uint32_t CR;
	uint32_t CFGR;
	uint32_t CIR;
	uint32_t APB2RSTR;
	uint32_t APB1RSTR;
	uint32_t AHBENR;
	uint32_t APB2ENR;
	uint32_t APB1ENR;
	uint32_t BDCR;
	uint32_t CSR;
} peripheral_t;


volatile peripheral_t * RCC = (peripheral_t *) RCC_BASE_ADDRESS;


/* This function takes system_clock_x and selects it as system clock */
status_t RCC_selectSystemClock (uint32_t clock)
{
	status_t status = status_Ok;

	if (clock == SYSTEM_CLOCK_HSI || clock == SYSTEM_CLOCK_HSE || clock == SYSTEM_CLOCK_PLL )
	{
		uint32_t temp;
		temp = (RCC->CFGR) & SELECT_SYSTEM_CLOCK_CLEAR;
		temp |= clock;
		RCC->CFGR = temp;
	}
	else
	{
		status =  status_Nok;
	}

	return status;
}

/* This function takes nothing and return the selected clock for system */
status_t RCC_getSystemClock(uint32_t *clockStatus)
{
	status_t status = status_Ok;

	*clockStatus = RCC->CFGR & GET_SYSTEM_CLOCK_CLEAR;

	return status;
}

/* This function shall return system frequency */
status_t RCC_getSystemFrequency (uint32_t * systemFreq)
{
	status_t status = status_Ok;

	uint32_t currentClock, tempFreq;
	uint32_t temp;
	/* Reading current system clock SWS */
	currentClock = RCC->CFGR & GET_SYSTEM_CLOCK_CLEAR;

	switch (currentClock)
	{
	case SWS_HSI_SELECTED:
	{
		tempFreq = HSI_VALUE;
		break;
	}
	case SWS_HSE_SELECTED:
	{
		/* HSE OSC */
		tempFreq = HSE_VALUE;
		break;
	}
	case SWS_PLL_SELECTED:
	{
		/*
          In case PLL is selected as system clock source, must check:
          1- PLL source which can be HSI/2, HSE, HSE/2
          2- PLL multiplication factor
		 */

		/* Checking PLL entry clock source */
		temp = ((RCC->CFGR & PLL_SRC) >> PLL_SRC_POS) & 1;

		/* HSI/2 is selected as PLL source */
		if (temp == 0)
		{
			tempFreq = HSI_VALUE / 2;
		}
		/* HSE is selected as PLL source */
		else
		{
			/* Checking HSE divider for PLL entry */
			temp = ((RCC->CFGR & PLL_XTPRE) >> PLL_XTPRE_POS) & 1;

			/* HSE clock not divided */
			if (temp == 0)
			{
				tempFreq = HSE_VALUE;
			}
			/* HSE clock divided by 2 */
			else
			{
				tempFreq = HSE_VALUE/2;
			}
		}

		/* Reading PLL MUL value */
		temp = (RCC->CFGR & PLL_MUL) >> PLL_MUL_POS;
		/* Real decimal values are +2 larger than binaries */
		temp = temp + PLL_MUL_BIN_DEC_DIFFERENCE;

		tempFreq = tempFreq * temp;
		break;
	}
	default:
		status = status_Nok;
	}

	/*AHB Prescaler */
	temp = RCC->CFGR & AHB_PRESCALER;
	switch (temp)
	{
	case SCALER_AHB_2:    tempFreq = tempFreq / 2;   break;
	case SCALER_AHB_4:    tempFreq = tempFreq / 4;   break;
	case SCALER_AHB_8:    tempFreq = tempFreq / 8;   break;
	case SCALER_AHB_16:   tempFreq = tempFreq / 16;  break;
	case SCALER_AHB_64:   tempFreq = tempFreq / 64;  break;
	case SCALER_AHB_128:  tempFreq = tempFreq / 128; break;
	case SCALER_AHB_256:  tempFreq = tempFreq / 256; break;
	case SCALER_AHB_512:  tempFreq = tempFreq / 512; break;
	}

	*systemFreq = tempFreq;
	return status;
}
/* This function takes set_x_status and sets its state Enabled or Disabled, it takes state_x*/
status_t RCC_setClockStatus (uint32_t clock, uint32_t state)
{
	status_t status = status_Ok;

	if ((clock == SET_HSI_STATUS || clock == SET_HSE_STATUS || clock == SET_PLL_STATUS) && (state == STATE_ENABLE || state == STATE_DISABLE))
	{
		if (state == STATE_ENABLE)
		{
			RCC->CR |= clock;

			if (clock == SET_HSI_STATUS)
			{
				while (!(RCC->CR & READY_STATE_HSI));
			}
			else if (clock == SET_HSE_STATUS)
			{
				while (!(RCC->CR & READY_STATE_HSE));
			}
			else if (clock == SET_PLL_STATUS)
			{
				while (!(RCC->CR & READY_STATE_PLL));
			}
		}

		else
		{
			RCC->CR &= ~clock;
		}
	}

	else
	{
		status = status_Nok;
	}

	return status;
}

/* This functuin selects MCO clock , it takes MCO_x_Clk and returns Ok/Nok */
status_t RCC_selectMCO_Clock (uint32_t clock)
{
	status_t status = status_Ok;

	if (clock == MCO_SYS_CLK || clock == MCO_HSI_CLK || clock == MCO_HSE_CLK || clock == MCO_PLL_CLK)
	{
		uint32_t temp;
		temp = RCC->CFGR & MCO_CLEAR;
		temp |= clock;
	}
	else
	{
		status = status_Nok;
	}

	return status;
}

/* This function enables/disables CSS clock and takes state_x */
status_t RCC_setClockSecurity_system (uint32_t state)
{
	status_t status = status_Ok;

	if (state == STATE_ENABLE)
	{
		RCC->CR |= CLOCK_SECURITY_SYSTEM;
	}
	else if (state == STATE_DISABLE)
	{
		RCC->CR &= ~CLOCK_SECURITY_SYSTEM;
	}
	else
	{
		status =  status_Nok;
	}

	return status;
}

/* This function selects pll source clock as PLL_SRC_x */
status_t RCC_selectPLL_Source (uint32_t source)
{
	status_t status = status_Ok;

	if (!(RCC->CR & READY_STATE_PLL))
	{
		if (source == PLL_SRC_HSI)
		{
			RCC->CFGR &= ~PLL_SRC;
		}
		else if (source == PLL_SRC_HSE)
		{
			RCC->CFGR |= PLL_SRC;
		}
		else
		{
			status =  status_Nok;
		}
	}
	else
	{
		status = status_Nok;
	}

	return status;
}
/* This function enables /disables HSE divider for PLL entry, it takes PLLXTPRE_HSE_Clk_x */
status_t RCC_setPLL_HSE_Divider (uint32_t PLLXTPRE)
{
	status_t status = status_Ok;

	if (!(RCC->CR & READY_STATE_PLL))
	{
		if (PLLXTPRE == PLLXTPRE_HSE_CLK_NOT_DIVIDED)
		{
			RCC->CFGR &= ~PLL_XTPRE;
		}
		else if ( PLLXTPRE == PLLXTPRE_HSE_CLK_DIVIDED)
		{
			RCC->CFGR |= PLLXTPRE;
		}
		else
		{
			status =  status_Nok;
		}

	}
	else
	{
		status =  status_Nok;
	}

	return status;
}

/* This function takes value of PLL MUL as PLL_MUL_x */
status_t RCC_setPLL_Multiplication (uint32_t mul_value)
{
	status_t status = status_Ok;

	/* Check if PLL is disabled */
	if (!(RCC->CR & READY_STATE_PLL))
	{
		uint32_t temp;
		temp = RCC->CFGR & PLL_MUL_CLEAR;
		temp |= mul_value;
		RCC->CFGR = temp;

	}
	else
	{
		status = status_Nok;
	}

	return status;
}

/* This function takes value of HSI trimming */
status_t RCC_setHSI_Trimming (uint32_t trim_value)
{
	status_t status = status_Ok;

	if (trim_value <= 31)
	{
		RCC->CR |= trim_value << HSI_TRIMMING;

	}
	else
	{
		status = status_Nok;
	}

	return status;
}

/* This function sets al high-speed clock bypass state as Enable or Disable, it takes state_x */
status_t RCC_setHSE_Bypass (uint32_t state)
{
	status_t status = status_Ok;

	if (state == STATE_ENABLE)
	{
		RCC->CR |= AL_HIGH_SPEED_CLOCK_BYPASS;
	}
	else if (state == STATE_DISABLE)
	{
		RCC->CR &= ~AL_HIGH_SPEED_CLOCK_BYPASS;
	}
	else
	{
		status =  status_Nok;
	}
	return status;
}


/* This function sets the division factor of AHB clock, it takes SCALER_AHB_x and return Ok/Nok */
status_t RCC_setAHB_Prescaler (uint32_t scale)
{
	status_t status = status_Ok;

	if (scale == SCALER_AHB_2 ||scale == SCALER_AHB_4 ||scale == SCALER_AHB_8 ||scale == SCALER_AHB_16 ||scale == SCALER_AHB_64 ||scale == SCALER_AHB_128 ||scale == SCALER_AHB_256 ||scale == SCALER_AHB_512)
	{
		uint32_t temp;
		temp = RCC->CFGR & AHB_SCALER_CLEAR;
		temp |= scale;
		RCC->CFGR = temp;

	}
	else
	{
		status = status_Nok;
	}
	return status;
}

/* This function sets the division factor of APB1 clock, it takes SCALER_APB1_x and return Ok/Nok */
status_t RCC_setAPB1_Prescaler (uint32_t scale)
{
	status_t status = status_Ok;

	if (scale == SCALER_APB1_2 ||scale == SCALER_APB1_4 ||scale == SCALER_APB1_8 ||scale == SCALER_APB1_16)
	{
		uint32_t temp;
		temp = RCC->CFGR & APB1_SCALER_CLEAR;
		temp |= scale;
		RCC->CFGR = temp;

	}
	else
	{
		status =  status_Nok;
	}

	return status;
}

/* This function sets the division factor of APB2 clock, it takes SCALER_APB2_x and return Ok/Nok */
status_t RCC_setAPB2_Prescaler (uint32_t scale)
{
	status_t status = status_Ok;

	if (scale == SCALER_APB2_2 ||scale == SCALER_APB2_4 ||scale == SCALER_APB2_8 ||scale == SCALER_APB2_16)
	{
		uint32_t temp;
		temp = RCC->CFGR & APB2_SCALER_CLEAR;
		temp |= scale;
		RCC->CFGR = temp;

	}
	else
	{
		status = status_Nok;
	}
	return status;
}

/* This function selects the frequency of the clock to ADC, it takes SCALER_ADC_x and return Ok/Nok */
status_t RCC_setADC_Prescaler (uint32_t scale)
{
	status_t status = status_Ok;

	if (scale == SCALER_ADC_2 ||scale == SCALER_ADC_4 ||scale == SCALER_ADC_6 ||scale == SCALER_ADC_8)
	{
		uint32_t temp;
		temp = RCC->CFGR & ADC_SCALER_CLEAR;
		temp |= scale;
		RCC->CFGR = temp;
	}
	else
	{
		status =  status_Nok;
	}

	return status;
}


/* This function selects if PLL clock is divided or not for UBS, it takes SCALER_USB_PLL_x and return Ok/Nok */
status_t RCC_setUBS_Prescaler (uint32_t scale)
{

	status_t status = status_Ok;

	if (scale == SCALER_USB_PLL_NOT_DIVIDED)
	{
		RCC->CFGR |= USB_PRESCALER;
	}
	else if (scale == SCALER_USB_PLL_DIVIDED)
	{
		RCC->CFGR &= ~USB_PRESCALER;
	}
	else
	{
		status =  status_Nok;
	}
	return status;

}

/* This function enables and disables peripherals on AHB Bus, it takes AHBENR_x and state_x */
extern status_t RCC_setAHB_PeripheralState (uint32_t peripheral, uint32_t state)
{
	status_t status = status_Ok;

	if (state == STATE_ENABLE)
	{
		RCC->AHBENR |= peripheral;
	}
	else if (state == STATE_DISABLE)
	{
		RCC->AHBENR &= ~peripheral;
	}
	else
	{
		status =  status_Nok;
	}

	return status;
}

/* This function enables and disables peripherals on APB2 Bus, it takes  APB2ENR_x and state_x */
status_t RCC_setAPB2_PeripheralState (uint32_t peripheral, uint32_t state)
{
	status_t status = status_Ok;

	if (state == STATE_ENABLE)
	{
		RCC->APB2ENR |= peripheral;
	}
	else if (state == STATE_DISABLE)
	{
		RCC->APB2ENR &= ~peripheral;
	}
	else
	{
		status =  status_Nok;
	}

	return status;
}
