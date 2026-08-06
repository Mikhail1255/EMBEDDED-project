################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../includes/ADC_prog.c \
../includes/DIO_prog.c \
../includes/EXTI_prog.c \
../includes/GIE_prog.c \
../includes/KEYBAD_prog.c \
../includes/LCD_prog.c \
../includes/TIM0_prog.c 

OBJS += \
./includes/ADC_prog.o \
./includes/DIO_prog.o \
./includes/EXTI_prog.o \
./includes/GIE_prog.o \
./includes/KEYBAD_prog.o \
./includes/LCD_prog.o \
./includes/TIM0_prog.o 

C_DEPS += \
./includes/ADC_prog.d \
./includes/DIO_prog.d \
./includes/EXTI_prog.d \
./includes/GIE_prog.d \
./includes/KEYBAD_prog.d \
./includes/LCD_prog.d \
./includes/TIM0_prog.d 


# Each subdirectory must supply rules for building sources it contributes
includes/%.o: ../includes/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


