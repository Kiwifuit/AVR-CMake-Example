cmake_minimum_required(VERSION 3.20)

project(avrc VERSION 1.0.0)

set(
  SOURCES
  src/serial.c
)

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC include/)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)

set(CPACK_PACKAGE_NAME lib${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${PACKAGE_VERSION})
set(CPACK_PACKAGE_VENDOR "Kiwifuit<mahkiwi123@gmail.com>")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Kiwifuit<mahkiwi123@gmail.com>")
set(CPACK_PACKAGE_DESCRIPTION "Simple HAL to interface with AVR systems")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "avr-libc (>=1:2.0.0+Atmel3.7.0-1)")

include(CPack)