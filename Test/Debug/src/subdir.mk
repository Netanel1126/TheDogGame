################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ClientTest.cpp \
../src/GameTest.cpp \
../src/ServerTest.cpp \
../src/test.cpp 

OBJS += \
./src/ClientTest.o \
./src/GameTest.o \
./src/ServerTest.o \
./src/test.o 

CPP_DEPS += \
./src/ClientTest.d \
./src/GameTest.d \
./src/ServerTest.d \
./src/test.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/user/TheDogGame/GameServer/src" -I"/home/user/TheDogGame/GameClient/src" -I"/home/user/TheDogGame/MyUtils/src" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


