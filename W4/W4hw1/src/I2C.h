/*
 * I2C.h
 *
 *  Created on: 21.2.2016
 *      Author: krl
 */

#ifndef I2C_H_
#define I2C_H_

#include "chip.h"


class I2C {
public:
	I2C(uint8_t I2C_TEMP_ADDR_7BIT , unsigned int i2c_bitrate , unsigned int I2C_CLK_DIVIDER );
	virtual ~I2C();
	bool transaction(uint8_t devAddr, uint8_t *txBuffPtr, uint16_t txSize, uint8_t *rxBuffPtr, uint16_t rxSize);
	bool write(uint8_t devAddr, uint8_t *txBuffPtr, uint16_t txSize);
	bool read(uint8_t devAddr, uint8_t *rxBuffPtr, uint16_t rxSize);
	void SetupXferRecAndExecute (uint8_t devAddr,uint8_t *txBuffPtr, uint16_t txSize, uint8_t *rxBuffPtr, uint16_t rxSize);
private:
	I2CM_XFER_T  i2cmXferRec;
	uint8_t I2C_TEMP_ADDR_7BIT ;
	unsigned int I2C_BITRATE ;
	unsigned int I2C_CLK_DIVIDER;
};

#endif /* I2C_H_ */
