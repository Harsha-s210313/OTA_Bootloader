
#ifndef BOOTLOADER_BOOT_CONTROL_H_
#define BOOTLOADER_BOOT_CONTROL_H_
#include<boot_config.h>
#include<stdbool.h>
#include<boot_jump.h>

bool check_ota();
void control_flow();

#endif /* BOOTLOADER_BOOT_CONTROL_H_ */
