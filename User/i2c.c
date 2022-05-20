#include "i2c.h"

void init_i2c_eeprom()
{
		// Périphérique alimenté par défaut
		// Mise de la vitesse de fonctionnement à 500Khz
		I2C_Init(LPC_I2C0, 500000);
	
		// Autoriser les échanges
		I2C_Cmd(LPC_I2C0, ENABLE);
}

void i2c_eeprom_write(uint16_t addr, T_SCORE* score, int length)
{
		I2C_M_SETUP_Type transferConfig;
		struct data {
			uint8_t addr;
			T_SCORE score;
		};
		
		struct data data;
		data.score = *score;
		data.addr = (uint8_t) addr;
	
		// Codage de l'adresse slave : 0101 0ABC avec A, B et C respectivement le 11, 10 et 9ème bit de l'adresse
		// La fonction fera un décalage à gauche pour avoir 1010 ABC0
		transferConfig.sl_addr7bit = (1 << 6) | (1 << 4) | (((addr >> 10) & 1) << 2) | (((addr >> 9) & 1) << 1) | (((addr >> 8) & 1) << 0);
		// Les 8 derniers bits + données
		transferConfig.tx_data = (uint8_t *) &data;
		transferConfig.tx_length = sizeof(data);
		transferConfig.rx_length = 0;
		I2C_MasterTransferData(LPC_I2C0, &transferConfig, I2C_TRANSFER_POLLING);
}

void i2c_eeprom_read(uint16_t addr, T_SCORE* score, int length)
{
		I2C_M_SETUP_Type transferConfig;
		uint8_t data = (uint8_t) addr;
	
		transferConfig.sl_addr7bit = (1 << 6) | (1 << 4) | (((addr >> 10) & 1) << 2) | (((addr >> 9) & 1) << 1) | (((addr >> 8) & 1) << 0);
		transferConfig.tx_data = (uint8_t *) &data;
		transferConfig.tx_length = sizeof(data);
		transferConfig.rx_length = length;
		transferConfig.rx_data = (uint8_t *) score;
		I2C_MasterTransferData(LPC_I2C0, &transferConfig, I2C_TRANSFER_POLLING);
}
