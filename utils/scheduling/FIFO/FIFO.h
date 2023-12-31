#ifndef FIFO_H
#define FIFO_H
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "../../queues/fifo/queue.h"
#include "../../../include/types.h"
#include "../useful/useful.h"
#include "../../gantt/format.h"

ExecutedTask *get_fifo_output(process *process_array, int process_array_size, int *executed_tasks_size);

#endif