#include "../../MCAL/timer/timer_types.h"




st_timerConfigType st_timer2Config = {
    .u8_timerNum = TIMER_2,
    .u8_timerClock = TIMER_F_CPU_CLOCK,
    .u16_timer_InitialValue = 0,
    .u8_timer_ovf_int_enable = TIMER_INTERRUPT_FEATURE_ENABLE,
};