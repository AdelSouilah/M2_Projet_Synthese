#ifndef INSTANCE_GEN_H
#define INSTANCE_GEN_H

#include "aide.h"

void generate_tasks(Task *tasks, int n, int pi_min, int pi_max, int di_min, int di_max);

void print_task_to_file(Task *tasks, int n, char *filename);

void save_results_to_file(char *filename, int taskID, double executionTime, int tardiness);

int compare_edd(const void *a, const void *b);

#endif //INSTANCE_GEN_H
