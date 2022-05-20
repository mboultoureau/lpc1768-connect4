#include "lpc17xx_gpio.h"

#include "pin_connect.h"

void pin_configuration()
{
	// Configuration du PIN Connect Block pour les boutons poussoir
	// Par soucis de compréhension, on remet 0 dans les bons emplacements
	LPC_PINCON->PINSEL4 &= ~((1 << 20) | (1 << 21)  | (1 << 22) | (1 << 23));
	
	// Configuration du PIN Connect Block pour la mémoire
	LPC_PINCON->PINSEL1 |= (1 << 22);
	LPC_PINCON->PINSEL1 |= (1 << 24);
	
	// Configuration des broches du GPIO des boutons poussoir
	GPIO_SetDir(2, (1 << 10) | (1 << 11), 0);
}
