################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../dlib/server/server_http.cpp \
../dlib/server/server_iostream.cpp \
../dlib/server/server_kernel.cpp 

OBJS += \
./dlib/server/server_http.o \
./dlib/server/server_iostream.o \
./dlib/server/server_kernel.o 

CPP_DEPS += \
./dlib/server/server_http.d \
./dlib/server/server_iostream.d \
./dlib/server/server_kernel.d 


# Each subdirectory must supply rules for building sources it contributes
dlib/server/%.o: ../dlib/server/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


