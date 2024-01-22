#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
    int i;
    int di;
    int pi;
} Task;

void display_tasks(Task *tasks, int n) {
    printf("ID\tDeadline\tDuration/Weight\n");
    int current_pi = 0;
    for (int i = 0; i < n; i++) {
        current_pi += tasks[i].pi;
        printf("%d\t%d\t\t%d\n", tasks[i].i, tasks[i].di, tasks[i].pi);
    }
    printf("\n");
}

void display_schedule(Task *tasks, int n) {
    int current_pi = 0;
    for (int i = 0; i < n - 1; i++) {
        current_pi += tasks[i].pi;
        printf("C%d : %d | ", tasks[i].i, current_pi);
    }
    current_pi += tasks[n - 1].pi;
    printf("C%d : %d ", tasks[n - 1].i, current_pi);
    printf("\n\n");
}

int compare_edd(const void *a, const void *b) {
    Task *taskA = (Task *) a;
    Task *taskB = (Task *) b;
    return taskA->di - taskB->di;
}

void edd_rule(Task *tasks, int n) {
    qsort(tasks, n, sizeof(Task), compare_edd);
}

int compare_lpt(const void *a, const void *b) {
    Task *taskA = (Task *) a;
    Task *taskB = (Task *) b;
    return taskB->pi - taskA->pi;
}

void lpt_rule(Task *tasks, int n) {
    qsort(tasks, n, sizeof(Task), compare_lpt);
}

int compare_spt(const void *a, const void *b) {
    Task *taskA = (Task *) a;
    Task *taskB = (Task *) b;
    return taskA->pi - taskB->pi;
}

void spt_rule(Task *tasks, int n) {
    qsort(tasks, n, sizeof(Task), compare_spt);
}

int compare_slack(const void *a, const void *b) {
    Task *taskA = (Task *) a;
    Task *taskB = (Task *) b;
    return (taskA->di - taskA->pi) - (taskB->di - taskB->pi);
}

void minimum_slack_rule(Task *tasks, int n) {
    qsort(tasks, n, sizeof(Task), compare_slack);
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


int calculate_cost(Task *tasks, int n) {
    int sum_pi = 0;
    for (int i = 0; i < n; ++i) {
        sum_pi += tasks[i].pi;
    }
    return sum_pi;
}

int smallest_tardiness(Task *tasks, int n) {
    int sum_pi = calculate_cost(tasks, n);
    int smallest_task_tardiness = 99999999;
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

Task* minimum_cost_rule(Task *tasks, int n) {
    // Copie des tâches pour ne pas modifier l'ordre initial
    Task* tasks_copy = malloc(sizeof(Task));
    Task* tasks_result = malloc(sizeof(Task));
    tasks_result = memcpy(tasks_result, tasks, sizeof(Task) * n);
    tasks_copy = memcpy(tasks_copy, tasks, sizeof(Task) * n);

    for (int i = n; i > 0; i--) {
        int pos_task_to_place = smallest_tardiness(tasks_copy, i);
        tasks_result[i - 1] = tasks_copy[pos_task_to_place];
        delete_task(tasks_copy, i, pos_task_to_place);
    }

    return tasks_result;
}

int main() {
    // Création d’un ensemble de tâches de test
    Task tasks1[] = {
            {1, 10001,  10001},
            {2, 100000, 10000},
            {3, 100001, 90000},
    };
    Task tasks2[] = {
            {1, 14,  2},
            {2, 98,  68},
            {3, 59, 28},
            {4, 80,  1},
    };
    Task tasks3[] = {
            {1, 37,  6},
            {2, 24,  6},
            {3, 100, 87},
            {4, 87,  22},
    };
    int n1 = sizeof(tasks1) / sizeof(tasks1[0]);
    int n2 = sizeof(tasks2) / sizeof(tasks2[0]);
    int n3 = sizeof(tasks3) / sizeof(tasks3[0]);

    printf("Taches d'origine:\n");
    display_tasks(tasks1, n1);

    // Test de la règle EDD
    printf("EDD Rule:\n");
    edd_rule(tasks1, n1);

    // Affichage de la liste dans l'ordre
    display_tasks(tasks1, n1);
    display_schedule(tasks1, n1);

    // Test de la règle LPT
    printf("LPT Rule:\n");
    lpt_rule(tasks1, n1);

    // Affichage de la liste dans l'ordre
    display_tasks(tasks1, n1);
    display_schedule(tasks1, n1);

    // Test de la règle SPT
    printf("SPT Rule:\n");
    spt_rule(tasks1, n1);

    // Affichage de la liste dans l'ordre
    display_tasks(tasks1, n1);
    display_schedule(tasks1, n1);

    // Test de la règle Minimum Slack
    printf("Minimum Slack Rule:\n");
    minimum_slack_rule(tasks2, n2);

    // Affichage de la liste dans l'ordre
    display_tasks(tasks2, n2);
    display_schedule(tasks2, n2);

    // Test de la règle Minimum Cost
    printf("Minimum Cost Rule:\n");
    Task* tasks4 = minimum_cost_rule(tasks3, n3);

    // Affichage de la liste dans l'ordre
    display_tasks(tasks4, n3);
    display_schedule(tasks4, n3);
    printf("Retard pondéré : %d", calculate_tardiness(tasks4, n3));

    // TODO - Ajouter la recherche locale de la recherche Tabou
    // 
    return 0;
}