################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/ai/AI.cpp \
../src/ai/MCAgent.cpp \
../src/ai/MCUCTAgent.cpp \
../src/ai/RAVEManager.cpp \
../src/ai/RndPlayer.cpp \
../src/ai/UCTNode.cpp 

OBJS += \
./src/ai/AI.o \
./src/ai/MCAgent.o \
./src/ai/MCUCTAgent.o \
./src/ai/RAVEManager.o \
./src/ai/RndPlayer.o \
./src/ai/UCTNode.o 

CPP_DEPS += \
./src/ai/AI.d \
./src/ai/MCAgent.d \
./src/ai/MCUCTAgent.d \
./src/ai/RAVEManager.d \
./src/ai/RndPlayer.d \
./src/ai/UCTNode.d 


# Each subdirectory must supply rules for building sources it contributes
src/ai/%.o: ../src/ai/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/joey/boost_1_47_0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


