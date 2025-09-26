#pragma once

#include <stdint.h>

/*
  Initializes the serial monitor at
  `SERIAL_BAUD_RATE`, which can be
  defined or left default at `9600`
*/
void init_serial();

/*
  Puts a character `data` inside the
  serial monitor

  Under normal circumstances, this
  function does not block except for
  when the internal buffer is full.
  By default, the buffer size is set
  to 64 bytes, but can be changed
  by defining `SERIAL_BUFFER_SIZE`
*/
void serial_putchar(uint8_t data);
