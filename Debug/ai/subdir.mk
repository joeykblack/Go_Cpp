################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ai/AI.cpp \
../ai/MCAgent.cpp \
../ai/MCUCTAgent.cpp \
../ai/RAVEManager.cpp \
../ai/RndPlayer.cpp \
../ai/UCTNode.cpp 

OBJS += \
./ai/AI.o \
./ai/MCAgent.o \
./ai/MCUCTAgent.o \
./ai/RAVEManager.o \
./ai/RndPlayer.o \
./ai/UCTNode.o 

CPP_DEPS += \
./ai/AI.d \
./ai/MCAgent.d \
./ai/MCUCTAgent.d \
./ai/RAVEManager.d \
./ai/RndPlayer.d \
./ai/UCTNode.d 


# Each subdirectory must supply rules for building sources it contributes
ai/%.o: ../ai/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/joey/boost_1_47_0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


