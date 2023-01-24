################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MotorLib/MidSys/bldc_scalar_current_motor.c \
../MotorLib/MidSys/bldc_scalar_pwm_bc.c \
../MotorLib/MidSys/bldc_scalar_speed_pos_hall.c \
../MotorLib/MidSys/bldc_scalar_volt_dcbus.c \
../MotorLib/MidSys/bldc_scalar_volt_potentiometer.c \
../MotorLib/MidSys/bldc_scalar_volt_userdef.c 

OBJS += \
./MotorLib/MidSys/bldc_scalar_current_motor.o \
./MotorLib/MidSys/bldc_scalar_pwm_bc.o \
./MotorLib/MidSys/bldc_scalar_speed_pos_hall.o \
./MotorLib/MidSys/bldc_scalar_volt_dcbus.o \
./MotorLib/MidSys/bldc_scalar_volt_potentiometer.o \
./MotorLib/MidSys/bldc_scalar_volt_userdef.o 

C_DEPS += \
./MotorLib/MidSys/bldc_scalar_current_motor.d \
./MotorLib/MidSys/bldc_scalar_pwm_bc.d \
./MotorLib/MidSys/bldc_scalar_speed_pos_hall.d \
./MotorLib/MidSys/bldc_scalar_volt_dcbus.d \
./MotorLib/MidSys/bldc_scalar_volt_potentiometer.d \
./MotorLib/MidSys/bldc_scalar_volt_userdef.d 


# Each subdirectory must supply rules for building sources it contributes
MotorLib/MidSys/%.o: ../MotorLib/MidSys/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F144x2048 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC4700_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

