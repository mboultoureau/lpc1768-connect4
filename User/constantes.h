#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED

typedef enum {P_NOTHING, P_YELLOW, P_RED} player;

// mettez dans ce fichier toutes les constantes et définitions 
// des nouveaux types que vous souhaitez

typedef struct {
	char player;
	char count;
	char victory;
	char board[7][6];
} T_PARTY_DATA;

typedef struct {
	char yellow;
	char red;
} T_SCORE;

#endif
