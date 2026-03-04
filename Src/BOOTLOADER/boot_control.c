#include<boot_control.h>
#include<stdint.h>
#include<OTA/ota_manager.h>
#include<BOOTLOADER/boot_jump.h>

bool check_ota(){
	uint32_t flag = *(uint32_t*) OTA_FLAG_ADDR;
	if(flag == OTA_MODE_FLAG){
		return 1;
	}
	return 0;
}

void control_flow(){
	if (check_ota()){
		*(uint32_t *)OTA_FLAG_ADDR = 0;
		OTA_init(staging_start_addr, staging_size);
		while(1){
			OTA_run();
		}
	}
	else{
		jump_to_app();
	}
}
