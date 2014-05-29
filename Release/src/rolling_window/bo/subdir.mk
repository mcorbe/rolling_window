################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/rolling_window/bo/RollingWindowBO.cc 

OBJS += \
./src/rolling_window/bo/RollingWindowBO.o 

CC_DEPS += \
./src/rolling_window/bo/RollingWindowBO.d 


# Each subdirectory must supply rules for building sources it contributes
src/rolling_window/bo/%.o: ../src/rolling_window/bo/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/rapidape/dev/workspace/stream/rolling_window/src" -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


