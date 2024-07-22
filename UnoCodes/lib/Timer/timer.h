#ifndef TIMER_H_
#define TIMER_H_

/*PROTOTYPES *****************************************************************/

/**type of function pointer used as timer callback
 */
typedef void (*pTimerCallback)(void);

/**
 * Sets a function to be called when the timer fires. If NULL is
 * passed, no callback is executed when the timer fires.
 *
 * @param cb  valid pointer to callback function
 */
void timer0_setCallback(pTimerCallback cb);

/**
 * Starts hardware timer 0 of MCU with a period
 * of 1 ms.
 */
void timer0_start(void);

/**
 * Stops timer 0.
 */
void timer0_stop(void);

#endif /* TIMER_H_ */
