
#include<boot_jump.h>
#include<cmsis_compiler.h>

void jump_to_app(){
	uint32_t app_sp = *(uint32_t*)application_start_addr;
	uint32_t app_reset = *(uint32_t*)(application_start_addr + 4);
	void (*func)(void) = (void(*)(void)) app_reset;
	uint32_t er_flash = 0xFFFFFFFF;
	if(app_sp!=er_flash){
		__set_MSP(app_sp);
		func();
	}
}
