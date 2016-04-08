################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../FrontEnd.o 

CPP_SRCS += \
../Account.cpp \
../AdminTransaction.cpp \
../ConsoleGui.cpp \
../Transaction.cpp \
../main.cpp 

OBJS += \
./Account.o \
./AdminTransaction.o \
./ConsoleGui.o \
./Transaction.o \
./main.o 

CPP_DEPS += \
./Account.d \
./AdminTransaction.d \
./ConsoleGui.d \
./Transaction.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++11 -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


