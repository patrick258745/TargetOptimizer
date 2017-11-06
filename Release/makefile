################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include dlib/unicode/subdir.mk
-include dlib/tokenizer/subdir.mk
-include dlib/timer/subdir.mk
-include dlib/threads/subdir.mk
-include dlib/test/gui/subdir.mk
-include dlib/test/blas_bindings/subdir.mk
-include dlib/test/subdir.mk
-include dlib/sockstreambuf/subdir.mk
-include dlib/sockets/subdir.mk
-include dlib/server/subdir.mk
-include dlib/misc_api/subdir.mk
-include dlib/md5/subdir.mk
-include dlib/matlab/subdir.mk
-include dlib/logger/subdir.mk
-include dlib/linker/subdir.mk
-include dlib/image_saver/subdir.mk
-include dlib/image_loader/subdir.mk
-include dlib/http_client/subdir.mk
-include dlib/gui_widgets/subdir.mk
-include dlib/gui_core/subdir.mk
-include dlib/external/zlib/subdir.mk
-include dlib/external/libpng/subdir.mk
-include dlib/external/libjpeg/subdir.mk
-include dlib/external/cblas/subdir.mk
-include dlib/entropy_encoder/subdir.mk
-include dlib/entropy_decoder/subdir.mk
-include dlib/dnn/test_for_cpp11/subdir.mk
-include dlib/dnn/subdir.mk
-include dlib/dir_nav/subdir.mk
-include dlib/data_io/subdir.mk
-include dlib/bsp/subdir.mk
-include dlib/bit_stream/subdir.mk
-include dlib/bigint/subdir.mk
-include dlib/base64/subdir.mk
-include dlib/all/subdir.mk
-include dlib/subdir.mk
-include build/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: TargetOptimizer

# Tool invocations
TargetOptimizer: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross G++ Linker'
	g++  -o "TargetOptimizer" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(C_DEPS)$(CPP_DEPS) TargetOptimizer
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
