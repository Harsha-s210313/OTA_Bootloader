#ifndef OTA_OTA_MANAGER_H_
#define OTA_OTA_MANAGER_H_
#include<stdint.h>
#include<OTA/ota_state.h>
#include<uart_if.h>
#include<stm32f411xe.h>
#include<OTA/ota_packet.h>
#include<flash_if.h>
#include<mbedtls/sha256.h>
#include<string.h>
#include<BOOTLOADER/boot_config.h>
#include<BOOTLOADER/boot_jump.h>

void OTA_init(uint32_t staging_addr, uint32_t length);
void OTA_run(void);

#endif /* OTA_OTA_MANAGER_H_ */
