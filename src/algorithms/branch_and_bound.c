#include "branch_and_bound.h"
#include "instance_gen.h"

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
}

void exploreTree(Node *currentNode, Task tasks[], int n, int *bestTardiness, int bestSequence[]) {
    int currentTardiness = calculateWeightedTardinessBranch(tasks, currentNode->sequence, currentNode->nbTasks);

    if (currentNode->nbTasks == n) {
        if (currentTardiness < *bestTardiness) {
            *bestTardiness = currentTardiness;
            memcpy(bestSequence, currentNode->sequence, n * sizeof(int));
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

                calculateBoundAndTardiness(&child, tasks, n);
                if (child.bound < *bestTardiness) {
                    exploreTree(&child, tasks, n, bestTardiness, bestSequence);
                }
            }
        }
    }
}

void branch_and_bound(Task tasks[], int n) {
    int initialSequence[MAX_TASKS];
    for (int i = 0; i < n; i++) {
        initialSequence[i] = i;
    }

    int bestTardiness = calculateWeightedTardinessBranch(tasks, initialSequence, n);
    int bestSequence[MAX_TASKS];

    for (int i = 0; i < n; i++) {
        bestSequence[i] = i;
    }

    Node root;
    root.nbTasks = 0;
    root.totalTardiness = 0;
    calculateBoundAndTardiness(&root, tasks, n);

    exploreTree(&root, tasks, n, &bestTardiness, bestSequence);
}

void test_branch_and_bound(Task *tasks, int n) {
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    branch_and_bound(tasks, n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    int tardiness = calculateWeightedTardiness(tasks, n);
//    printf("Retard branch and bound: %d\n\n", tardiness);
    save_tard_and_time_to_file("../output/result.csv", cpu_time_used, tardiness);
}