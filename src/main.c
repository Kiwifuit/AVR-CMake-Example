// The program here is a simple blink example
// available to most atmega-based boards.

#include <avr/io.h>
#include <avr/interrupt.h>

// Define how long one second is in terms
// of the amount of ticks
#define ONE_SECOND ((F_CPU / 1024) - 1)
#define LED_BUILTIN (1 << PB5)

ISR(TIMER1_COMPA_vect)
{
  // Toggle the LED_BUILTIN pin
  // whenever the TCINT1's output
  // compare register matches with
  // the counter
  PORTB ^= LED_BUILTIN;
}

int main()
{
  // Set the LED_BUILTIN pin to OUTPUT
  DDRB = LED_BUILTIN;

  // Set the "target" to toggle the state of
  // LED_BUILTIN to be half a second
  OCR1A = ONE_SECOND / 2;

  // Set the prescaler to 1024 (CS10 & CS12),
  // and set the waveform generation mode to
  // CTC.
  //
  // CTC mode caps out at the value stored at
  // OCR1A. When the value of TCINT1 equals to
  // the value inside OCR1A, an interrupt is
  // issued (enabled on the TIMSK1 OCIE1A bit)
  // and TCINT is reset to 0.
  //
  // For more information about the different
  // waveforms that TCINT1 can generate, refer
  // to table 15-5 on page 109 on the datashet
  // and table 15-6 on page 110 for the prescaler
  // selection
  //
  // Essentially, the prescaler divides the CPU's
  // clock frequency into a lower resolution
  // integer. Higher prescaler = lower "max"
  // value on TCINT1.
  //
  // With a clock of 16 MHz, and the prescaler
  // set to 1024, one second lasts 15,625 ticks,
  // meaning the 16-bit TCINT1 can hold about
  // 4.2 seconds before it overflows and resets
  // to zero. A lower prescaler value decreases
  // the time it takes for the counter to overflow
  TCCR1B = (1 << CS10) | (1 << CS12) | (1 << WGM12);
  TIMSK1 = (1 << OCIE1A);

  // Enable interrupts
  sei();

  // `main` should never exit, else the code does not
  // run
  while (1)
  {
    // Busy wait loop
  }
}