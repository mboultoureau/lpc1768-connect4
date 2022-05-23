#include "timer.h"

void init_timer()
{
	TIM_TIMERCFG_Type configTimer;
	TIM_MATCHCFG_Type configMatch;
	
	// Création d'un timer de précision 500µs
	configTimer.PrescaleOption = TIM_PRESCALE_USVAL;
	configTimer.PrescaleValue = TIMER_PRECISION;
	TIM_Init(LPC_TIM0, TIM_TIMER_MODE, &configTimer);

	// Générer une interruption toutes les 10ms
	configMatch.MatchChannel = 0;
	configMatch.IntOnMatch = ENABLE;
	configMatch.StopOnMatch = DISABLE;
	configMatch.ResetOnMatch = ENABLE;
	configMatch.ExtMatchOutputType = TIM_EXTMATCH_NOTHING;
	configMatch.MatchValue = MATCH_VALUE;
	TIM_ConfigMatch(LPC_TIM0, &configMatch);
	
	// Lancement du timer
	TIM_Cmd(LPC_TIM0, ENABLE);
}

void TIMER0_IRQHandler()
{
	buttonCounter++;
	touchCounter++;
	
	// On vérifie l'appui d'un bouton toutes les 1s
	if (buttonCounter >= 100) {
		
		if (((LPC_GPIO2->FIOPIN >> 11) & (0x01)) == 0){
			flag_button_reset = 1;
		}
		
		buttonCounter = 0;
	}
	
	// On vérifie l'écran tactile toutes les 100ms
	if (touchCounter >= 10) {
		// Vérification d'un appui
		if ((GPIO_ReadValue(0) >> 19 & (1 << 0)) == 0) {
			flag_tactile_input = 1;
		}
		
		touchCounter = 0;
	}
	
	TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
}
