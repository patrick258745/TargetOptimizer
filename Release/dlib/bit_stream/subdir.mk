################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../dlib/bit_stream/bit_stream_kernel_1.cpp 

OBJS += \
./dlib/bit_stream/bit_stream_kernel_1.o 

CPP_DEPS += \
./dlib/bit_stream/bit_stream_kernel_1.d 


# Each subdirectory must supply rules for building sources it contributes
dlib/bit_stream/%.o: ../dlib/bit_stream/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


