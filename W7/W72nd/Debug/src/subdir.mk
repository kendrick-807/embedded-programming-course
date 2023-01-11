################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BarGraph.cpp \
../src/DecimalEdit.cpp \
../src/DigitalIoPin.cpp \
../src/IntegerEdit.cpp \
../src/LiquidCrystal.cpp \
../src/LpcUart.cpp \
../src/MenuItem.cpp \
../src/SimpleMenu.cpp \
../src/W72nd.cpp \
../src/W7hw2.cpp \
../src/cr_cpp_config.cpp \
../src/cr_startup_lpc15xx.cpp 

C_SRCS += \
../src/crp.c \
../src/sysinit.c 

CPP_DEPS += \
./src/BarGraph.d \
./src/DecimalEdit.d \
./src/DigitalIoPin.d \
./src/IntegerEdit.d \
./src/LiquidCrystal.d \
./src/LpcUart.d \
./src/MenuItem.d \
./src/SimpleMenu.d \
./src/W72nd.d \
./src/W7hw2.d \
./src/cr_cpp_config.d \
./src/cr_startup_lpc15xx.d 

C_DEPS += \
./src/crp.d \
./src/sysinit.d 

OBJS += \
./src/BarGraph.o \
./src/DecimalEdit.o \
./src/DigitalIoPin.o \
./src/IntegerEdit.o \
./src/LiquidCrystal.o \
./src/LpcUart.o \
./src/MenuItem.o \
./src/SimpleMenu.o \
./src/W72nd.o \
./src/W7hw2.o \
./src/cr_cpp_config.o \
./src/cr_startup_lpc15xx.o \
./src/crp.o \
./src/sysinit.o 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C++ Compiler'
	arm-none-eabi-c++ -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC15XX__ -I"/Users/kendrick807/Documents/MCUXpressoIDE_11.6.0_8187/workspace/lpc_board_nxp_lpcxpresso_1549/inc" -I"/Users/kendrick807/Documents/MCUXpressoIDE_11.6.0_8187/workspace/lpc_chip_15xx/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=c11 -DDEBUG -D__CODE_RED -D__NEWLIB__ -DCORE_M3 -D__USE_LPCOPEN -DCPP_USE_HEAP -D__LPC15XX__ -I"/Users/kendrick807/Documents/MCUXpressoIDE_11.6.0_8187/workspace/lpc_board_nxp_lpcxpresso_1549/inc" -I"/Users/kendrick807/Documents/MCUXpressoIDE_11.6.0_8187/workspace/lpc_chip_15xx/inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m3 -mthumb -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-src

clean-src:
	-$(RM) ./src/BarGraph.d ./src/BarGraph.o ./src/DecimalEdit.d ./src/DecimalEdit.o ./src/DigitalIoPin.d ./src/DigitalIoPin.o ./src/IntegerEdit.d ./src/IntegerEdit.o ./src/LiquidCrystal.d ./src/LiquidCrystal.o ./src/LpcUart.d ./src/LpcUart.o ./src/MenuItem.d ./src/MenuItem.o ./src/SimpleMenu.d ./src/SimpleMenu.o ./src/W72nd.d ./src/W72nd.o ./src/W7hw2.d ./src/W7hw2.o ./src/cr_cpp_config.d ./src/cr_cpp_config.o ./src/cr_startup_lpc15xx.d ./src/cr_startup_lpc15xx.o ./src/crp.d ./src/crp.o ./src/sysinit.d ./src/sysinit.o

.PHONY: clean-src

