################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../FileWatcher/FileWatcher.cpp 

OBJS += \
./FileWatcher/FileWatcher.o 

CPP_DEPS += \
./FileWatcher/FileWatcher.d 


# Each subdirectory must supply rules for building sources it contributes
FileWatcher/%.o: ../FileWatcher/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


