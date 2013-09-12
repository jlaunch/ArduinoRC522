
#include <RC522.h>

RC522::RC522(int pinSelect) {
	_pinSelect = pinSelect;
	
	pinMode(_pinSelect, OUTPUT);
	reset();
};

void RC522::reset() {
	regWrite(RC522_REG_COMMAND, RC522_CMD_SOFTRESET);
};

void RC522::select() {
	digitalWrite(_pinSelect, LOW);
};

void RC522::deselect() {
	digitalWrite(_pinSelect, HIGH);
};

uint8_t RC522::regRead(uint8_t addr) {
	select();
	SPI.transfer((addr & 0x3F) << 1 | 0x80);
	uint8_t data = SPI.transfer(data);
	deselect();
	return data;
};

void RC522::regReadBulk(uint8_t addr, uint8_t* data, unsigned int dataLen) {
	select();
	uint8_t spiAddr = (addr & 0x3F) << 1 | 0x80;
	SPI.transfer(spiAddr);
	while (dataLen-- > 0) {
		*data = SPI.transfer(spiAddr);
		data++;
	};
	deselect();
};

void RC522::regWrite(uint8_t addr, uint8_t data) {
	select();
	SPI.transfer((addr & 0x3F) << 1);
	SPI.transfer(data);
	deselect();
};

void RC522::regWriteBulk(uint8_t addr, uint8_t* data, unsigned int dataLen) {
	select();
	SPI.transfer((addr & 0x3F) << 1);
	while (dataLen-- > 0) {
		SPI.transfer(*data);
		data++;
	};
	deselect();
};
