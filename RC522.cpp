
#include <RC522.h>

RC522::RC522(int pinSelect) {
	_pinSelect = pinSelect;
	
	pinMode(_pinSelect, OUTPUT);
	reset();
};

// Issues a soft-reset
void RC522::reset() {
	regWrite(RC522_REG_COMMAND, RC522_CMD_SOFTRESET);
};

// Selects the device by setting the pin high
void RC522::select() {
	digitalWrite(_pinSelect, LOW);
};

// Unselects the device by setting the pin high
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

// Checks if the device is busy doing another operation
bool RC522::isBusy() {
	uint8_t val = regRead(RC522_REG_CMD);
	return val & 0x0F != RC522_CMD_IDLE;
};

// Cancels the comand being executed
void RC522::interrupt() {
	regWrite(RC522_REG_COMMAND, RC522_CMD_IDLE);
};

// Bidirectional communication
int RC522::transceive(uint8_t* out, unsigned int outLen, uint8_t* in, unsigned int inMaxLen, uint8_t* inLen) {
	// Wait until the device is ready
	while (isBusy());
	// Write data to send to FIFO
	regWriteBulk(RC522_REG_FIFODATA, out, outLen);
	// Start command
	regWrite(RC522_REG_COMMAND, RC522_CMD_TRANSCEIVE);
	// Wait until it finishes
	while (isBusy());
	// Check if an error ocurred
	uint8_t error = regRead(RC522_REG_ERROR) & 0xDF; // AND with 0xDF to exclude RFU bit
	if (error != 0) {
		if (error == 0x10) // Only overflow bit is set
			return RC522_OVERFLOW;
		return RC522_ERROR;
	};
	// Get amount of read bytes
	uint8_t rxLen = regRead(RC522_REG_FIFOLEVEL);
	if (inLen != NULL)
		&inLen = rxLen;
	// If we have received more than what the output buffer can hold, throw an error
	if (rxLen > inMaxLen)
		return RC522_OVERFLOW;
	// Read data
	regReadBulk(RC522_REG_FIFODATA, in, rxLen);
	return RC522_OK;
};
	
