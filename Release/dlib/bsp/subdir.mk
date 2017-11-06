################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../dlib/bsp/bsp.cpp 

OBJS += \
./dlib/bsp/bsp.o 

CPP_DEPS += \
./dlib/bsp/bsp.d 


# Each subdirectory must supply rules for building sources it contributes
dlib/bsp/%.o: ../dlib/bsp/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


