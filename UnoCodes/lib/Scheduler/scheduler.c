/*INCLUDES *******************************************************************/
#include <stdlib.h>

#include "timer.h"
#include "scheduler.h"
#include "util/atomic.h"

/* PRIVATE VARIABLES *********************************************************/

/**
 * We make sure that the list is accessed only within atomic sections
 * protected by a memory barrier --> no volatile necessary
 */
static task_descriptor_t *taskList = NULL;

/*FUNCTION DEFINITION *************************************************/

void scheduler_update(void)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        task_descriptor_t *current = taskList;
        while (current != NULL)
        {
            if (current->expire > 0)
            {
                // decrement the expiration time by 1ms
                current->expire--;
            }
            if (current->expire == 0)
            {
                // make current task ready for execution
                current->execute = 1;
                if (current->period > 0)
                {
                    // if task is periodic set its expiration time by the period
                    current->expire = current->period;
                }
            }
            current = current->next;
        }
    }
}

void scheduler_init()
{
    // Initialize Timer0 to call scheduler_update() every 1 ms
    timer0_start();
    timer0_setCallback(scheduler_update);
}

void scheduler_run()
{

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        task_descriptor_t *current = taskList;
        while (current != NULL)
        {
            if (current->execute)
            {
                current->task(current->param);
                current->execute = 0;
                if (current->period == 0)
                {
                    scheduler_remove(current);
                }
            }
            current = current->next;
        }
    }
}

bool scheduler_add(task_descriptor_t *toAdd)
{
    if (toAdd == NULL || toAdd->task == NULL)
    {
        return false;
    }

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        // check if task is already in the list
        task_descriptor_t *current = taskList;
        while (current != NULL)
        {
            if (current == toAdd)
            {
                return false;
            }
            current = current->next;
        }

        // add new task to beginning of the list
        toAdd->next = taskList;
        taskList = toAdd;
    }
    return true;
}

void scheduler_remove(const task_descriptor_t *toRemove)
{
    if (toRemove == NULL)
    {
        return;
    }

    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        // remove task from list
        task_descriptor_t *current = taskList;
        task_descriptor_t *prev = NULL;

        while (current != NULL)
        {
            if (current == toRemove)
            {
                if (prev == NULL)
                {
                    taskList = current->next;
                }
                else
                {
                    prev->next = current->next;
                }
                return;
            }
            prev = current;
            current = current->next;
        }
    }
}
