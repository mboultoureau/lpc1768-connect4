#include "constantes.h" // fichier contenant toutes les constantes du projet
#include <stdint.h>
#include "lpc17xx_i2c.h"

// mettez ici toutes les d�clarations de variables globales

char chaine[30]; // buffer pour l'affichage sur le LCD
uint16_t touch_x, touch_y;

T_PARTY_DATA party_data;

char counter = 0;
char flag_tactile_input = 0;