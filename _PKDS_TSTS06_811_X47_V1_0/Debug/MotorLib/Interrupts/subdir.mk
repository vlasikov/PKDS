################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MotorLib/Interrupts/bldc_scalar_control_loop.c \
../MotorLib/Interrupts/bldc_scalar_ctrap.c \
../MotorLib/Interrupts/bldc_scalar_hall_event.c \
../MotorLib/Interrupts/bldc_scalar_pattern_shadowtx.c \
../MotorLib/Interrupts/bldc_scalar_protection_error.c \
../MotorLib/Interrupts/bldc_scalar_state_machine.c 

OBJS += \
./MotorLib/Interrupts/bldc_scalar_control_loop.o \
./MotorLib/Interrupts/bldc_scalar_ctrap.o \
./MotorLib/Interrupts/bldc_scalar_hall_event.o \
./MotorLib/Interrupts/bldc_scalar_pattern_shadowtx.o \
./MotorLib/Interrupts/bldc_scalar_protection_error.o \
./MotorLib/Interrupts/bldc_scalar_state_machine.o 

C_DEPS += \
./MotorLib/Interrupts/bldc_scalar_control_loop.d \
./MotorLib/Interrupts/bldc_scalar_ctrap.d \
./MotorLib/Interrupts/bldc_scalar_hall_event.d \
./MotorLib/Interrupts/bldc_scalar_pattern_shadowtx.d \
./MotorLib/Interrupts/bldc_scalar_protection_error.d \
./MotorLib/Interrupts/bldc_scalar_state_machine.d 


# Each subdirectory must supply rules for building sources it contributes
MotorLib/Interrupts/%.o: ../MotorLib/Interrupts/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F144x2048 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC4700_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

