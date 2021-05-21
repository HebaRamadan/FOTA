################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DIO_Program.c \
../src/ESP_Program.c \
../src/FPEC_Program.c \
../src/LED_Program.c \
../src/NVIC_Program.c \
../src/Parse.c \
../src/RCC_Program.c \
../src/SyStick_Program.c \
../src/Timer_Program.c \
../src/UART_Program.c \
../src/main.c 

OBJS += \
./src/DIO_Program.o \
./src/ESP_Program.o \
./src/FPEC_Program.o \
./src/LED_Program.o \
./src/NVIC_Program.o \
./src/Parse.o \
./src/RCC_Program.o \
./src/SyStick_Program.o \
./src/Timer_Program.o \
./src/UART_Program.o \
./src/main.o 

C_DEPS += \
./src/DIO_Program.d \
./src/ESP_Program.d \
./src/FPEC_Program.d \
./src/LED_Program.d \
./src/NVIC_Program.d \
./src/Parse.d \
./src/RCC_Program.d \
./src/SyStick_Program.d \
./src/Timer_Program.d \
./src/UART_Program.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DDEBUG -DUSE_FULL_ASSERT -DTRACE -DOS_USE_TRACE_SEMIHOSTING_DEBUG -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=8000000 -I"../include" -I"../system/include" -I"../system/include/cmsis" -I"../system/include/stm32f1-stdperiph" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


