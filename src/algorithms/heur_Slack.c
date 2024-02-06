#include "heur_Slack.h"
#include "instance_gen.h"

int compare_slack(const void *a, const void *b) {
    Task *taskA = (Task *) a;
    Task *taskB = (Task *) b;
    return (taskA->di - taskA->pi) - (taskB->di - taskB->pi);
}

void minimum_slack_rule(Task *tasks, int n) {
    qsort(tasks, n, sizeof(Task), compare_slack);
}

void test_slack(Task *tasks, int i, int n) {
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    minimum_slack_rule(tasks, n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    int tardiness = calculateWeightedTardiness(tasks, n);
    save_tard_and_time_to_file("../output/result.csv", cpu_time_used, tardiness);
}