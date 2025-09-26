// The program here is a simple
// blink example available to
// most atmega-based boards. For
// more information, please refer
// to the datasheet of the ATmega328

#include <avr/io.h>
#include <avr/interrupt.h>

#define ONE_SECOND ((F_CPU / 1024) - 1)
#define LED_BUILTIN (1 << PB5)

ISR(TIMER1_COMPA_vect)
{
  PORTB ^= LED_BUILTIN;
}

int main()
{
  DDRB = LED_BUILTIN;

  OCR1A = ONE_SECOND / 2;

  TCCR1B = (1 << CS10) | (1 << CS12) | (1 << WGM12);
  TIMSK1 = (1 << OCIE1A);

  sei();

  while (1)
  {
    // Busy wait loop
  }
}