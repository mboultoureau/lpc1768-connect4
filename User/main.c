/**
 *	@author Mathis Boultoureau
 */

#include "lpc17xx_libcfg_default.h"
#include "touch\ili_lcd_general.h"
#include "touch\lcd_api.h"
#include "affichagelcd.h"
#include "touch\touch_panel.h"
#include "pin_connect.h"
#include "i2c.h"
#include "timer.h"
#include "nvic.h"
#include "globaldec.h"
#include <stdio.h>
#include <string.h>

// Réinitialisation les scores
void reset_score() {
	T_SCORE score_data;
	
	// Réinitialisation si pas de checksum
	score_data.red = 0;
	score_data.yellow = 0;
	
	// Ecriture en mémoire des scores
	i2c_eeprom_write(0, &score_data, sizeof(score_data));
}

// Affiche l'écran de victoire et incrémentation du score
void display_victory() {
	int n;
	T_SCORE score_data;
	
	// Lecture en mémoire des scores
	i2c_eeprom_read(0, &score_data, sizeof(score_data));
	
	if (party_data.player != P_YELLOW) {
		score_data.yellow++;
	} else {
		score_data.red++;
	}
	
	// Ecriture en mémoire des scores
	i2c_eeprom_write(0, &score_data, sizeof(score_data));
	
	// Fond
	dessiner_rect(0, 0, 240, 320, 0, 1, White, Black);

	if (party_data.player != P_YELLOW) {
		dessiner_rect(55, 50, 120, 120, 1, 1, White, Yellow);
		n = sprintf(chaine,"Player YELLOW won!");
		LCD_write_english_string(45, 200, chaine, White, Black);
	} else {
		dessiner_rect(55, 50, 120, 120, 1, 1, White, Red);
		n = sprintf(chaine,"Player RED won!");
		LCD_write_english_string(55, 200, chaine, White, Black);
	}

	n = sprintf(chaine, "Rouge : %d / Jaune : %d", score_data.red, score_data.yellow);
	LCD_write_english_string(34, 250, chaine, White, Black);
}

void reset_board()
{
	int i, j;
	party_data.player = P_YELLOW;
	party_data.count = 0;
	party_data.victory = 0;
	for (i = 0; i < 7; i++) {
		for (j = 0; j < 6; j++) {
			party_data.board[i][j] = P_NOTHING;
		}
	}
}

void display_board()
{
	int i, j;
		
	for (i = 0; i < 7; i++) {
		for (j = 0; j < 6; j++) {
			if (party_data.board[i][j] == P_YELLOW) {
				dessiner_rect(i * 34 + 2, j * 34, 30, 30, 2, 1, Black, Yellow);
			} else if (party_data.board[i][j] == P_RED) {
				dessiner_rect(i * 34 + 2, j * 34, 30, 30, 2, 1, Black, Red);
			} else {
				dessiner_rect(i * 34 + 2, j * 34, 30, 30, 2, 1, Black, White);
			}
		}
	}
}

void check_victory()
{
	int i, j, combo;
	
	// Vérification horizontale
	for (i = 0; i < 7; i++) {
		combo = 0;
		for (j = 0; j < 6; j++) {
			if (party_data.board[i][j] == party_data.player) {
				combo++;
			} else {
				combo = 0;
			}
			
			if (combo == 4) party_data.victory = 1;
		}
	}
	
	// Vérification verticale
	for (j = 0; j < 6; j++) {
		combo = 0;
		for (i = 0; i < 7; i++) {
			if (party_data.board[i][j] == party_data.player) {
				combo++;
			} else {
				combo = 0;
			}
			
			if (combo == 4) party_data.victory = 1;
		}
	}
	
	// Vérification diagonale haut droite vers bas gauche
	for (i = 3; i < 7; i++) {
		for (j = 0; j < 3; j++){
			if (party_data.board[i][j] == party_data.player && party_data.board[i-1][j+1] == party_data.player && party_data.board[i-2][j+2] == party_data.player && party_data.board[i-3][j+3] == party_data.player) {
				party_data.victory = 1;
			}
		}
	}
	
	// Vérification diagonale haut gauche vers bas droite
  for (i = 3; i < 7; i++){
		for (j = 3; j < 6; j++){
			if (party_data.board[i][j] == party_data.player && party_data.board[i-1][j-1] == party_data.player && party_data.board[i-2][j-2] == party_data.player && party_data.board[i-3][j-3] == party_data.player)
				party_data.victory = 1;
		}
  }
}

void play(char x)
{
	// On regarde la première case disponible pour la colonne
	char i = 5;
	while (party_data.board[x][i] != P_NOTHING && i >= 0) {
		i--;
	}
	
	// Si une case disponible on joue
	if (i != -1) {
		party_data.board[x][i] = party_data.player;
		party_data.count++;
		check_victory();
		
		if (party_data.player == P_YELLOW) {
			party_data.player = P_RED;
		} else {
			party_data.player = P_YELLOW;
		}
	}
}

//===========================================================//
// Function: Main
//===========================================================//
int main(void)
{
		int x, y;
		pin_configuration();
		init_nvic();
		init_i2c_eeprom();
	
		// Réinitialisation du plateau
		reset_score();
		reset_board();
	
		// Initialisation de l'écran LCD et du tactile
		lcd_Initializtion(); // init pinsel ecran et init LCD
		touch_init(); // init pinsel tactile et init tactile; à ne laisser que si vous utilisez le tactile
	

		// Affichage du plateau
		display_board();
	
		// Initialisation du timer avec le match register
		init_timer();		
	  
    while(1) {
			// Appui sur le bouton reset
			if (flag_button_reset == 1) {
				reset_board();
				reset_score();
				display_board();
				flag_button_reset = 0;
				continue;
			}
			
			// Appui tactile
			if (flag_tactile_input == 1) {
				// Si il y a une victoire
				if (party_data.victory == 1) {
					dessiner_rect(0, 0, 240, 320, 0, 1, White, Blue);
					reset_board();
					display_board();
				// Si égalité
				} else if (party_data.count >= 42) {
					dessiner_rect(0, 0, 240, 320, 0, 1, White, Blue);
					reset_board();
					display_board();
				} else {
					touch_read();
					
					x = touch_x * 240 / 4000;
					x = x / 34;

					if (x >= 0 && x < 7 && touch_y > 1500) {
						play(x);
						
						if (party_data.victory == 1) {
							display_victory();
						} else {
							display_board();
						}
					}
				}
				
				flag_tactile_input = 0;
			}
		}
}

//---------------------------------------------------------------------------------------------	
#ifdef  DEBUG
void check_failed(uint8_t *file, uint32_t line) {while(1);}
#endif
