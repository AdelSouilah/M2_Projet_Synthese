#include "branch_and_bound.h"
#include "aide.h"

#include <stdio.h>

#define MAX_TASKS 100

typedef struct Node {
    int sequence[MAX_TASKS]; // IDs des tâches dans l'ordre de planification
    int nbTasks; // Nombre de tâches planifiées dans ce nœud
    int bound; // Borne inférieure de la solution partielle
    int totalTardiness; // Tardiveté totale de la solution partielle
} Node;

// Prototypes des fonctions
void branch_and_bound(Task tasks[], int n);

int calculateTardiness(int sequence[], Task tasks[], int nbTasks) {
    int sum_pi = 0;
    int tardiness = 0;

    for (int i = 0; i < nbTasks; ++i) {
        int taskId = sequence[i]; // Get the task ID from the sequence
        // Find the corresponding task by ID
        for (int j = 0; j < nbTasks; ++j) {
            if (tasks[j].i == taskId) {
                sum_pi += tasks[j].pi;
                int task_tardiness = max(0, sum_pi - tasks[j].di);
                tardiness += tasks[j].pi * task_tardiness;
                break; // Break since we found the task
            }
        }
    }
    return tardiness;
}

int calculateWeightedTardinessBranch(Task tasks[], int sequence[], int n) {
    int currentTime = 0;
    int totalWeightedTardiness = 0;

    for (int i = 0; i < n; i++) {
        Task currentTask = tasks[sequence[i]];
        currentTime += currentTask.pi;
        int tardiness = max(0, currentTime - currentTask.di);
        totalWeightedTardiness += currentTask.pi * tardiness;
    }

    return totalWeightedTardiness;
}

void calculateBoundAndTardiness(Node *node, Task tasks[], int n) {
    if (node->nbTasks > 0) {
        node->totalTardiness = calculateWeightedTardinessBranch(tasks, node->sequence, node->nbTasks);
    } else {
        node->totalTardiness = 0;
    }
    node->bound = node->totalTardiness;
    printf("Calculating bounds for node with %d tasks. Total tardiness: %d\n", node->nbTasks, node->totalTardiness);
}

void exploreTree(Node *currentNode, Task tasks[], int n, int *bestTardiness, int bestSequence[]) {
    printf("Exploring node with %d tasks. Current sequence: ", currentNode->nbTasks);
    for (int i = 0; i < currentNode->nbTasks; i++) {
        printf("%d ", currentNode->sequence[i]);
    }
    printf("\n");

    int currentTardiness = calculateWeightedTardinessBranch(tasks, currentNode->sequence, currentNode->nbTasks);
    printf("Current tardiness: %d\n", currentTardiness);

    if (currentNode->nbTasks == n) {
        if (currentTardiness < *bestTardiness) {
            *bestTardiness = currentTardiness;
            memcpy(bestSequence, currentNode->sequence, n * sizeof(int));
            printf("New best sequence found with tardiness %d: ", *bestTardiness);
            for (int i = 0; i < n; i++) {
                printf("%d ", bestSequence[i]);
            }
            printf("\n");
        }
    } else {
        for (int i = 0; i < n; i++) {
            int found = 0;
            for (int j = 0; j < currentNode->nbTasks; j++) {
                if (currentNode->sequence[j] == i) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                Node child;
                memcpy(child.sequence, currentNode->sequence, currentNode->nbTasks * sizeof(int));
                child.sequence[currentNode->nbTasks] = i;
                child.nbTasks = currentNode->nbTasks + 1;
                printf("Creating child node with %d tasks. Adding task: %d\n", child.nbTasks, i);

                calculateBoundAndTardiness(&child, tasks, n);
                if (child.bound < *bestTardiness) {
                    printf("Exploring child node...\n");
                    exploreTree(&child, tasks, n, bestTardiness, bestSequence);
                } else {
                    printf("Pruning child node with bound %d and best tardiness %d\n", child.bound, *bestTardiness);
                }
            }
        }
    }
}

void branch_and_bound(Task tasks[], int n) {
    printf("Initial Tasks:\n");
    for (int i = 0; i < n; ++i) {
        printf("Task %d: pi=%d, di=%d\n", tasks[i].i, tasks[i].pi, tasks[i].di);
    }

    int initialSequence[MAX_TASKS];
    for (int i = 0; i < n; i++) {
        initialSequence[i] = i; // Initial sequence based on task index order
    }

    // Initial best tardiness based on the original order of tasks
    int bestTardiness = calculateWeightedTardinessBranch(tasks, initialSequence, n);
    int bestSequence[MAX_TASKS];

    for (int i = 0; i < n; i++) {
        bestSequence[i] = i; // Initialize bestSequence with the task indices
    }

    Node root;
    root.nbTasks = 0;
    root.totalTardiness = 0;
    calculateBoundAndTardiness(&root, tasks, n); // Corrected to pass 'n' as the third argument

    exploreTree(&root, tasks, n, &bestTardiness, bestSequence);

    printf("Best sequence: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", bestSequence[i]);
    }
    printf("\nBest tardiness: %d\n", bestTardiness);
}

int main() {
    Task tasks[MAX_TASKS] = {
            {1, 14, 2}, // Exemple de tâches
            {2, 98, 68},
            {3, 59, 28},
            {4, 80, 1}
            // Ajoutez d'autres tâches selon votre cas de test
    };
    int n = 4; // Nombre de tâches

    branch_and_bound(tasks, n);

    return 0;
}