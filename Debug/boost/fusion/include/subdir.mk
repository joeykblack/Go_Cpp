################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../boost/fusion/include/adapt_adt_named.cpp 

OBJS += \
./boost/fusion/include/adapt_adt_named.o 

CPP_DEPS += \
./boost/fusion/include/adapt_adt_named.d 


# Each subdirectory must supply rules for building sources it contributes
boost/fusion/include/%.o: ../boost/fusion/include/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


