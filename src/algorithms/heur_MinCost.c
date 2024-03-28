#include "heur_MinCost.h"
#include "instance_gen.h"

Task* minimum_cost_rule(Task *tasks, int n) {
    Task* tasks_copy = malloc(sizeof(Task) * n);
    Task* tasks_result = malloc(sizeof(Task) * n);
    tasks_result = memcpy(tasks_result, tasks, sizeof(Task) * n);
    tasks_copy = memcpy(tasks_copy, tasks, sizeof(Task) * n);

    for (int i = n; i > 0; i--) {
        int pos_task_to_place = smallest_tardiness(tasks_copy, i);
        tasks_result[i - 1] = tasks_copy[pos_task_to_place];
        delete_task(tasks_copy, i, pos_task_to_place);
    }

    return tasks_result;
}

void test_minCost(Task *tasks, int n) {
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    minimum_cost_rule(tasks, n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    int tardiness = calculateWeightedTardiness(tasks, n);
//    printf("Retard mincost: %d\n", tardiness);
    save_tard_and_time_to_file("../output/result.csv", cpu_time_used, tardiness);
}