#ifndef EEPROM_H_
#define EEPROM_H_

/* PROTOTYPES ********************************************************************/

void eeprom_write(uint16_t address, uint8_t data);
uint8_t eeprom_read(uint16_t address);

#endif /* EEPROM_H_ */
