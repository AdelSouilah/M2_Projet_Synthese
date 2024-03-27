#include "rech_taboo.h"
#include "instance_gen.h"

#define NUM_NEIGHBORS 20  // Nombre de voisins à générer par itération
#define NUM_ITERATIONS 5  // Nombre total d'itérations

#define TABOO_SIZE 10  // Taille de la liste tabou

TabooMove tabooList[TABOO_SIZE];
int tabooIndex = 0;

// Taboo search
void addTabooMove(int task1, int task2) {
    tabooList[tabooIndex].task1 = task1;
    tabooList[tabooIndex].task2 = task2;
    tabooIndex = (tabooIndex + 1) % TABOO_SIZE;
}

int isTaboo(int task1, int task2) {
    for (int i = 0; i < TABOO_SIZE; i++) {
        if ((tabooList[i].task1 == task1 && tabooList[i].task2 == task2) ||
            (tabooList[i].task1 == task2 && tabooList[i].task2 == task1)) {
            return 1;
        }
    }
    return 0;
}

void swapTasks(Task *tasks, int i, int j) {
    Task temp = tasks[i];
    tasks[i] = tasks[j];
    tasks[j] = temp;
}

void tabooSearch(Task *tasks, int n) {
    Task bestSolution[n], currentSolution[n];
    memcpy(bestSolution, tasks, n * sizeof(Task));
    int bestTardiness = calculateWeightedTardiness(tasks, n);

    for (int iteration = 0; iteration < NUM_ITERATIONS; iteration++) {
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

/*    // Afficher la séquence du meilleur individu
    printf("Meilleure séquence tabou: ");
    for (int i = 0; i < n; i++) {
        printf("%d ",bestSolution[i].i); // Assurez-vous que cela correspond à votre structure de données
    }*/

    memcpy(tasks, bestSolution, n * sizeof(Task));  // Restaurer la meilleure solution trouvée
}

void test_taboo(Task *tasks, int n) {
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    tabooSearch(tasks, n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    int tardiness = calculateWeightedTardiness(tasks, n);
//    printf("Retard taboo: %d\n", tardiness);
    save_tard_and_time_to_file("../output/result.csv", cpu_time_used, tardiness);
}