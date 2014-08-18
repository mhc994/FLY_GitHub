################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := D:/ti/ccs6/ccsv6/tools/compiler/c2000_6.2.6

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
-l"rts2800_fpu32_fast_supplement.lib" \
-l"rts2800_fpu32.lib" \
"./TiFiles/F2806x_usDelay.obj" \
"./TiFiles/F2806x_SysCtrl.obj" \
"./TiFiles/F2806x_Spi.obj" \
"./TiFiles/F2806x_Sci.obj" \
"./TiFiles/F2806x_PieVect.obj" \
"./TiFiles/F2806x_PieCtrl.obj" \
"./TiFiles/F2806x_I2C.obj" \
"./TiFiles/F2806x_HRCap.obj" \
"./TiFiles/F2806x_Gpio.obj" \
"./TiFiles/F2806x_GlobalVariableDefs.obj" \
"./TiFiles/F2806x_EPwm.obj" \
"./TiFiles/F2806x_ECap.obj" \
"./TiFiles/F2806x_DefaultIsr.obj" \
"./TiFiles/F2806x_CpuTimers.obj" \
"./TiFiles/F2806x_CodeStartBranch.obj" \
"./mhcFiles/num2string.obj" \
"./mhcFiles/mhc_initDSP.obj" \
"./mhcFiles/mhc_ePWM.obj" \
"./mhcFiles/mhc_eCap.obj" \
"./mhcFiles/mhc_doData.obj" \
"./mhcFiles/mhc_cpuTimer.obj" \
"./mhcFiles/mhc_control.obj" \
"./mhcFiles/mhc_SPI.obj" \
"./mhcFiles/mhc_SCIB_S_BUS.obj" \
"./mhcFiles/mhc_SCIA.obj" \
"./mhcFiles/mhc_I2C.obj" \
"./mhcFiles/mhc_GlobalVariables.obj" \
"./mhcFiles/main.obj" \
"../28069_RAM_lnk.cmd" \
"../F2806x_Headers_nonBIOS.cmd" \
-l"IQmath_fpu32.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include mhcFiles/subdir_vars.mk
-include TiFiles/subdir_vars.mk
-include subdir_rules.mk
-include mhcFiles/subdir_rules.mk
-include TiFiles/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
Example_2806xEPwmDeadBand.out \

EXE_OUTPUTS__QUOTED += \
"Example_2806xEPwmDeadBand.out" \

BIN_OUTPUTS += \
Example_2806xEPwmDeadBand.hex \

BIN_OUTPUTS__QUOTED += \
"Example_2806xEPwmDeadBand.hex" \


# All Target
all: Example_2806xEPwmDeadBand.out

# Tool invocations
Example_2806xEPwmDeadBand.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo '正在调用： C2000 Linker'
	"D:/ti/ccs6/ccsv6/tools/compiler/c2000_6.2.6/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --verbose_diagnostics --diag_warning=225 --issue_remarks --output_all_syms --cdebug_asm_data -z -m"Example_2806xEPwmDeadBand.map" --stack_size=0x200 --warn_sections -i"D:/ti/ccs6/ccsv6/tools/compiler/c2000_6.2.6/lib" -i"D:/ti/ccs6/ccsv6/tools/compiler/c2000_6.2.6/include" -i"D:/ti/controlSUITE/device_support/f2806x/v136/F2806x_common/lib" -i"D:/ti/controlSUITE/libs/math/IQmath/v160/lib" -i"D:/ti/controlSUITE/libs/math/FPUfastRTS/V100/lib" --reread_libs --priority --verbose_diagnostics --issue_remarks --xml_link_info="Example_2806xEPwmDeadBand_linkInfo.xml" --entry_point=code_start --rom_model -o "Example_2806xEPwmDeadBand.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

Example_2806xEPwmDeadBand.hex: $(EXE_OUTPUTS)
	@echo '正在调用： C2000 Hex Utility'
	"D:/ti/ccs6/ccsv6/tools/compiler/c2000_6.2.6/bin/hex2000"  -o "Example_2806xEPwmDeadBand.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "mhcFiles\main.pp" "mhcFiles\mhc_GlobalVariables.pp" "mhcFiles\mhc_I2C.pp" "mhcFiles\mhc_SCIA.pp" "mhcFiles\mhc_SCIB_S_BUS.pp" "mhcFiles\mhc_SPI.pp" "mhcFiles\mhc_control.pp" "mhcFiles\mhc_cpuTimer.pp" "mhcFiles\mhc_doData.pp" "mhcFiles\mhc_eCap.pp" "mhcFiles\mhc_ePWM.pp" "mhcFiles\mhc_initDSP.pp" "mhcFiles\num2string.pp" "TiFiles\F2806x_CpuTimers.pp" "TiFiles\F2806x_DefaultIsr.pp" "TiFiles\F2806x_ECap.pp" "TiFiles\F2806x_EPwm.pp" "TiFiles\F2806x_GlobalVariableDefs.pp" "TiFiles\F2806x_Gpio.pp" "TiFiles\F2806x_HRCap.pp" "TiFiles\F2806x_I2C.pp" "TiFiles\F2806x_PieCtrl.pp" "TiFiles\F2806x_PieVect.pp" "TiFiles\F2806x_Sci.pp" "TiFiles\F2806x_Spi.pp" "TiFiles\F2806x_SysCtrl.pp" 
	-$(RM) "mhcFiles\main.obj" "mhcFiles\mhc_GlobalVariables.obj" "mhcFiles\mhc_I2C.obj" "mhcFiles\mhc_SCIA.obj" "mhcFiles\mhc_SCIB_S_BUS.obj" "mhcFiles\mhc_SPI.obj" "mhcFiles\mhc_control.obj" "mhcFiles\mhc_cpuTimer.obj" "mhcFiles\mhc_doData.obj" "mhcFiles\mhc_eCap.obj" "mhcFiles\mhc_ePWM.obj" "mhcFiles\mhc_initDSP.obj" "mhcFiles\num2string.obj" "TiFiles\F2806x_CodeStartBranch.obj" "TiFiles\F2806x_CpuTimers.obj" "TiFiles\F2806x_DefaultIsr.obj" "TiFiles\F2806x_ECap.obj" "TiFiles\F2806x_EPwm.obj" "TiFiles\F2806x_GlobalVariableDefs.obj" "TiFiles\F2806x_Gpio.obj" "TiFiles\F2806x_HRCap.obj" "TiFiles\F2806x_I2C.obj" "TiFiles\F2806x_PieCtrl.obj" "TiFiles\F2806x_PieVect.obj" "TiFiles\F2806x_Sci.obj" "TiFiles\F2806x_Spi.obj" "TiFiles\F2806x_SysCtrl.obj" "TiFiles\F2806x_usDelay.obj" 
	-$(RM) "TiFiles\F2806x_CodeStartBranch.pp" "TiFiles\F2806x_usDelay.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

