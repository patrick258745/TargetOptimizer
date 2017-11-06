################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../dlib/dnn/test_for_cpp11/cpp11_test.cpp 

OBJS += \
./dlib/dnn/test_for_cpp11/cpp11_test.o 

CPP_DEPS += \
./dlib/dnn/test_for_cpp11/cpp11_test.d 


# Each subdirectory must supply rules for building sources it contributes
dlib/dnn/test_for_cpp11/%.o: ../dlib/dnn/test_for_cpp11/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


