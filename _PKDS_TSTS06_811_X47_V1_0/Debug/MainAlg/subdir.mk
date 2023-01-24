################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MainAlg/door_periph.c \
../MainAlg/main_alg.c \
../MainAlg/moving.c \
../MainAlg/presets.c \
../MainAlg/retain_xmc4.c \
../MainAlg/serv_mode.c 

OBJS += \
./MainAlg/door_periph.o \
./MainAlg/main_alg.o \
./MainAlg/moving.o \
./MainAlg/presets.o \
./MainAlg/retain_xmc4.o \
./MainAlg/serv_mode.o 

C_DEPS += \
./MainAlg/door_periph.d \
./MainAlg/main_alg.d \
./MainAlg/moving.d \
./MainAlg/presets.d \
./MainAlg/retain_xmc4.d \
./MainAlg/serv_mode.d 


# Each subdirectory must supply rules for building sources it contributes
MainAlg/%.o: ../MainAlg/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM-GCC C Compiler'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -MMD -MT "$@" -DXMC4700_F144x2048 -I"$(PROJECT_LOC)/Libraries/XMCLib/inc" -I"$(PROJECT_LOC)/Libraries/CMSIS/Include" -I"$(PROJECT_LOC)/Libraries/CMSIS/Infineon/XMC4700_series/Include" -I"$(PROJECT_LOC)" -I"$(PROJECT_LOC)/Dave/Generated" -I"$(PROJECT_LOC)/Libraries" -O0 -ffunction-sections -fdata-sections -Wall -std=gnu99 -mfloat-abi=softfp -Wa,-adhlns="$@.lst" -pipe -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d) $@" -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -g -gdwarf-2 -o "$@" "$<" 
	@echo 'Finished building: $<'
	@echo.

