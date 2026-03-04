################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/BOOTLOADER/boot_control.c \
../Src/BOOTLOADER/boot_jump.c \
../Src/BOOTLOADER/boot_verify.c 

OBJS += \
./Src/BOOTLOADER/boot_control.o \
./Src/BOOTLOADER/boot_jump.o \
./Src/BOOTLOADER/boot_verify.o 

C_DEPS += \
./Src/BOOTLOADER/boot_control.d \
./Src/BOOTLOADER/boot_jump.d \
./Src/BOOTLOADER/boot_verify.d 


# Each subdirectory must supply rules for building sources it contributes
Src/BOOTLOADER/%.o Src/BOOTLOADER/%.su Src/BOOTLOADER/%.cyclo: ../Src/BOOTLOADER/%.c Src/BOOTLOADER/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I../Inc -I"C:/Users/HARSHA/Downloads/mbedtls-mbedtls-2.28.10/mbedtls-mbedtls-2.28.10/library" -I"C:/Users/HARSHA/Downloads/mbedtls-mbedtls-2.28.10/mbedtls-mbedtls-2.28.10/programs/fuzz" -I"C:/Users/HARSHA/STM32CubeIDE/workspace_2.0.0/BootLoader/Inc/mbedtls" -I"C:/Users/HARSHA/STM32CubeIDE/workspace_2.0.0/BootLoader/Inc/BOOTLOADER" -I"C:/Users/HARSHA/Desktop/BMP/chip_headers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/HARSHA/Desktop/BMP/chip_headers/CMSIS/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src-2f-BOOTLOADER

clean-Src-2f-BOOTLOADER:
	-$(RM) ./Src/BOOTLOADER/boot_control.cyclo ./Src/BOOTLOADER/boot_control.d ./Src/BOOTLOADER/boot_control.o ./Src/BOOTLOADER/boot_control.su ./Src/BOOTLOADER/boot_jump.cyclo ./Src/BOOTLOADER/boot_jump.d ./Src/BOOTLOADER/boot_jump.o ./Src/BOOTLOADER/boot_jump.su ./Src/BOOTLOADER/boot_verify.cyclo ./Src/BOOTLOADER/boot_verify.d ./Src/BOOTLOADER/boot_verify.o ./Src/BOOTLOADER/boot_verify.su

.PHONY: clean-Src-2f-BOOTLOADER

