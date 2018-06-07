################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../TetirisUser.cpp \
../TetrisSocket.cpp \
../Validator.cpp 

OBJS += \
./TetirisUser.o \
./TetrisSocket.o \
./Validator.o 

CPP_DEPS += \
./TetirisUser.d \
./TetrisSocket.d \
./Validator.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++14 -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


