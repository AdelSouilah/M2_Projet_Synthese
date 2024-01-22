#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  // Ajout pour initialiser rand

#define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
    int i;
    int di;
    int pi;
} Task;

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

/*int compare_edd(const void *a, const void *b) {
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
}*/

int calculateWeightedTardiness(Task *tasks, int n) {
    int sum_pi = 0;
    int tardiness = 0;
    for (int i = 0; i < n; ++i) {
        sum_pi += tasks[i].pi;
        tardiness += tasks[i].pi * max(0, sum_pi - tasks[i].di);
        printf("Retard : %d, pi : %d, i: %d\n", tasks[i].pi, sum_pi, i);
    }
    return tardiness;
}

/*int calculate_cost(Task *tasks, int n) {
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
}*/

// Recherche tabou
#define TABOO_SIZE 10  // Taille de la liste tabou

typedef struct {
    int task1;
    int task2;
} TabooMove;

TabooMove tabooList[TABOO_SIZE];
int tabooIndex = 0;

void addTabooMove(int task1, int task2) {
    printf("Ajout de la permutation %d %d dans la liste tabou\n", task1, task2);
    tabooList[tabooIndex].task1 = task1;
    tabooList[tabooIndex].task2 = task2;
    tabooIndex = (tabooIndex + 1) % TABOO_SIZE;
}

int isTaboo(int task1, int task2) {
    printf("Recherche de la permutation %d %d dans la liste tabou\n", task1, task2);
    for (int i = 0; i < TABOO_SIZE; i++) {
        if ((tabooList[i].task1 == task1 && tabooList[i].task2 == task2) ||
            (tabooList[i].task1 == task2 && tabooList[i].task2 == task1)) {
            return 1;
        }
    }
    return 0;
}

void swapTasks(Task *tasks, int i, int j) {
    printf("Permutation des taches %d et %d\n", i, j);
    Task temp = tasks[i];
    tasks[i] = tasks[j];
    tasks[j] = temp;
}

void generateNeighbor(Task *tasks, int n) {
    printf("Generation d'un voisin\n");
    int bestTardiness = calculateWeightedTardiness(tasks, n);
    Task temp[n];
    memcpy(temp, tasks, n * sizeof(Task));
    int improved = 0;

    for (int i = 0; i < n - 1 && !improved; i++) {
        for (int j = i + 1; j < n && !improved; j++) {
            if (!isTaboo(i, j)) {
                // Effectuer la permutation
                swapTasks(temp, i, j);

                // Calculer le retard après permutation
                int newTardiness = calculateWeightedTardiness(temp, n);
                if (newTardiness < bestTardiness) {
                    // Si le retard est amélioré, ajouter à la liste tabou et mettre à jour les tâches
                    addTabooMove(i, j);
                    memcpy(tasks, temp, n * sizeof(Task));
                    improved = 1;
                }

                // Remettre les tâches dans leur état initial pour la prochaine itération
                swapTasks(temp, i, j);
            }
        }
    }

    // Si aucune amélioration n'a été trouvée, effectuer une permutation aléatoire non tabou
    if (!improved) {
        int task1, task2;
        do {
            task1 = rand() % n;
            task2 = rand() % n;
        } while (task1 == task2 || isTaboo(task1, task2));

        swapTasks(tasks, task1, task2);
        addTabooMove(task1, task2);
    }
}


void tabooSearch(Task *tasks, int n) {
    printf("Initialisation de la liste tabou\n");
    Task bestSolution[n];
    memcpy(bestSolution, tasks, n * sizeof(Task));
    int bestTardiness = calculateWeightedTardiness(tasks, n);

    printf("Debut de la recherche tabou\n");
    printf("Retard initial: %d\n", bestTardiness);

    for (int iteration = 0; iteration < 10; iteration++) {
        printf("Iteration: %d\n", iteration);

        generateNeighbor(tasks, n);
        int currentTardiness = calculateWeightedTardiness(tasks, n);
        printf("Retard pondere apres permutation: %d\n", currentTardiness);

        if (currentTardiness < bestTardiness) {
            memcpy(bestSolution, tasks, n * sizeof(Task));
            bestTardiness = currentTardiness;
            printf("Nouvelle meilleure solution trouvee: %d\n", bestTardiness);
        } else {
            memcpy(tasks, bestSolution, n * sizeof(Task));
            printf("Retour a la meilleure solution precedente\n");
        }
    }

    printf("Fin de la recherche tabou\n");
    printf("Meilleure retard trouve: %d\n", bestTardiness);
}

int main() {
    srand(time(NULL));  // Initialisation de rand
    // Création d’un ensemble de tâches de test
    /*Task tasks1[] = {
            {1, 10001,  10001},
            {2, 100000, 10000},
            {3, 100001, 90000},
    };
    Task tasks2[] = {
            {1, 14,  2},
            {2, 98,  68},
            {3, 59, 28},
            {4, 80,  1},
    };*/
    Task tasks3[] = {
            {1, 37,  6},
            {2, 24,  6},
            {3, 100, 87},
            {4, 87,  22},
    };

    Task tasksExtended[] = {
            {1,  37,  5},
            {2,  24,  23},
            {3,  65,  14},
            {4,  80,  75},
            {5,  6,   2},
            {6,  54,  46},
            {7,  87,  22},
            {8,  100, 43},
            {9,  20,  8},
            {10, 65,  32}
    };


    /*int n1 = sizeof(tasks1) / sizeof(tasks1[0]);
    int n2 = sizeof(tasks2) / sizeof(tasks2[0]);*/
    int n3 = sizeof(tasks3) / sizeof(tasks3[0]);

    int nExtended = sizeof(tasksExtended) / sizeof(tasksExtended[0]);

    /*printf("Taches d'origine:\n");
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
    printf("Retard pondéré : %d", calculateWeightedTardiness(tasks4, n3));*/

    /*// Test de la règle EDD
    printf("retard pondere initial: %d\n", calculateWeightedTardiness(tasksExtended, nExtended));

    printf("EDD Rule:\n");
    edd_rule(tasksExtended, nExtended);
    printf("retard pondere EDD: %d\n", calculateWeightedTardiness(tasksExtended, nExtended));*/

    // Affichage de la liste dans l'ordre
    display_tasks(tasksExtended, nExtended);
    display_schedule(tasksExtended, nExtended);

    tabooSearch(tasksExtended, nExtended);
    // Affichage de la liste dans l'ordre
    display_tasks(tasksExtended, nExtended);
    display_schedule(tasksExtended, nExtended);
    return 0;
}
