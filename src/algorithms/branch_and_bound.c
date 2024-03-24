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

void calculateBoundAndTardiness(Node *node, Task tasks[], int n);

int calculateTardiness(int sequence[], Task tasks[], int n);

// Mettez ici les implémentations des fonctions calculateBoundAndTardiness et calculateTardiness

// Calcule la tardiveté d'une séquence de tâches
int calculateTardiness(int sequence[], Task tasks[], int n) {
    int tardiness = 0;
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        Task task = tasks[sequence[i]];
        currentTime += task.pi;
        if (currentTime > task.di) {
            tardiness += (currentTime - task.di) * task.pi; // Ponderation par pi si nécessaire
        }
    }

    return tardiness;
}

// Met à jour la borne inférieure et la tardiveté totale pour un nœud donné
void calculateBoundAndTardiness(Node *node, Task tasks[], int n) {
    // Supposons que la borne inférieure soit simplement la tardiveté actuelle
    // Plusieurs approches peuvent être utilisées pour calculer une borne inférieure plus serrée
    node->totalTardiness = calculateTardiness(node->sequence, tasks, n);
    node->bound = node->totalTardiness; // Simplification pour l'exemple
}

void exploreTree(Node *currentNode, Task tasks[], int n, int *bestTardiness, int bestSequence[]) {
    if (currentNode->nbTasks == n) {
        // Si le nœud est une feuille (solution complète), vérifiez si c'est la meilleure solution
        if (currentNode->totalTardiness < *bestTardiness) {
            *bestTardiness = currentNode->totalTardiness;
            for (int i = 0; i < n; i++) {
                bestSequence[i] = currentNode->sequence[i];
            }
        }
    } else {
        for (int i = 0; i < n; i++) {
            // Vérifiez si la tâche i est déjà dans la séquence
            int found = 0;
            for (int j = 0; j < currentNode->nbTasks; j++) {
                if (currentNode->sequence[j] == i) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                Node child = *currentNode;
                child.sequence[child.nbTasks++] = i;
                calculateBoundAndTardiness(&child, tasks, n);
                if (child.bound < *bestTardiness) {
                    exploreTree(&child, tasks, n, bestTardiness, bestSequence);
                }
            }
        }
    }
}

// La fonction principale branch_and_bound
void branch_and_bound(Task tasks[], int n) {
    int bestTardiness = calculateWeightedTardiness(tasks, n);
    int bestSequence[MAX_TASKS];

    // Initialisation du nœud racine
    Node root;
    root.nbTasks = 0;
    root.totalTardiness = 0;
    calculateBoundAndTardiness(&root, tasks, n);

    // Exploration de l'arbre de recherche pour trouver la meilleure séquence
    exploreTree(&root, tasks, n, &bestTardiness, bestSequence);

    // Affichage de la meilleure séquence et de la tardiveté totale minimale
    for (int i = 0; i < n; i++) {
        printf("%d ", tasks[bestSequence[i]].i); // Utilisez l'ID de la tâche et non l'indice
    }
    printf("\nRetard total minimal: %d\n", bestTardiness);
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