// The program here is a simple
// blink example available to
// most atmega-based boards. For
// more information, please refer
// to the datasheet of the ATmega328

// Set the buffer size of the serial
// monitor to be 16 bytes long
#define SERIAL_BUFFER_SIZE 16

#include <avr/io.h>
#include <avr/interrupt.h>

#include <core/serial.h>

#define ONE_SECOND ((F_CPU / 1024) - 1)
#define LED_BUILTIN (1 << PB5)

ISR(TIMER1_COMPA_vect)
{
  PORTB ^= LED_BUILTIN;
}

int main()
{
  char text[SERIAL_BUFFER_SIZE] = "Hello world!\n";
  DDRB = LED_BUILTIN;

  OCR1A = ONE_SECOND / 2;

  TCCR1B = (1 << CS10) | (1 << CS12) | (1 << WGM12);
  TIMSK1 = (1 << OCIE1A);

  init_serial();
  sei();

  for (int i = 0; i < SERIAL_BUFFER_SIZE; i++)
  {
    serial_putchar(text[i]);
  }

  while (1)
  {
    // Busy wait loop
  }
}