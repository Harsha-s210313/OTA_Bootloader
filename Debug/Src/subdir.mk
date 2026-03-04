################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/bignum.c \
../Src/constant_time.c \
../Src/ecdsa.c \
../Src/ecp.c \
../Src/flash_if.c \
../Src/main.c \
../Src/md.c \
../Src/platform_util.c \
../Src/sha256.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/uart_if.c 

OBJS += \
./Src/bignum.o \
./Src/constant_time.o \
./Src/ecdsa.o \
./Src/ecp.o \
./Src/flash_if.o \
./Src/main.o \
./Src/md.o \
./Src/platform_util.o \
./Src/sha256.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/uart_if.o 

C_DEPS += \
./Src/bignum.d \
./Src/constant_time.d \
./Src/ecdsa.d \
./Src/ecp.d \
./Src/flash_if.d \
./Src/main.d \
./Src/md.d \
./Src/platform_util.d \
./Src/sha256.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/uart_if.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411RETx -DSTM32F411xE -c -I../Inc -I"C:/Users/HARSHA/Downloads/mbedtls-mbedtls-2.28.10/mbedtls-mbedtls-2.28.10/library" -I"C:/Users/HARSHA/Downloads/mbedtls-mbedtls-2.28.10/mbedtls-mbedtls-2.28.10/programs/fuzz" -I"C:/Users/HARSHA/STM32CubeIDE/workspace_2.0.0/BootLoader/Inc/mbedtls" -I"C:/Users/HARSHA/STM32CubeIDE/workspace_2.0.0/BootLoader/Inc/BOOTLOADER" -I"C:/Users/HARSHA/Desktop/BMP/chip_headers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/HARSHA/Desktop/BMP/chip_headers/CMSIS/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/bignum.cyclo ./Src/bignum.d ./Src/bignum.o ./Src/bignum.su ./Src/constant_time.cyclo ./Src/constant_time.d ./Src/constant_time.o ./Src/constant_time.su ./Src/ecdsa.cyclo ./Src/ecdsa.d ./Src/ecdsa.o ./Src/ecdsa.su ./Src/ecp.cyclo ./Src/ecp.d ./Src/ecp.o ./Src/ecp.su ./Src/flash_if.cyclo ./Src/flash_if.d ./Src/flash_if.o ./Src/flash_if.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/md.cyclo ./Src/md.d ./Src/md.o ./Src/md.su ./Src/platform_util.cyclo ./Src/platform_util.d ./Src/platform_util.o ./Src/platform_util.su ./Src/sha256.cyclo ./Src/sha256.d ./Src/sha256.o ./Src/sha256.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/uart_if.cyclo ./Src/uart_if.d ./Src/uart_if.o ./Src/uart_if.su

.PHONY: clean-Src

