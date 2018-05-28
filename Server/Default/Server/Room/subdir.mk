################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Server/Room/GameRoom.cpp \
../Server/Room/Room.cpp \
../Server/Room/WaitingRoom.cpp 

OBJS += \
./Server/Room/GameRoom.o \
./Server/Room/Room.o \
./Server/Room/WaitingRoom.o 

CPP_DEPS += \
./Server/Room/GameRoom.d \
./Server/Room/Room.d \
./Server/Room/WaitingRoom.d 


# Each subdirectory must supply rules for building sources it contributes
Server/Room/%.o: ../Server/Room/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -std=c++1y -I"/home/pi/workspace/OnlineTetris/Commons" -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


