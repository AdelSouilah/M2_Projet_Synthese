#include "instance_gen.h"

void generate_tasks(Task *tasks, int n, int pi_min, int pi_max, int di_min, int di_max) {
    for (int i = 0; i < n; ++i) {
        tasks[i].i = i;
        tasks[i].pi = (rand() %(pi_max - pi_min + 1)) + pi_min;
        tasks[i].di = tasks[i].pi + (rand() %(di_max - di_min + 1)) + di_min;
    }
}

void print_task_to_file(Task *tasks, int n, char *filename) {
    FILE *file = fopen(filename, "a");
    fprintf(file, "di1,pi1;di2,pi2;...;din,pin\n");
    for (int i = 0; i < n - 1; i++) {
        fprintf(file, "%d,%d;",tasks[i].di, tasks[i].pi);
    }
    fprintf(file, "%d,%d",tasks[n - 1].di, tasks[n - 1].pi);
    fclose(file);
}

void save_results_to_file(char *filename, int taskID, double executionTime, int tardiness) {
    FILE *file = fopen(filename, "a");
    fprintf(file, "ID : %d, Time : %f, Tardiness : %d\n", taskID, executionTime, tardiness);
    fclose(file);
}
