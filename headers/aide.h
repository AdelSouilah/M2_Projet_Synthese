#ifndef M2_PROJET_SYNTHESE_AIDE_H
#define M2_PROJET_SYNTHESE_AIDE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "task.h"

#define max(a, b) ((a) > (b) ? (a) : (b))

void display_tasks(Task *tasks, int n);

void display_schedule_abridged(Task *tasks, int n);

void display_schedule(Task *tasks, int n);

int calculateWeightedTardiness(Task *tasks, int n);

int calculate_cost(Task *tasks, int n);

int calculate_tardiness(Task *tasks, int n);

int smallest_tardiness(Task *tasks, int n);

void delete_task(Task *tasks, int n, int pos);

#endif //M2_PROJET_SYNTHESE_AIDE_H
