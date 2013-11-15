################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/test/TestComplexOpps.cpp \
../src/test/TestGreedyPlayer.cpp \
../src/test/TestRndPlayer.cpp \
../src/test/TestUCTNode.cpp 

OBJS += \
./src/test/TestComplexOpps.o \
./src/test/TestGreedyPlayer.o \
./src/test/TestRndPlayer.o \
./src/test/TestUCTNode.o 

CPP_DEPS += \
./src/test/TestComplexOpps.d \
./src/test/TestGreedyPlayer.d \
./src/test/TestRndPlayer.d \
./src/test/TestUCTNode.d 


# Each subdirectory must supply rules for building sources it contributes
src/test/%.o: ../src/test/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/home/joey/boost_1_47_0 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


