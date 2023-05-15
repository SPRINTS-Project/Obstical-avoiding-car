/*
 * button.c
 *
 * Created: 4/13/2023 11:44:22 PM
 *  Author: Mahmoud Sarhan
 *	EMAIL : Eng.mahmoud.adel94@gmail.com
 */ 


#include "button.h"
#include "../../MCAL/dio/dio.h"


#define BUTTON_DEBOUNCE_THRESHOLD    20
#define BUTTON_HOLD_THRESHOLD		 20
#define BUTTONS_NUM					 2U

const st_btnConfigType st_gc_btnConfig = {
	BUTTON_DEBOUNCE_THRESHOLD,																// Button_1 Debounce Threshold
	BUTTON_HOLD_THRESHOLD																	// Button_1 Hold Threshold

};

typedef struct {
	uint8_t port;
	uint8_t pin;
	u8_en_btnStateType u8_a_btnState;
	uint8_t u8_a_debounceThreshold;
	uint8_t u8_a_holdThreshold;
}st_btnConfig;

static st_btnConfig st_gs_strBtnInfo[BUTTONS_NUM];



/******************************************************************************/
/*********************** Private Functions Declaration ************************/
/******************************************************************************/
static void vidUpdateBtnState(u8_en_btnIdType en_a_BtnId);
static void vidPrePushState(u8_en_btnIdType en_a_BtnId);
static void vidPushState(u8_en_btnIdType en_a_BtnId);
static void vidPreHoldState(u8_en_btnIdType en_a_BtnId);
static void vidHoldState(u8_en_btnIdType en_a_BtnId);
static void vidPreReleaseState(u8_en_btnIdType en_a_BtnId);
static void vidReleaseState(u8_en_btnIdType en_a_BtnId);



/******************************************************************************/
/*********************** Public Functions Implementation **********************/
/******************************************************************************/

void BUTTON_mainTask(void)
{
	uint8_t u8Index;
	
	
	for(u8Index=0;u8Index<BUTTONS_NUM; u8Index++)
	{
		vidUpdateBtnState((u8_en_btnIdType)u8Index);
	}
}
u8_en_btnStateType BUTTON_init(uint8_t u8_a_port , uint8_t u8_a_pin, u8_en_btnIdType en_btnId)
{
	uint8_t u8_RetVal;
	// Set button pin as input
	u8_RetVal = DIO_init(u8_a_port, u8_a_pin , STD_INPUT);
	
	// Enable PULLUP
	u8_RetVal = DIO_writePIN(u8_a_port, u8_a_pin, STD_HIGH);
	
	st_gs_strBtnInfo[en_btnId].u8_a_btnState     = BT_PRE_PUSH;
	st_gs_strBtnInfo[en_btnId].u8_a_debounceThreshold  = ((uint8_t)0U);
	st_gs_strBtnInfo[en_btnId].u8_a_holdThreshold      = ((uint8_t)0U);
	st_gs_strBtnInfo[en_btnId].port = u8_a_port;
	st_gs_strBtnInfo[en_btnId].pin = u8_a_pin;
	/*for(u8Index=0;u8Index<BUTTONS_NUM;u8Index++)
	{
		// Set button pin as input
		DIO_init((st_gc_btnConfig[u8Index].u8_a_channelId[0]), (st_gc_btnConfig[u8Index].u8_a_channelId[1]) , STD_INPUT);
		
		// Enable PULLUP
		DIO_writePIN((st_gc_btnConfig[u8Index].u8_a_channelId[0]), (st_gc_btnConfig[u8Index].u8_a_channelId[1]), STD_HIGH);
		
		st_gs_strBtnInfo[u8Index].u8_a_btnState     = BT_PRE_PUSH;
		st_gs_strBtnInfo[u8Index].u8_a_debounceThreshold  = ((uint8_t)0U);
		st_gs_strBtnInfo[u8Index].u8_a_holdThreshold      = ((uint8_t)0U);
	}*/
	if (u8_RetVal == DIO_E_OK)
	{
		return BT_PRE_PUSH;
	}
	else
	{
		return BT_UNDEFINED;
	}
}
u8_en_btnStateType BUTTON_getState(u8_en_btnIdType en_btnId)
{
	u8_en_btnStateType enuReturn;
	
	if(en_btnId < BUTTONS_NUM)
	{
		enuReturn = st_gs_strBtnInfo[en_btnId].u8_a_btnState ;
	}
	else
	{
		enuReturn = BT_UNDEFINED;
	}
	
	return (enuReturn);
}




/******************************************************************************/
/*********************** Private Functions Implementation *********************/
/******************************************************************************/
static void vidUpdateBtnState(u8_en_btnIdType en_a_BtnId)
{
	switch(st_gs_strBtnInfo[en_a_BtnId].u8_a_btnState)
	{
		case BT_PRE_PUSH:
		vidPrePushState(en_a_BtnId);
		break;
		
		case BT_PUSHED:
		vidPushState(en_a_BtnId);
		break;
		
		case BT_PRE_HOLD:
		vidPreHoldState(en_a_BtnId);
		break;
		
		case BT_HOLD:
		vidHoldState(en_a_BtnId);
		break;
		
		case BT_PRE_RELEASE:
		vidPreReleaseState(en_a_BtnId);
		break;
		
		case BT_RELEASED:
		vidReleaseState(en_a_BtnId);
		break;
		
		default:
		break;
	}
}
static void vidPrePushState(u8_en_btnIdType en_a_BtnId)
{
	uint8_t u8BtnValue;
	
	DIO_readPIN((st_gs_strBtnInfo[en_a_BtnId].port), (st_gs_strBtnInfo[en_a_BtnId].pin),&u8BtnValue);
	
	if(u8BtnValue == BT_RELEASE_LEVEL)
	{
		st_gs_strBtnInfo[en_a_BtnId].u8_a_btnState    = BT_PUSHED;
	}
	else
	{
		st_gs_strBtnInfo[en_a_BtnId].u8_a_btnState    = BT_PRE_PUSH;
	}
}
static void vidPushState(u8_en_btnIdType en_a_BtnId)
{
	uint8_t u8_BtnValue;
	
	DIO_readPIN((st_gs_strBtnInfo[en_a_BtnId].port), (st_gs_strBtnInfo[en_a_BtnId].pin),&u8_BtnValue);
	
	if(u8_BtnValue == BT_RELEASE_LEVEL)
	{
		st_gs_strBtnInfo[en_a_BtnId].u8_a_btnState = BT_PRE_HOLD;
	}
	else
	{
		st_gs_strBtnInfo[en_a_BtnId].u8_a_btnState = BT_RELEASED;
	}
}
static void vidPreHoldState(u8_en_btnIdType en_a_BtnId)
{
	uint8_t u8_BtnValue;
	
	DIO_readPIN((st_gs_strBtnInfo[en_a_BtnId].port), (st_gs_strBtnInfo[en_a_BtnId].pin),&u8_BtnValue);
	
	if(u8_BtnValue == BT_RELEASE_LEVEL)
	{
		st_gs_strBtnInfo[en_a_BtnId].u8_a_btnState   = BT_HOLD;
	}
	else
	{
		st_gs_strBtnInfo[en_a_BtnId].u8_a_btnState    = BT_RELEASED;
	}
}
static void vidHoldState(u8_en_btnIdType en_a_BtnId)
{
	uint8_t u8_BtnValue;
	
	DIO_readPIN((st_gs_strBtnInfo[en_a_BtnId].port), (st_gs_strBtnInfo[en_a_BtnId].pin),&u8_BtnValue);
	
	if(u8_BtnValue == BT_RELEASE_LEVEL)
	{
		st_gs_strBtnInfo[en_a_BtnId].u8_a_debounceThreshold++;
		if(st_gs_strBtnInfo[en_a_BtnId].u8_a_debounceThreshold >= st_gc_btnConfig.u8_a_debounceThreshold)
		{
			st_gs_strBtnInfo[en_a_BtnId].u8_a_debounceThreshold = ((uint8_t)0);
			st_gs_strBtnInfo[en_a_BtnId].u8_a_btnState    = BT_PRE_RELEASE;
		}
		else
		{
			/* Do Nothing */
		}
		
	}
	else
	{
		// do nothing
	}
}
static void vidPreReleaseState(u8_en_btnIdType en_a_BtnId)
{
	uint8_t u8_BtnValue;
	
	DIO_readPIN((st_gs_strBtnInfo[en_a_BtnId].port), (st_gs_strBtnInfo[en_a_BtnId].pin),&u8_BtnValue);
	
	if(u8_BtnValue == BT_RELEASE_LEVEL)
	{
		st_gs_strBtnInfo[en_a_BtnId].u8_a_debounceThreshold++;
	}
	else
	{
		if(st_gs_strBtnInfo[en_a_BtnId].u8_a_debounceThreshold >= st_gc_btnConfig.u8_a_debounceThreshold)
		{
			st_gs_strBtnInfo[en_a_BtnId].u8_a_btnState = BT_RELEASED;
		}
		else
		{
			st_gs_strBtnInfo[en_a_BtnId].u8_a_btnState    = BT_PRE_PUSH;
		}
		st_gs_strBtnInfo[en_a_BtnId].u8_a_debounceThreshold = ((uint8_t)0);	
	}
}
static void vidReleaseState(u8_en_btnIdType en_a_BtnId)
{
	uint8_t u8_BtnValue;
	
	DIO_readPIN((st_gs_strBtnInfo[en_a_BtnId].port), (st_gs_strBtnInfo[en_a_BtnId].pin),&u8_BtnValue);
	
	if(u8_BtnValue == BT_PUSH_LEVEL)
	{
		//strBtnInfo[enuBtnId].u8DebounceThreshold = ((uint8_t)0);
		st_gs_strBtnInfo[en_a_BtnId].u8_a_btnState    = BT_PRE_PUSH;
	}
	else
	{
		/* Do nothing */
	}
}