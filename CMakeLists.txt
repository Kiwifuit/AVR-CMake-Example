cmake_minimum_required(VERSION 3.20)
project(mato LANGUAGES C VERSION 1.0.0)

option(DEVICE "Path to TTY device" "/dev/ttyACM0")

set(SOURCES src/main.c)

set(MCU "atmega328p")
set(F_CPU "16000000UL")

find_program(AVR_GCC avr-gcc)
find_program(AVR_OBJCOPY avr-objcopy)
find_program(AVR_SIZE avr-size)

set(CMAKE_C_FLAGS "-mmcu=${MCU} -DF_CPU=${F_CPU} -Os -Wall")
set(CMAKE_CXX_FLAGS "-mmcu=${MCU} -DF_CPU=${F_CPU} -Os -Wall")
set(CMAKE_EXE_LINKER_FLAGS "-mmcu=${MCU} -Os")

if(NOT AVR_GCC)
    message(FATAL_ERROR "AVR-GCC not found. Please install the AVR toolchain.")
endif()

if(NOT AVR_OBJCOPY)
    message(FATAL_ERROR "AVR-OBJCOPY not found. Please install the AVR toolchain.")
endif()

if(NOT AVR_SIZE)
    message(FATAL_ERROR "AVR-SIZE not found. Please install the AVR toolchain.")
endif()

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER /usr/bin/avr-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/avr-g++)

add_executable(${PROJECT_NAME}.elf ${SOURCES})

add_custom_command(
  TARGET ${PROJECT_NAME}.elf POST_BUILD
  COMMAND avr-objcopy -O ihex -R .eeprom $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.hex
  COMMENT "Generating hex file"
)

add_custom_command(
  TARGET ${PROJECT_NAME}.elf POST_BUILD
  COMMAND avr-objcopy -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.eep
  COMMENT "Generating eeprom file"
)

add_custom_target(flash
  COMMAND avrdude -p ${MCU} -c arduino -P ${DEVICE} -U flash:w:${PROJECT_NAME}.hex:i
  DEPENDS ${PROJECT_NAME}.elf
  COMMENT "Flashing ${PROJECT_NAME}.hex"
)

add_custom_target(monitor
  COMMAND screen ${DEVICE} 9600
  DEPENDS flash
  COMMENT "Monitor ${PROJECT_NAME}"
)