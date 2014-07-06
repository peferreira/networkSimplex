################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Arc.cpp \
../src/Graph.cpp \
../src/InputReader.cpp \
../src/SimplexForNetworks.cpp \
../src/simplex_for_networks.cpp 

OBJS += \
./src/Arc.o \
./src/Graph.o \
./src/InputReader.o \
./src/SimplexForNetworks.o \
./src/simplex_for_networks.o 

CPP_DEPS += \
./src/Arc.d \
./src/Graph.d \
./src/InputReader.d \
./src/SimplexForNetworks.d \
./src/simplex_for_networks.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


