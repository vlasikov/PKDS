################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MotorLib/bldc_scalar_user_interface.c \
../MotorLib/bldc_scalar_variables_config.c \
../MotorLib/motor.c 

OBJS += \
./MotorLib/bldc_scalar_user_interface.o \
./MotorLib/bldc_scalar_variables_config.o \
./MotorLib/motor.o 

C_DEPS += \
./MotorLib/bldc_scalar_user_interface.d \
./MotorLib/bldc_scalar_variables_config.d \
./MotorLib/motor.d 


# Each subdirectory must supply rules for building sources it contributes
MotorLib/%.o: ../MotorLib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F144x2048 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC4700_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

