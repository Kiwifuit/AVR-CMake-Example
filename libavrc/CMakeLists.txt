cmake_minimum_required(VERSION 3.20)

project(avrc VERSION 1.0.0)

set(
  SOURCES
  src/serial.c
)

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC include/)