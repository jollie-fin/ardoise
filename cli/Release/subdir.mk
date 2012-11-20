################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Cadre.cpp \
../Saisie_texte.cpp \
../Widget.cpp \
../main.cpp 

OBJS += \
./Cadre.o \
./Saisie_texte.o \
./Widget.o \
./main.o 

CPP_DEPS += \
./Cadre.d \
./Saisie_texte.d \
./Widget.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Compilateur C++ GCC'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


