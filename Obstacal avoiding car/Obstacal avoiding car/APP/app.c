
#include <util/delay.h>
#include "../STD_LIBRARIES/STD_TYPES.h"
#include "../HAL/button/button.h"
#include "../HAL/keypad/keypad.h"
#include "../HAL/lcd/lcd.h"
#include "../HAL/motor/motor.h"
#include "../HAL/timer_manager/timer_manager.h"
#include "../HAL/Ultrasonic/ultrasonic.h"
#include "app.h"



extern void HULTRASONIC_vidTimerCBF(void);
extern void HULTRASONIC_vidSigCalc(void);

void APP_vidInit(void)
{
    float64_t local_f64Dist;
    HULTRASONIC_vidInit();
    HULTRASONIC_vidCBF_TIM(HULTRASONIC_vidTimerCBF);
	HULTRASONIC_vidCBF_INT(HULTRASONIC_vidSigCalc);

}

void APP_vidStart(void)
{
    local_f64Dist = HULTRASONIC_u8Read();
	_delay_ms(15);

}
