#ifndef FLASH_IF_H_
#define FLASH_IF_H_
#include<stdint.h>
#include<stdbool.h>

#include<stm32f411xe.h>

bool flash_erase(uint8_t sector);
bool flash_write(uint32_t appl_addr, uint8_t *data, uint16_t length);

#endif /* FLASH_IF_H_ */
