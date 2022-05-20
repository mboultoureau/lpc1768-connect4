#include "nvic.h"

void init_nvic()
{
	NVIC_EnableIRQ(TIMER0_IRQn);
}
