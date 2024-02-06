#include "aide.h"

void display_tasks(Task *tasks, int n) {
    printf("Affichage des taches:\n");
    printf("ID\tDeadline\tDuration/Weight\n");
    int current_pi = 0;
    for (int i = 0; i < n; i++) {
        current_pi += tasks[i].pi;
        printf("%d\t%d\t\t%d\n", tasks[i].i, tasks[i].di, tasks[i].pi);
    }
    printf("\n");
}

void display_schedule_abridged(Task *tasks, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d | ", tasks[i].i);
    }
    printf("\n");
}

void display_schedule(Task *tasks, int n) {
    printf("Affichage de l'ordonnancement:\n");
    int current_pi = 0;
    for (int i = 0; i < n - 1; i++) {
        current_pi += tasks[i].pi;
        printf("C%d : %d | ", tasks[i].i, current_pi);
    }
    current_pi += tasks[n - 1].pi;
    printf("C%d : %d ", tasks[n - 1].i, current_pi);
    printf("\n\n");
}

int calculateWeightedTardiness(Task *tasks, int n) {
    int sum_pi = 0;
    int tardiness = 0;
    for (int i = 0; i < n; ++i) {
        sum_pi += tasks[i].pi;
        tardiness += tasks[i].pi * max(0, sum_pi - tasks[i].di);
//        printf("Retard : %d, pi : %d, i: %d\n", tasks[i].pi, sum_pi, i);
    }
    return tardiness;
}

int calculate_cost(Task *tasks, int n) {
    int sum_pi = 0;
    for (int i = 0; i < n; ++i) {
        sum_pi += tasks[i].pi;
    }
    return sum_pi;
}

int calculate_tardiness(Task *tasks, int n) {
    int sum_pi = 0;
    int tardiness = 0;
    for (int i = 0; i < n; ++i) {
        sum_pi += tasks[i].pi;
        tardiness += tasks[i].pi * max(0, sum_pi - tasks[i].di);
    }
    return tardiness;
}

int smallest_tardiness(Task *tasks, int n) {
    int sum_pi = calculate_cost(tasks, n);
    int smallest_task_tardiness = 999999999;
    int smallest_task_position = 0;
    for (int i = 0; i < n; i++){
        if (tasks[i].di >= sum_pi) {
            return i;
        }
        int tardiness = tasks[i].pi * (sum_pi - tasks[i].di);

        if (tardiness < smallest_task_tardiness) {
            smallest_task_tardiness = tardiness;
            smallest_task_position = i;
        }
    }
    return smallest_task_position;
}

void delete_task(Task *tasks, int n, int pos) {
    Task tmp = tasks[pos];
    for (int j = pos; j < n - 1; ++j) {
        tasks[j] = tasks[j + 1];
    }
    tasks[n - 1] = tmp;
}