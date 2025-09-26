cmake_minimum_required(VERSION 3.20)
project(mato LANGUAGES C VERSION 1.0.0)

option(DEVICE "Path to TTY device" "/dev/ttyACM0")

add_subdirectory(libavrc/)
add_subdirectory(program/)