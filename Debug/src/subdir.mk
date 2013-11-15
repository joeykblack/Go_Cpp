################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/BitBoard.cpp \
../src/BoardState.cpp \
../src/GameState.cpp \
../src/SetupCommands.cpp \
../src/SysCommands.cpp \
../src/complexOpps.cpp \
../src/config.cpp \
../src/main.cpp \
../src/util.cpp 

OBJS += \
./src/BitBoard.o \
./src/BoardState.o \
./src/GameState.o \
./src/SetupCommands.o \
./src/SysCommands.o \
./src/complexOpps.o \
./src/config.o \
./src/main.o \
./src/util.o 

CPP_DEPS += \
./src/BitBoard.d \
./src/BoardState.d \
./src/GameState.d \
./src/SetupCommands.d \
./src/SysCommands.d \
./src/complexOpps.d \
./src/config.d \
./src/main.d \
./src/util.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/joey/boost_1_47_0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


