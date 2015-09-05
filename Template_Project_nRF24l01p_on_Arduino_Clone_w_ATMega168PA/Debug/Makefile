################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../ADC.c \
../AVRTemplateApp.c \
../BaseTmr.c \
../Dio_Driver.c \
../mirf.c \
../Port.c \
../spi.c \
../UART.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
ADC.o \
AVRTemplateApp.o \
BaseTmr.o \
Dio_Driver.o \
mirf.o \
Port.o \
spi.o \
UART.o

OBJS_AS_ARGS +=  \
ADC.o \
AVRTemplateApp.o \
BaseTmr.o \
Dio_Driver.o \
mirf.o \
Port.o \
spi.o \
UART.o

C_DEPS +=  \
ADC.d \
AVRTemplateApp.d \
BaseTmr.d \
Dio_Driver.d \
mirf.d \
Port.d \
spi.d \
UART.d

C_DEPS_AS_ARGS +=  \
ADC.d \
AVRTemplateApp.d \
BaseTmr.d \
Dio_Driver.d \
mirf.d \
Port.d \
spi.d \
UART.d

OUTPUT_FILE_PATH +=Template_Project_nRF24l01p_on_Arduino_Clone_w_ATMega168PA.elf

OUTPUT_FILE_PATH_AS_ARGS +=Template_Project_nRF24l01p_on_Arduino_Clone_w_ATMega168PA.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

# AVR32/GNU C Compiler

















./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1051\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -D"F_CPU=16000000"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall -mmcu=atmega168pa -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 4.8.1
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1051\avr8-gnu-toolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="Template_Project_nRF24l01p_on_Arduino_Clone_w_ATMega168PA.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -mmcu=atmega168pa  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1051\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "Template_Project_nRF24l01p_on_Arduino_Clone_w_ATMega168PA.elf" "Template_Project_nRF24l01p_on_Arduino_Clone_w_ATMega168PA.hex"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1051\avr8-gnu-toolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "Template_Project_nRF24l01p_on_Arduino_Clone_w_ATMega168PA.elf" "Template_Project_nRF24l01p_on_Arduino_Clone_w_ATMega168PA.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1051\avr8-gnu-toolchain\bin\avr-objdump.exe" -h -S "Template_Project_nRF24l01p_on_Arduino_Clone_w_ATMega168PA.elf" > "Template_Project_nRF24l01p_on_Arduino_Clone_w_ATMega168PA.lss"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1051\avr8-gnu-toolchain\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "Template_Project_nRF24l01p_on_Arduino_Clone_w_ATMega168PA.elf" "Template_Project_nRF24l01p_on_Arduino_Clone_w_ATMega168PA.srec"
	"C:\Program Files (x86)\Atmel\Atmel Toolchain\AVR8 GCC\Native\3.4.1051\avr8-gnu-toolchain\bin\avr-size.exe" "Template_Project_nRF24l01p_on_Arduino_Clone_w_ATMega168PA.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "Template_Project_nRF24l01p_on_Arduino_Clone_w_ATMega168PA.elf" "Template_Project_nRF24l01p_on_Arduino_Clone_w_ATMega168PA.a" "Template_Project_nRF24l01p_on_Arduino_Clone_w_ATMega168PA.hex" "Template_Project_nRF24l01p_on_Arduino_Clone_w_ATMega168PA.lss" "Template_Project_nRF24l01p_on_Arduino_Clone_w_ATMega168PA.eep" "Template_Project_nRF24l01p_on_Arduino_Clone_w_ATMega168PA.map" "Template_Project_nRF24l01p_on_Arduino_Clone_w_ATMega168PA.srec" "Template_Project_nRF24l01p_on_Arduino_Clone_w_ATMega168PA.usersignatures"
	