cmake_minimum_required(VERSION 3.20)

project(sketch VERSION 1.0.0)

set(SOURCES main.c)

add_executable(${PROJECT_NAME}.elf ${SOURCES})
target_link_libraries(${PROJECT_NAME}.elf PUBLIC avrc)

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