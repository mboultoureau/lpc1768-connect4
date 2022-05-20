#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include "lpc17xx_timer.h"
#include "global.h"
#include "lpc17xx_gpio.h"


#define TIMER_PRECISION	500
#define MATCH_VALUE			20

/**
 *	Initialisation du timer (précision 500µs, interruption toutes les 10ms)
 */
void init_timer(void);
void TIMER0_IRQHandler(void);

#endif
