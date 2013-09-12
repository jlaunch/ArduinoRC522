
#ifndef HAVE_RC522
#define HAVE_RC522

#include <Arduino.h>
#include <SPI.h>

// ### REGISTERS ###
// Page 0: Command and status
#define RC522_REG_COMMAND 0x01
#define RC522_REG_COMIEN 0x02
#define RC522_REG_DIVIEN 0x03
#define RC522_REG_COMIRQ 0x04
#define RC522_REG_DIVIRQ 0x05
#define RC522_REG_ERROR 0x06
#define RC522_REG_STATUS1 0x07
#define RC522_REG_STATUS2 0x08
#define RC522_REG_FIFODATA 0x09
#define RC522_REG_FIFOLEVEL 0x0A
#define RC522_REG_WATERLEVEL 0x0B
#define RC522_REG_CONTROL 0x0C
#define RC522_REG_BITFRAMING 0x0D
#define RC522_REG_COLL 0x0E
// Page 1: Command
#define RC522_REG_MODE 0x11
#define RC522_REG_TXMODE 0x12
#define RC522_REG_RXMODE 0x13
#define RC522_REG_TXCONTROL 0x14
#define RC522_REG_TXASK 0x15
#define RC522_REG_TXSEL 0x16
#define RC522_REG_RXSEL 0x17
#define RC522_REG_RXTHRESHOLD 0x18
#define RC522_REG_DEMOD 0x19
#define RC522_REG_MFTX 0x1C
#define RC522_REG_MFRX 0x1D
#define RC522_REG_SERIALSPEED 0x1F
// Page 2: Configuration
#define RC522_REG_CRCRESULT_HI 0x21
#define RC522_REG_CRCRESULT_LO 0x22
#define RC522_REG_MODWIDTH 0x24
#define RC522_REG_RFCFG 0x26
#define RC522_REG_GSN 0x27
#define RC522_REG_CWGSP 0x28
#define RC522_REG_MODGSP 0x29
#define RC522_REG_TMODE 0x2A
#define RC522_REG_TPRESCALER 0x2B
#define RC522_REG_TRELOAD_HI 0x2C
#define RC522_REG_TRELOAD_LO 0x2D
#define RC522_REG_TCOUNTERVAL_HI 0x2E
#define RC522_REG_TCOUNTERVAL_LO 0x2F
// Page 3: Test
#define RC522_REG_TESTSEL1 0x31
#define RC522_REG_TESTSEL2 0x32
#define RC522_REG_TESTPINEN 0x33
#define RC522_REG_TESTPINVALUE 0x34
#define RC522_REG_TESTBUS 0x35
#define RC522_REG_AUTOTEST 0x36
#define RC522_REG_VERSION 0x37
#define RC522_REG_ANALOGTEST 0x38
#define RC522_REG_TESTDAC1 0x39
#define RC522_REG_TESTDAC2 0x3A
#define RC522_REG_TESTADC 0x3B

// ### COMMANDS ###
#define RC522_CMD_IDLE 0x0
#define RC522_CMD_MEM 0x1
#define RC522_CMD_GENID 0x2
#define RC522_CMD_CALCCRC 0x3
#define RC522_CMD_TRANSMIT 0x4
#define RC522_CMD_NOCMDCHANGE 0x7
#define RC522_CMD_RECEIVE 0x8
#define RC522_CMD_TRANSCEIVE 0xC
#define RC522_CMD_MFAUTHENT 0xE
#define RC522_CMD_SOFTRESET 0xF

// ### KEYS IDS ###
#define RC522_KEY_BIAS 0x60
#define RC522_KEY_A RC522_KEY_BIAS+0x00
#define RC522_KEY_B RC522_KEY_BIAS+0x01

#define __RC522_ACTION_READ 1
#define __RC522_ACTION_WRITE 2

class RC522 {
	public:
		RC522(int pinSelect);
		void reset();
		void select();
		void deselect();
		uint8_t regRead(uint8_t addr);
		void regReadBulk(uint8_t addr, uint8_t* data, unsigned int dataLen);
		void regWrite(uint8_t addr, uint8_t data);
		void regWriteBulk(uint8_t addr, uint8_t* data, unsigned int dataLen);
	private:
		int _pinSelect;
};

#endif