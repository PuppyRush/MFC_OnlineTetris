################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Server/ServerManager.cpp \
../Server/ServerSocket.cpp \
../Server/TetrisUserServer.cpp 

OBJS += \
./Server/ServerManager.o \
./Server/ServerSocket.o \
./Server/TetrisUserServer.o 

CPP_DEPS += \
./Server/ServerManager.d \
./Server/ServerSocket.d \
./Server/TetrisUserServer.d 


# Each subdirectory must supply rules for building sources it contributes
Server/%.o: ../Server/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -I"/home/pi/workspace/OnlineTetris/Commons" -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


