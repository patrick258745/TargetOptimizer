################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../dlib/external/zlib/adler32.c \
../dlib/external/zlib/compress.c \
../dlib/external/zlib/crc32.c \
../dlib/external/zlib/deflate.c \
../dlib/external/zlib/gzclose.c \
../dlib/external/zlib/gzlib.c \
../dlib/external/zlib/gzread.c \
../dlib/external/zlib/gzwrite.c \
../dlib/external/zlib/infback.c \
../dlib/external/zlib/inffast.c \
../dlib/external/zlib/inflate.c \
../dlib/external/zlib/inftrees.c \
../dlib/external/zlib/trees.c \
../dlib/external/zlib/uncompr.c \
../dlib/external/zlib/zutil.c 

OBJS += \
./dlib/external/zlib/adler32.o \
./dlib/external/zlib/compress.o \
./dlib/external/zlib/crc32.o \
./dlib/external/zlib/deflate.o \
./dlib/external/zlib/gzclose.o \
./dlib/external/zlib/gzlib.o \
./dlib/external/zlib/gzread.o \
./dlib/external/zlib/gzwrite.o \
./dlib/external/zlib/infback.o \
./dlib/external/zlib/inffast.o \
./dlib/external/zlib/inflate.o \
./dlib/external/zlib/inftrees.o \
./dlib/external/zlib/trees.o \
./dlib/external/zlib/uncompr.o \
./dlib/external/zlib/zutil.o 

C_DEPS += \
./dlib/external/zlib/adler32.d \
./dlib/external/zlib/compress.d \
./dlib/external/zlib/crc32.d \
./dlib/external/zlib/deflate.d \
./dlib/external/zlib/gzclose.d \
./dlib/external/zlib/gzlib.d \
./dlib/external/zlib/gzread.d \
./dlib/external/zlib/gzwrite.d \
./dlib/external/zlib/infback.d \
./dlib/external/zlib/inffast.d \
./dlib/external/zlib/inflate.d \
./dlib/external/zlib/inftrees.d \
./dlib/external/zlib/trees.d \
./dlib/external/zlib/uncompr.d \
./dlib/external/zlib/zutil.d 


# Each subdirectory must supply rules for building sources it contributes
dlib/external/zlib/%.o: ../dlib/external/zlib/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


