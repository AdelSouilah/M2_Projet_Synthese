#include "heur_EDD.h"
#include "instance_gen.h"

int compare_edd(const void *a, const void *b) {
    Task *taskA = (Task *) a;
    Task *taskB = (Task *) b;
    return taskA->di - taskB->di;
}

void edd_rule(Task *tasks, int n) {
    qsort(tasks, n, sizeof(Task), compare_edd);
}

void test_edd(Task *tasks, int n) {
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    edd_rule(tasks, n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    int tardiness = calculateWeightedTardiness(tasks, n);
    save_tard_and_time_to_file("../output/result.csv", cpu_time_used, tardiness);
}