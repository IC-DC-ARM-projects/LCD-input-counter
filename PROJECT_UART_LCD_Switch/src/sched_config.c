#include "STD_TYPES.h"
#include "sched_interface.h"
#include "sched_config.h"

/* tasks objects defined in each corresponding module */
extern SCHED_task_t const task_switch,
                          task_lcd,
                          task_app;

/* each object is defined by:
 * task_t reference,
 * initial delay (ms)  */
const SCHED_systask_info_t tasks_config[SCHED_MAX_TASKS] = {
		// Runnable, 		firstDelay
		{&task_switch,  .delayMs = 0},
		{&task_lcd,      2},
		{&task_app,      4},
};

