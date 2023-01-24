################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include MotorLib/MidSys/subdir.mk
-include MotorLib/MCUInit/subdir.mk
-include MotorLib/Interrupts/subdir.mk
-include MotorLib/ControlModule/subdir.mk
-include MotorLib/subdir.mk
-include MainAlg/Protocols/subdir.mk
-include MainAlg/Peripherials/subdir.mk
-include MainAlg/subdir.mk
-include Libraries/XMCLib/src/subdir.mk
-include Libraries/Newlib/subdir.mk
-include Dave/Generated/SYSTIMER/subdir.mk
-include Dave/Generated/PWM_CCU4/subdir.mk
-include Dave/Generated/INTERRUPT/subdir.mk
-include Dave/Generated/GLOBAL_CCU4/subdir.mk
-include Dave/Generated/GLOBAL_CAN/subdir.mk
-include Dave/Generated/GLOBAL_ADC/subdir.mk
-include Dave/Generated/DIGITAL_IO/subdir.mk
-include Dave/Generated/CPU_CTRL_XMC4/subdir.mk
-include Dave/Generated/CLOCK_XMC4/subdir.mk
-include Dave/Generated/CAN_NODE/subdir.mk
-include Dave/Generated/BUS_IO/subdir.mk
-include Dave/Generated/ANALOG_IO/subdir.mk
-include Dave/Generated/ADC_MEASUREMENT/subdir.mk
-include Dave/Generated/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
_PKDS_TSTS06_811_X47_V1_0.hex \

SECONDARY_LIST += \
_PKDS_TSTS06_811_X47_V1_0.lst \

SECONDARY_SIZE += \
_PKDS_TSTS06_811_X47_V1_0.siz \


LIST_FILES = $(addsuffix .o.lst, $(basename $(OBJS))) 
MAP_FILE = "_PKDS_TSTS06_811_X47_V1_0.map"

TOOLCHAIN_ROOT=C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2020-q4-major
PROJECT_LOC=C:/Workspaces/DAVE-4.4.2-64Bit/_PKDS_TSTS06_811_X47_V1_0

# All Target
all: _PKDS_TSTS06_811_X47_V1_0.elf secondary-outputs

# Tool invocations
_PKDS_TSTS06_811_X47_V1_0.elf: $(OBJS) ../linker_script.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM-GCC C Linker'
	$(file >objects.rsp,$(OBJS))
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-gcc" -T"../linker_script.ld" -nostartfiles -Xlinker --gc-sections -specs=nano.specs -specs=nosys.specs -Wl,-Map,$(MAP_FILE) -mfloat-abi=softfp -mfpu=fpv4-sp-d16 -mcpu=cortex-m4 -mthumb -g -gdwarf-2 -o "_PKDS_TSTS06_811_X47_V1_0.elf" "@objects.rsp" $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo.
_PKDS_TSTS06_811_X47_V1_0.hex: _PKDS_TSTS06_811_X47_V1_0.elf
	@echo 'Invoking: ARM-GCC Create Flash Image'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-objcopy" -O ihex "_PKDS_TSTS06_811_X47_V1_0.elf" "_PKDS_TSTS06_811_X47_V1_0.hex"
	@echo 'Finished building: $@'
	@echo.
_PKDS_TSTS06_811_X47_V1_0.lst: _PKDS_TSTS06_811_X47_V1_0.elf
	@echo 'Invoking: ARM-GCC Create Listing'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-objdump" -h -S "_PKDS_TSTS06_811_X47_V1_0.elf" > "_PKDS_TSTS06_811_X47_V1_0.lst"
	@echo 'Finished building: $@'
	@echo.
_PKDS_TSTS06_811_X47_V1_0.siz: _PKDS_TSTS06_811_X47_V1_0.elf
	@echo 'Invoking: ARM-GCC Print Size'
	"$(TOOLCHAIN_ROOT)/bin/arm-none-eabi-size" --format=berkeley "_PKDS_TSTS06_811_X47_V1_0.elf"
	@echo 'Finished building: $@'
	@echo.
# Other Targets
clean:
	-$(RM) $(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ARM_GCC_FOR_XMC_LINKER_OUTPUT_TYPE_OUTPUTS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS)
	-$(RM) Dave/Generated/ADC_MEASUREMENT/adc_measurement.o Dave/Generated/ADC_MEASUREMENT/adc_measurement_conf.o Dave/Generated/ANALOG_IO/analog_io.o Dave/Generated/ANALOG_IO/analog_io_conf.o Dave/Generated/BUS_IO/bus_io.o Dave/Generated/BUS_IO/bus_io_conf.o Dave/Generated/CAN_NODE/can_node.o Dave/Generated/CAN_NODE/can_node_conf.o Dave/Generated/CLOCK_XMC4/clock_xmc4.o Dave/Generated/CLOCK_XMC4/clock_xmc4_conf.o Dave/Generated/CPU_CTRL_XMC4/cpu_ctrl_xmc4.o Dave/Generated/CPU_CTRL_XMC4/cpu_ctrl_xmc4_conf.o Dave/Generated/DAVE.o Dave/Generated/DIGITAL_IO/digital_io.o Dave/Generated/DIGITAL_IO/digital_io_conf.o Dave/Generated/GLOBAL_ADC/global_adc.o Dave/Generated/GLOBAL_ADC/global_adc_conf.o Dave/Generated/GLOBAL_CAN/global_can.o Dave/Generated/GLOBAL_CAN/global_can_conf.o Dave/Generated/GLOBAL_CCU4/global_ccu4.o Dave/Generated/GLOBAL_CCU4/global_ccu4_conf.o Dave/Generated/INTERRUPT/interrupt.o Dave/Generated/INTERRUPT/interrupt_conf.o Dave/Generated/PWM_CCU4/pwm_ccu4.o Dave/Generated/PWM_CCU4/pwm_ccu4_conf.o Dave/Generated/SYSTIMER/systimer.o Dave/Generated/SYSTIMER/systimer_conf.o Libraries/Newlib/syscalls.o Libraries/XMCLib/src/xmc4_eru.o Libraries/XMCLib/src/xmc4_flash.o Libraries/XMCLib/src/xmc4_gpio.o Libraries/XMCLib/src/xmc4_rtc.o Libraries/XMCLib/src/xmc4_scu.o Libraries/XMCLib/src/xmc_can.o Libraries/XMCLib/src/xmc_ccu4.o Libraries/XMCLib/src/xmc_ccu8.o Libraries/XMCLib/src/xmc_common.o Libraries/XMCLib/src/xmc_dac.o Libraries/XMCLib/src/xmc_dma.o Libraries/XMCLib/src/xmc_dsd.o Libraries/XMCLib/src/xmc_ebu.o Libraries/XMCLib/src/xmc_ecat.o Libraries/XMCLib/src/xmc_eru.o Libraries/XMCLib/src/xmc_eth_mac.o Libraries/XMCLib/src/xmc_eth_phy_dp83848.o Libraries/XMCLib/src/xmc_eth_phy_ksz8031rnl.o Libraries/XMCLib/src/xmc_eth_phy_ksz8081rnb.o Libraries/XMCLib/src/xmc_fce.o Libraries/XMCLib/src/xmc_gpio.o Libraries/XMCLib/src/xmc_hrpwm.o Libraries/XMCLib/src/xmc_i2c.o Libraries/XMCLib/src/xmc_i2s.o 
	-$(RM) Libraries/XMCLib/src/xmc_ledts.o Libraries/XMCLib/src/xmc_posif.o Libraries/XMCLib/src/xmc_rtc.o Libraries/XMCLib/src/xmc_sdmmc.o Libraries/XMCLib/src/xmc_spi.o Libraries/XMCLib/src/xmc_uart.o Libraries/XMCLib/src/xmc_usbd.o Libraries/XMCLib/src/xmc_usbh.o Libraries/XMCLib/src/xmc_usic.o Libraries/XMCLib/src/xmc_vadc.o Libraries/XMCLib/src/xmc_wdt.o MainAlg/Peripherials/Buzzer.o MainAlg/Peripherials/LedRubber.o MainAlg/Peripherials/Scheme.o MainAlg/Protocols/j1939.o MainAlg/door_periph.o MainAlg/main_alg.o MainAlg/moving.o MainAlg/presets.o MainAlg/retain_xmc4.o MainAlg/serv_mode.o MotorLib/ControlModule/bldc_scalar_control_hall.o MotorLib/ControlModule/bldc_scalar_control_scheme.o MotorLib/ControlModule/bldc_scalar_ramp_generator.o MotorLib/Interrupts/bldc_scalar_control_loop.o MotorLib/Interrupts/bldc_scalar_ctrap.o MotorLib/Interrupts/bldc_scalar_hall_event.o MotorLib/Interrupts/bldc_scalar_pattern_shadowtx.o MotorLib/Interrupts/bldc_scalar_protection_error.o MotorLib/Interrupts/bldc_scalar_state_machine.o MotorLib/MCUInit/ccu4.o MotorLib/MCUInit/ccu8.o MotorLib/MCUInit/dac.o MotorLib/MCUInit/gpio.o MotorLib/MCUInit/nvic.o MotorLib/MCUInit/posif.o MotorLib/MCUInit/systick.o MotorLib/MCUInit/vadc.o MotorLib/MidSys/bldc_scalar_current_motor.o MotorLib/MidSys/bldc_scalar_pwm_bc.o MotorLib/MidSys/bldc_scalar_speed_pos_hall.o MotorLib/MidSys/bldc_scalar_volt_dcbus.o MotorLib/MidSys/bldc_scalar_volt_potentiometer.o MotorLib/MidSys/bldc_scalar_volt_userdef.o MotorLib/bldc_scalar_user_interface.o MotorLib/bldc_scalar_variables_config.o MotorLib/motor.o Startup/startup_XMC4700.o Startup/system_XMC4700.o main.o  _PKDS_TSTS06_811_X47_V1_0.elf $(LIST_FILES) $(MAP_FILE) objects.rsp
	-@echo.
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
