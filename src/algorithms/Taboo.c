#pragma once

#include "../../HelperFunctions.c"

#define NUM_NEIGHBORS 20  // Nombre de voisins à générer par itération
#define NUM_ITERATIONS 5  // Nombre total d'itérations

#define TABOO_SIZE 10  // Taille de la liste tabou

typedef struct {
    int task1;
    int task2;
} TabooMove;

TabooMove tabooList[TABOO_SIZE];
int tabooIndex = 0;

// Taboo search
void addTabooMove(int task1, int task2) {
    printf("Ajout de la permutation %d %d dans la liste tabou\n", task1, task2);
    tabooList[tabooIndex].task1 = task1;
    tabooList[tabooIndex].task2 = task2;
    tabooIndex = (tabooIndex + 1) % TABOO_SIZE;
}

int isTaboo(int task1, int task2) {
//    printf("Recherche de la permutation %d %d dans la liste tabou\n", task1, task2);
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

void tabooSearch(Task *tasks, int n) {
    Task bestSolution[n], currentSolution[n];
    memcpy(bestSolution, tasks, n * sizeof(Task));
    int bestTardiness = calculateWeightedTardiness(tasks, n);

    for (int iteration = 0; iteration < NUM_ITERATIONS; iteration++) {
        printf("Iteration %d\n", iteration);

        printf("Meilleure solution actuelle : ");
        display_schedule_abridged(currentSolution, n);
        printf("Meilleure solution : ");
        display_schedule_abridged(bestSolution, n);

        memcpy(currentSolution, bestSolution, n * sizeof(Task));
        int currentBestTardiness = bestTardiness;

        for (int neighbor = 0; neighbor < NUM_NEIGHBORS; neighbor++) {
            Task temp[n];
            memcpy(temp, currentSolution, n * sizeof(Task));

            int task1, task2;
            do {
                task1 = rand() % n;
                task2 = rand() % n;
            } while (task1 == task2 || isTaboo(task1, task2));

            swapTasks(temp, task1, task2);
            int tempTardiness = calculateWeightedTardiness(temp, n);

            if (tempTardiness < currentBestTardiness) {
                memcpy(currentSolution, temp, n * sizeof(Task));
                currentBestTardiness = tempTardiness;
                addTabooMove(task1, task2);
            }
        }

        if (currentBestTardiness < bestTardiness) {
            memcpy(bestSolution, currentSolution, n * sizeof(Task));
            bestTardiness = currentBestTardiness;
        }
    }

    memcpy(tasks, bestSolution, n * sizeof(Task));  // Restaurer la meilleure solution trouvée
    printf("Meilleure retard trouve: %d\n", bestTardiness);
}