################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/MThread.cpp \
../src/MultipleTCPSocketsListener.cpp \
../src/TCPSocket.cpp \
../src/TCPp2pMessenger.cpp \
../src/TCPp2pServerClient.cpp \
../src/UDPSocket.cpp 

OBJS += \
./src/MThread.o \
./src/MultipleTCPSocketsListener.o \
./src/TCPSocket.o \
./src/TCPp2pMessenger.o \
./src/TCPp2pServerClient.o \
./src/UDPSocket.o 

CPP_DEPS += \
./src/MThread.d \
./src/MultipleTCPSocketsListener.d \
./src/TCPSocket.d \
./src/TCPp2pMessenger.d \
./src/TCPp2pServerClient.d \
./src/UDPSocket.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


