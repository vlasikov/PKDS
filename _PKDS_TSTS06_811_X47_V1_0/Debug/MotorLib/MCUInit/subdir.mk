################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MotorLib/MCUInit/ccu4.c \
../MotorLib/MCUInit/ccu8.c \
../MotorLib/MCUInit/dac.c \
../MotorLib/MCUInit/gpio.c \
../MotorLib/MCUInit/nvic.c \
../MotorLib/MCUInit/posif.c \
../MotorLib/MCUInit/systick.c \
../MotorLib/MCUInit/vadc.c 

OBJS += \
./MotorLib/MCUInit/ccu4.o \
./MotorLib/MCUInit/ccu8.o \
./MotorLib/MCUInit/dac.o \
./MotorLib/MCUInit/gpio.o \
./MotorLib/MCUInit/nvic.o \
./MotorLib/MCUInit/posif.o \
./MotorLib/MCUInit/systick.o \
./MotorLib/MCUInit/vadc.o 

C_DEPS += \
./MotorLib/MCUInit/ccu4.d \
./MotorLib/MCUInit/ccu8.d \
./MotorLib/MCUInit/dac.d \
./MotorLib/MCUInit/gpio.d \
./MotorLib/MCUInit/nvic.d \
./MotorLib/MCUInit/posif.d \
./MotorLib/MCUInit/systick.d \
./MotorLib/MCUInit/vadc.d 


# Each subdirectory must supply rules for building sources it contributes
MotorLib/MCUInit/%.o: ../MotorLib/MCUInit/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F144x2048 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC4700_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

