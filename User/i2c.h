#ifndef I2C_H_INCLUDED
#define I2C_H_INCLUDED

#include "global.h"
#include "lpc17xx_i2c.h"


/**
 * Caract�ristiques de la m�moire I2C :
 * - 2048 mots de 8 bits
 * - 11 bits pour adresser un mot (2^11 = 2048)
*/

/**
 *	Initialisation de la m�moire I2C
 *
 *	Vitesse de fonctionnement � 500Khz et autorisation des �changes
 */
void init_i2c_eeprom(void);

/**
 *	Ecriture dans la m�moire I2C d'une structure PARTY
 *
 *	@param addr		Adresse dans la m�moire I2C o� enregistr� la donn�e
 *	@param score	Un pointeur vers la structure T_SCORE � enregistrer
 *	@param length	La taille en m�moire prise (ici sizeof(length))
 */
void i2c_eeprom_write(uint16_t addr, T_SCORE* score, int length);

/**
 *	Lecture depuis la m�moire I2C d'une structure PARTY
 *
 *	@param addr		Adresse dans la m�moire I2C o� la donn�e est enregistr�
 *	@param score	Un pointeur vers la structure T_SCORE o� les donn�es seront �cras�s
 *	@param length	La taille en m�moire lu (ici sizeof(length))
 */
void i2c_eeprom_read(uint16_t addr, T_SCORE* score, int length);

#endif
