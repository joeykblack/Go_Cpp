################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../boost/test/utils/runtime/file/config_file.cpp \
../boost/test/utils/runtime/file/config_file_iterator.cpp 

OBJS += \
./boost/test/utils/runtime/file/config_file.o \
./boost/test/utils/runtime/file/config_file_iterator.o 

CPP_DEPS += \
./boost/test/utils/runtime/file/config_file.d \
./boost/test/utils/runtime/file/config_file_iterator.d 


# Each subdirectory must supply rules for building sources it contributes
boost/test/utils/runtime/file/%.o: ../boost/test/utils/runtime/file/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


