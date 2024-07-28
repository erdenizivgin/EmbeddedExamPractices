#include "timer.h"
#include "avr/io.h"
#include "avr/interrupt.h"

#define TIMER0_CYC_FOR_1MS 249
#define TIMER1_ICR_VAL 31249
#define TIMER1_DUTYCYCLE 0.7

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

void timer1_PWMinit(void)
{
    // Set non inverting pwm mode
    TCCR1A |= (1 << COM1A1) | (1 << WGM11);
    // Fast PWM with TOP ICR1A
    TCCR1B |= (1 << WGM13) | (1 << WGM12);
    // Set prescaler to 1024
    TCCR1B |= (1 << CS12) | (1 << CS10);
    // For 2 sec period the top value set to 31249
    ICR1 = TIMER1_ICR_VAL;
    // 70% duty cycle OCR1A value 21874
    OCR1A = (uint16_t)(TIMER1_ICR_VAL * TIMER1_DUTYCYCLE);

    // set OC1A pin (PB1) as output
    DDRB |= (1 << PB1);
}
