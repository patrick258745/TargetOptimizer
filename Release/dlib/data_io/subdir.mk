################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../dlib/data_io/image_dataset_metadata.cpp \
../dlib/data_io/mnist.cpp 

OBJS += \
./dlib/data_io/image_dataset_metadata.o \
./dlib/data_io/mnist.o 

CPP_DEPS += \
./dlib/data_io/image_dataset_metadata.d \
./dlib/data_io/mnist.d 


# Each subdirectory must supply rules for building sources it contributes
dlib/data_io/%.o: ../dlib/data_io/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


