#include "instance_gen.h"

void generate_tasks(Task *tasks, int n, int pi_min, int pi_max, int di_min, int di_max) {
    for (int i = 0; i < n; ++i) {
        tasks[i].i = i;
        tasks[i].pi = (rand() % (pi_max - pi_min + 1)) + pi_min;
        tasks[i].di = tasks[i].pi + (rand() % (di_max - di_min + 1)) + di_min;
    }
}

void print_task_to_file(Task *tasks, int n, char *filename) {
    FILE *file = fopen(filename, "a");
    for (int i = 0; i < n - 1; i++) {
        fprintf(file, "%d,%d;", tasks[i].di, tasks[i].pi);
    }
    fprintf(file, "%d,%d\n", tasks[n - 1].di, tasks[n - 1].pi);
    fclose(file);
}

void save_id_to_file(char *filename, int taskID) {
    FILE *file = fopen(filename, "a");
    fprintf(file, "%d,", taskID);
    fclose(file);
}

void save_tard_and_time_to_file(char *filename, double executionTime, int tardiness) {
    FILE *file = fopen(filename, "a");
    fprintf(file, "%f,%d,", executionTime, tardiness);
    fclose(file);
}

void save_inst_info_to_file(char *filename, double avgDuration, double avgDeadline, double varianceDuration,
                            double varianceDeadline, double stdDevDuration, double stdDevDeadline) {
    FILE *file = fopen(filename, "a");
    fprintf(file, "%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",
            avgDuration, avgDeadline,
            varianceDuration, varianceDeadline,
            stdDevDuration, stdDevDeadline);
    fclose(file);
}