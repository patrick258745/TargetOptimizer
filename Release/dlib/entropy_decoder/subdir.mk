################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../dlib/entropy_decoder/entropy_decoder_kernel_1.cpp \
../dlib/entropy_decoder/entropy_decoder_kernel_2.cpp 

OBJS += \
./dlib/entropy_decoder/entropy_decoder_kernel_1.o \
./dlib/entropy_decoder/entropy_decoder_kernel_2.o 

CPP_DEPS += \
./dlib/entropy_decoder/entropy_decoder_kernel_1.d \
./dlib/entropy_decoder/entropy_decoder_kernel_2.d 


# Each subdirectory must supply rules for building sources it contributes
dlib/entropy_decoder/%.o: ../dlib/entropy_decoder/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

