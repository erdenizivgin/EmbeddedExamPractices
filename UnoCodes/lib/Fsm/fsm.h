#ifndef FSM_H_
#define FSM_H_

/* INCLUDES *****************************************************************/
#include <stdbool.h>
#include <stdint.h>

/* TYPES ********************************************************************/

typedef enum return_values fsm_return_status_t; //< typedef return value

typedef uint32_t system_time_t; // typedef for systemtime

typedef struct fsm_s fsm_t; //< typedef for alarm clock state machine

typedef struct event_s event_t; //< event type for alarm clock fsm

/*
 * a state is represented by a function pointer
 * called for each transition emanating in this
 * state
 */

typedef fsm_return_status_t (*state_t)(fsm_t *, const event_t *);

struct fsm_s
{
    state_t state; //< current state, pointer to event handler
};

struct event_s
{
    uint8_t signal; //< identifies the type of event
};

/** return values */
enum return_values
{
    RET_HANDLED,   //< event was handled
    RET_IGNORED,   //< event was ignored; not used in this implementation
    RET_TRANSITION //< event was handled and a state transition occurred
};

/** enum for event signals */
enum signal_e
{
    ENTRY,
    EXIT,
};

/* FUNCTION PROTOTYPES *******************************************************/

/**
 * Dispatches events to state machine, called in application
 */
void fsm_dispatch(fsm_t *fsm, const event_t *event);

/* sets and calls initial state of state machine */
void fsm_init(fsm_t *fsm, state_t init);

#endif /* FSM_H_ */
