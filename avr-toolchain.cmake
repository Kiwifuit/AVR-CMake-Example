set(MCU "atmega328p")
set(F_CPU "16000000UL")

find_program(AVR_GCC avr-gcc)
find_program(AVR_OBJCOPY avr-objcopy)
find_program(AVR_SIZE avr-size)

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

set(CMAKE_C_FLAGS "-mmcu=${MCU} -DF_CPU=${F_CPU} -Os -Wall")
set(CMAKE_CXX_FLAGS "-mmcu=${MCU} -DF_CPU=${F_CPU} -Os -Wall")
set(CMAKE_EXE_LINKER_FLAGS "-mmcu=${MCU} -Os")