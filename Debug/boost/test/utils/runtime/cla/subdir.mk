################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../boost/test/utils/runtime/cla/argv_traverser.cpp \
../boost/test/utils/runtime/cla/char_parameter.cpp \
../boost/test/utils/runtime/cla/dual_name_parameter.cpp \
../boost/test/utils/runtime/cla/id_policy.cpp \
../boost/test/utils/runtime/cla/named_parameter.cpp \
../boost/test/utils/runtime/cla/parser.cpp \
../boost/test/utils/runtime/cla/validation.cpp 

OBJS += \
./boost/test/utils/runtime/cla/argv_traverser.o \
./boost/test/utils/runtime/cla/char_parameter.o \
./boost/test/utils/runtime/cla/dual_name_parameter.o \
./boost/test/utils/runtime/cla/id_policy.o \
./boost/test/utils/runtime/cla/named_parameter.o \
./boost/test/utils/runtime/cla/parser.o \
./boost/test/utils/runtime/cla/validation.o 

CPP_DEPS += \
./boost/test/utils/runtime/cla/argv_traverser.d \
./boost/test/utils/runtime/cla/char_parameter.d \
./boost/test/utils/runtime/cla/dual_name_parameter.d \
./boost/test/utils/runtime/cla/id_policy.d \
./boost/test/utils/runtime/cla/named_parameter.d \
./boost/test/utils/runtime/cla/parser.d \
./boost/test/utils/runtime/cla/validation.d 


# Each subdirectory must supply rules for building sources it contributes
boost/test/utils/runtime/cla/%.o: ../boost/test/utils/runtime/cla/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


