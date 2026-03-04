
#include<flash_if.h>

bool flash_erase(uint8_t sector){
	FLASH->KEYR = (0x45670123);
	FLASH->KEYR = (0xCDEF89AB);

	while(FLASH->SR & (1U<<16));

	FLASH->CR |= (1U<<1);
	FLASH->CR |= (sector<<3);

	FLASH->CR |= (1U<<16);
	while(FLASH->SR & (1U<<16));

	FLASH->CR |= (1U<<31);
	return true;

}
bool flash_write(uint32_t appl_addr, uint8_t *data, uint16_t length){

	FLASH->KEYR = (0x45670123);
	FLASH->KEYR = (0xCDEF89AB);

	while(FLASH->SR & (1U<<16));

	FLASH->CR |= (1U<<0);

	for(int i=0; i<length; i+=4){
		uint32_t word = data[i] | (data[i+1]<<8) | (data[i+2]<<16) |(data[i+3]<<24);
		*(uint32_t *)(appl_addr + i) = word;
		while(FLASH->SR & (1U<<16));
	}
	FLASH->CR |= (1U<<31);
	return true;

}
