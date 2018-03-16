################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := cs-rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include commonEclipse/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
pr3.hex \

SECONDARY_LIST += \
pr3.lst \

SECONDARY_SIZE += \
pr3.siz \


# All Target
all: pr3.elf secondary-outputs

# Tool invocations
pr3.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Sourcery Windows GCC C Linker'
	arm-none-eabi-gcc -T"C:\hlocal\EclipseARMwspace\pr3\commonEclipse\ld_script_iic.ld" -nostartfiles -L"/../sourcery-g++-lite-arm-2011.03/armnone-eabi/lib" -L"/../sourcery-g++-lite-arm-2011.03/lib/gcc/arm-noneeabi/4.5.2" -L"C:\hlocal\EclipseARMwspace\pr3\commonEclipse" -Wl,-Map,pr3.map -mcpu=arm7tdmi -g3 -gdwarf-2 -o "pr3.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

pr3.hex: pr3.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Flash Image'
	arm-none-eabi-objcopy -O binary pr3.elf  "pr3.hex"
	@echo 'Finished building: $@'
	@echo ' '

pr3.lst: pr3.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Listing'
	arm-none-eabi-objdump -h -S pr3.elf > "pr3.lst"
	@echo 'Finished building: $@'
	@echo ' '

pr3.siz: pr3.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Print Size'
	arm-none-eabi-size  --format=berkeley pr3.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(EXECUTABLES)$(SECONDARY_LIST)$(S_UPPER_DEPS) pr3.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
