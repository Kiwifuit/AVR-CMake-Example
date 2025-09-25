#include <avr/io.h>
#include <avr/interrupt.h>

#define ONE_SECOND ((F_CPU / 1024) - 1)

ISR(TIMER1_COMPA_vect)
{
  PORTB ^= (1 << PB5);
}

int main()
{
  DDRB = (1 << PB5);
  OCR1A = ONE_SECOND / 2;
  TCCR1B = (1 << CS10) | (1 << CS12) | (1 << WGM12);
  TIMSK1 = (1 << OCIE1A);
  sei();

  while (1)
  {
    // Busy wait loop
  }
}