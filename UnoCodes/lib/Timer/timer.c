#include "timer.h"
#include "avr/io.h"
#include "avr/interrupt.h"

#define TIMER0_CYC_FOR_1MS 249

static volatile pTimerCallback timer0Callback;
static volatile pTimerCallback timer1Callback;

void timer0_start(void)
{
    TCCR0A |= (1 << WGM01);              // Set WGM01 bit 1 to set Timer0 operates as CTC mode
    TCCR0A &= ~(0 << WGM00);             // Set WGM00 bit 0 to set Timer0 operates as CTC mode
    TCCR0B |= (1 << CS01) | (1 << CS00); // Set Prescaler 64
    TIMSK0 |= (1 << OCIE0A);             // Enable the compare match interrupt
    TIFR0 |= (1 << OCF0A);               // Clear the interrupt flag for output match A
    OCR0A = TIMER0_CYC_FOR_1MS;
}

void timer0_stop(void)
{
    TIMSK0 &= (1 << OCIE0A); // Disable Timer 0 Compare Match A interrupt
}

void timer0_setCallback(pTimerCallback callback)
{
    timer0Callback = callback;
}

ISR(TIMER0_COMPA_vect)
{
    timer0Callback();
}
