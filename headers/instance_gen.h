#ifndef M2_PROJET_SYNTHESE_INSTANCE_GEN_H
#define M2_PROJET_SYNTHESE_INSTANCE_GEN_H

#include "aide.h"

void generate_tasks(Task *tasks, int n, int pi_min, int pi_max, int di_min, int di_max);

void print_task_to_file(Task *tasks, int n, char *filename);

void save_id_to_file(char *filename, int taskID);

void save_tard_and_time_to_file(char *filename, double executionTime, int tardiness);

void save_inst_info_to_file(char *filename, double avgDuration, double avgDeadline, double varianceDuration,
                            double varianceDeadline, double stdDevDuration, double stdDevDeadline);
#endif //M2_PROJET_SYNTHESE_INSTANCE_GEN_H
