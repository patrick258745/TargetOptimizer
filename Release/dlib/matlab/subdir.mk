################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../dlib/matlab/example_mex_callback.cpp \
../dlib/matlab/example_mex_function.cpp \
../dlib/matlab/example_mex_struct.cpp \
../dlib/matlab/mex_wrapper.cpp \
../dlib/matlab/subprocess_stream.cpp 

OBJS += \
./dlib/matlab/example_mex_callback.o \
./dlib/matlab/example_mex_function.o \
./dlib/matlab/example_mex_struct.o \
./dlib/matlab/mex_wrapper.o \
./dlib/matlab/subprocess_stream.o 

CPP_DEPS += \
./dlib/matlab/example_mex_callback.d \
./dlib/matlab/example_mex_function.d \
./dlib/matlab/example_mex_struct.d \
./dlib/matlab/mex_wrapper.d \
./dlib/matlab/subprocess_stream.d 


# Each subdirectory must supply rules for building sources it contributes
dlib/matlab/%.o: ../dlib/matlab/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


