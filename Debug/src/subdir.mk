################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
../src/lscript\ -\ Copy.ld \
../src/lscript.ld 

C_SRCS += \
../src/ftl.c \
../src/host_controller.c \
../src/identify.c \
../src/lld.c \
../src/main.c \
../src/pagemap.c \
../src/req_handler.c 

OBJS += \
./src/ftl.o \
./src/host_controller.o \
./src/identify.o \
./src/lld.o \
./src/main.o \
./src/pagemap.o \
./src/req_handler.o 

C_DEPS += \
./src/ftl.d \
./src/host_controller.d \
./src/identify.d \
./src/lld.d \
./src/main.d \
./src/pagemap.d \
./src/req_handler.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -I../../GreedyFTL_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


