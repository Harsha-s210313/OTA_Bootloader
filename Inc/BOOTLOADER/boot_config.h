
#ifndef BOOTLOADER_BOOT_CONFIG_H_
#define BOOTLOADER_BOOT_CONFIG_H_

#define bootloader_start_addr					(0x08000000UL)
#define bootloader_size							(64 * 1024)

#define staging_start_addr						(0x08010000UL)
#define staging_size							(64 * 1024)

#define application_start_addr					(0x08020000UL)
#define application_size						(384 * 1024)

#define OTA_MODE_FLAG							(0x07FFFFFFUL)
#define OTA_FLAG_ADDR							(0X2001FFFCUL)

#endif /* BOOTLOADER_BOOT_CONFIG_H_ */
