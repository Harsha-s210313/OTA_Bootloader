################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/OTA/ota_manager.c \
../Src/OTA/ota_packet.c \
../Src/OTA/ota_state.c 

OBJS += \
./Src/OTA/ota_manager.o \
./Src/OTA/ota_packet.o \
./Src/OTA/ota_state.o 

C_DEPS += \
./Src/OTA/ota_manager.d \
./Src/OTA/ota_packet.d \
./Src/OTA/ota_state.d 


# Each subdirectory must supply rules for building sources it contributes
Src/OTA/%.o Src/OTA/%.su Src/OTA/%.cyclo: ../Src/OTA/%.c Src/OTA/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I../Inc -I"C:/Users/HARSHA/Downloads/mbedtls-mbedtls-2.28.10/mbedtls-mbedtls-2.28.10/library" -I"C:/Users/HARSHA/Downloads/mbedtls-mbedtls-2.28.10/mbedtls-mbedtls-2.28.10/programs/fuzz" -I"C:/Users/HARSHA/STM32CubeIDE/workspace_2.0.0/BootLoader/Inc/mbedtls" -I"C:/Users/HARSHA/STM32CubeIDE/workspace_2.0.0/BootLoader/Inc/BOOTLOADER" -I"C:/Users/HARSHA/Desktop/BMP/chip_headers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/HARSHA/Desktop/BMP/chip_headers/CMSIS/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-OTA

clean-Src-2f-OTA:
	-$(RM) ./Src/OTA/ota_manager.cyclo ./Src/OTA/ota_manager.d ./Src/OTA/ota_manager.o ./Src/OTA/ota_manager.su ./Src/OTA/ota_packet.cyclo ./Src/OTA/ota_packet.d ./Src/OTA/ota_packet.o ./Src/OTA/ota_packet.su ./Src/OTA/ota_state.cyclo ./Src/OTA/ota_state.d ./Src/OTA/ota_state.o ./Src/OTA/ota_state.su

.PHONY: clean-Src-2f-OTA

