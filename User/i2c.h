#ifndef I2C_H_INCLUDED
#define I2C_H_INCLUDED

#include "global.h"
#include "lpc17xx_i2c.h"


/**
 * Caractéristiques de la mémoire I2C :
 * - 2048 mots de 8 bits
 * - 11 bits pour adresser un mot (2^11 = 2048)
*/

/**
 *	Initialisation de la mémoire I2C
 *
 *	Vitesse de fonctionnement à 500Khz et autorisation des échanges
 */
void init_i2c_eeprom(void);

/**
 *	Ecriture dans la mémoire I2C d'une structure PARTY
 *
 *	@param addr		Adresse dans la mémoire I2C où enregistré la donnée
 *	@param score	Un pointeur vers la structure T_SCORE à enregistrer
 *	@param length	La taille en mémoire prise (ici sizeof(length))
 */
void i2c_eeprom_write(uint16_t addr, T_SCORE* score, int length);

/**
 *	Lecture depuis la mémoire I2C d'une structure PARTY
 *
 *	@param addr		Adresse dans la mémoire I2C où la donnée est enregistré
 *	@param score	Un pointeur vers la structure T_SCORE où les données seront écrasés
 *	@param length	La taille en mémoire lu (ici sizeof(length))
 */
void i2c_eeprom_read(uint16_t addr, T_SCORE* score, int length);

#endif
