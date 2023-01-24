################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MotorLib/ControlModule/bldc_scalar_control_hall.c \
../MotorLib/ControlModule/bldc_scalar_control_scheme.c \
../MotorLib/ControlModule/bldc_scalar_ramp_generator.c 

OBJS += \
./MotorLib/ControlModule/bldc_scalar_control_hall.o \
./MotorLib/ControlModule/bldc_scalar_control_scheme.o \
./MotorLib/ControlModule/bldc_scalar_ramp_generator.o 

C_DEPS += \
./MotorLib/ControlModule/bldc_scalar_control_hall.d \
./MotorLib/ControlModule/bldc_scalar_control_scheme.d \
./MotorLib/ControlModule/bldc_scalar_ramp_generator.d 


# Each subdirectory must supply rules for building sources it contributes
MotorLib/ControlModule/%.o: ../MotorLib/ControlModule/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F144x2048 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC4700_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

