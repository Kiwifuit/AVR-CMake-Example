#ifndef SERIAL_BAUD_RATE
#define SERIAL_BAUD_RATE 9600
#endif

#ifndef SERIAL_BUFFER_SIZE
#define SERIAL_BUFFER_SIZE 64
#endif

#define BAUD_VALUE ((F_CPU / (16UL * SERIAL_BAUD_RATE)) - 1)

#include <stdint.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include <core/serial.h>

static volatile uint8_t SERIAL_BUFFER[SERIAL_BUFFER_SIZE];
static volatile uint8_t write_head = 0;
static volatile uint8_t read_head = 0;

ISR(USART_UDRE_vect)
{
  if (write_head != read_head)
  {
    // Push character on read_head to the
    // serial buffer and increment the
    // read head
    UDR0 = SERIAL_BUFFER[read_head];
    read_head = (read_head + 1) % SERIAL_BUFFER_SIZE;
  }
  else
  {
    // Disable the Data Register Empty
    // Interrupt
    UCSR0B &= ~(1 << UDRIE0);
  }
}

void serial_putchar(uint8_t data)
{
  if (UCSR0B == 0)
  {
    return;
  }
  else if (data == '\n')
  {
    serial_putchar('\r');
  }

  while ((write_head + 1) % SERIAL_BUFFER_SIZE == read_head)
  {
    // Wait for the buffer to be
    // empty
  }

  SERIAL_BUFFER[write_head % SERIAL_BUFFER_SIZE] = data;
  write_head = (write_head + 1) % SERIAL_BUFFER_SIZE;
  UCSR0B |= (1 << UDRIE0);
}

void init_serial()
{
  if (UCSR0B != 0)
  {
    return;
  }

  // Enable TX and RX
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);

  // Enable 8-bit character size
  // This is the default, but
  // it is done anyway to be more
  // explicit
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

  // Set the baud value, which
  // is calculated by the baud rate
  UBRR0 = BAUD_VALUE;
}
