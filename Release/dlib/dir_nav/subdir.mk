################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../dlib/dir_nav/dir_nav_extensions.cpp \
../dlib/dir_nav/dir_nav_kernel_1.cpp \
../dlib/dir_nav/dir_nav_kernel_2.cpp 

OBJS += \
./dlib/dir_nav/dir_nav_extensions.o \
./dlib/dir_nav/dir_nav_kernel_1.o \
./dlib/dir_nav/dir_nav_kernel_2.o 

CPP_DEPS += \
./dlib/dir_nav/dir_nav_extensions.d \
./dlib/dir_nav/dir_nav_kernel_1.d \
./dlib/dir_nav/dir_nav_kernel_2.d 


# Each subdirectory must supply rules for building sources it contributes
dlib/dir_nav/%.o: ../dlib/dir_nav/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


