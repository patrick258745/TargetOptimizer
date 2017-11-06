################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../dlib/dnn/cpu_dlib.cpp \
../dlib/dnn/cublas_dlibapi.cpp \
../dlib/dnn/cudnn_dlibapi.cpp \
../dlib/dnn/curand_dlibapi.cpp \
../dlib/dnn/gpu_data.cpp \
../dlib/dnn/tensor_tools.cpp 

OBJS += \
./dlib/dnn/cpu_dlib.o \
./dlib/dnn/cublas_dlibapi.o \
./dlib/dnn/cudnn_dlibapi.o \
./dlib/dnn/curand_dlibapi.o \
./dlib/dnn/gpu_data.o \
./dlib/dnn/tensor_tools.o 

CPP_DEPS += \
./dlib/dnn/cpu_dlib.d \
./dlib/dnn/cublas_dlibapi.d \
./dlib/dnn/cudnn_dlibapi.d \
./dlib/dnn/curand_dlibapi.d \
./dlib/dnn/gpu_data.d \
./dlib/dnn/tensor_tools.d 


# Each subdirectory must supply rules for building sources it contributes
dlib/dnn/%.o: ../dlib/dnn/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


