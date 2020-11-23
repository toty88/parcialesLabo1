################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Cliente.c \
../src/Cliente_Venta.c \
../src/Controller.c \
../src/LinkedList.c \
../src/Venta.c \
../src/main.c \
../src/menu.c \
../src/parser.c \
../src/utn.c 

OBJS += \
./src/Cliente.o \
./src/Cliente_Venta.o \
./src/Controller.o \
./src/LinkedList.o \
./src/Venta.o \
./src/main.o \
./src/menu.o \
./src/parser.o \
./src/utn.o 

C_DEPS += \
./src/Cliente.d \
./src/Cliente_Venta.d \
./src/Controller.d \
./src/LinkedList.d \
./src/Venta.d \
./src/main.d \
./src/menu.d \
./src/parser.d \
./src/utn.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


