#include "avr/io.h"
#include "avr/interrupt.h"
#include "led.h"
#include "scheduler.h"

task_descriptor_t ledBlinkTask = {.task = (task_t)led_builtinToggle, .expire = 300, .period = 300};

int main(void)
{
  led_builtinInit();
  scheduler_init();
  scheduler_add(&ledBlinkTask);
  sei();
  while (1)
  {
    scheduler_run();
  }

  return 0;
}
