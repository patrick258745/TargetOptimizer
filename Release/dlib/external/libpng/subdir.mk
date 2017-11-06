################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../dlib/external/libpng/png.c \
../dlib/external/libpng/pngerror.c \
../dlib/external/libpng/pngget.c \
../dlib/external/libpng/pngmem.c \
../dlib/external/libpng/pngpread.c \
../dlib/external/libpng/pngread.c \
../dlib/external/libpng/pngrio.c \
../dlib/external/libpng/pngrtran.c \
../dlib/external/libpng/pngrutil.c \
../dlib/external/libpng/pngset.c \
../dlib/external/libpng/pngtrans.c \
../dlib/external/libpng/pngwio.c \
../dlib/external/libpng/pngwrite.c \
../dlib/external/libpng/pngwtran.c \
../dlib/external/libpng/pngwutil.c 

OBJS += \
./dlib/external/libpng/png.o \
./dlib/external/libpng/pngerror.o \
./dlib/external/libpng/pngget.o \
./dlib/external/libpng/pngmem.o \
./dlib/external/libpng/pngpread.o \
./dlib/external/libpng/pngread.o \
./dlib/external/libpng/pngrio.o \
./dlib/external/libpng/pngrtran.o \
./dlib/external/libpng/pngrutil.o \
./dlib/external/libpng/pngset.o \
./dlib/external/libpng/pngtrans.o \
./dlib/external/libpng/pngwio.o \
./dlib/external/libpng/pngwrite.o \
./dlib/external/libpng/pngwtran.o \
./dlib/external/libpng/pngwutil.o 

C_DEPS += \
./dlib/external/libpng/png.d \
./dlib/external/libpng/pngerror.d \
./dlib/external/libpng/pngget.d \
./dlib/external/libpng/pngmem.d \
./dlib/external/libpng/pngpread.d \
./dlib/external/libpng/pngread.d \
./dlib/external/libpng/pngrio.d \
./dlib/external/libpng/pngrtran.d \
./dlib/external/libpng/pngrutil.d \
./dlib/external/libpng/pngset.d \
./dlib/external/libpng/pngtrans.d \
./dlib/external/libpng/pngwio.d \
./dlib/external/libpng/pngwrite.d \
./dlib/external/libpng/pngwtran.d \
./dlib/external/libpng/pngwutil.d 


# Each subdirectory must supply rules for building sources it contributes
dlib/external/libpng/%.o: ../dlib/external/libpng/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


