#ifndef M2_PROJET_SYNTHESE_BRANCH_AND_BOUND_H
#define M2_PROJET_SYNTHESE_BRANCH_AND_BOUND_H

#include "aide.h"

#define MAX_TASKS 100

typedef struct Node {
    int sequence[MAX_TASKS]; // IDs des tâches dans l'ordre de planification
    int nbTasks; // Nombre de tâches planifiées dans ce nœud
    int bound; // Borne inférieure de la solution partielle
    int totalTardiness; // Retard total de la solution partielle
} Node;

int calculateTardiness(int sequence[], Task tasks[], int nbTasks);
int calculateWeightedTardinessBranch(Task tasks[], int sequence[], int n);
void calculateBoundAndTardiness(Node *node, Task tasks[], int n);
void exploreTree(Node *currentNode, Task tasks[], int n, int *bestTardiness, int bestSequence[]);
void branch_and_bound(Task tasks[], int n);
void test_branch_and_bound(Task *tasks, int n);

#endif //M2_PROJET_SYNTHESE_BRANCH_AND_BOUND_H
