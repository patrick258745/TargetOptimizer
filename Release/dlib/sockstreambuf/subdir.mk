################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../dlib/sockstreambuf/sockstreambuf.cpp \
../dlib/sockstreambuf/sockstreambuf_unbuffered.cpp 

OBJS += \
./dlib/sockstreambuf/sockstreambuf.o \
./dlib/sockstreambuf/sockstreambuf_unbuffered.o 

CPP_DEPS += \
./dlib/sockstreambuf/sockstreambuf.d \
./dlib/sockstreambuf/sockstreambuf_unbuffered.d 


# Each subdirectory must supply rules for building sources it contributes
dlib/sockstreambuf/%.o: ../dlib/sockstreambuf/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


