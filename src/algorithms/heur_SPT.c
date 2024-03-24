#include "heur_SPT.h"
#include "instance_gen.h"

int compare_spt(const void *a, const void *b) {
    Task *taskA = (Task *) a;
    Task *taskB = (Task *) b;
    return taskA->pi - taskB->pi;
}

void spt_rule(Task *tasks, int n) {
    qsort(tasks, n, sizeof(Task), compare_spt);
}

void test_spt(Task *tasks, int n) {
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    spt_rule(tasks, n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    int tardiness = calculateWeightedTardiness(tasks, n);
    save_tard_and_time_to_file("../output/result.csv", cpu_time_used, tardiness);
}