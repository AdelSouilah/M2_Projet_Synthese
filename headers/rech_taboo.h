#ifndef M2_PROJET_SYNTHESE_RECH_TABOO_H
#define M2_PROJET_SYNTHESE_RECH_TABOO_H

#include "aide.h"

#define NUM_NEIGHBORS 20  // Nombre de voisins à générer par itération
#define NUM_ITERATIONS 5  // Nombre total d'itérations

#define TABOO_SIZE 10  // Taille de la liste tabou

typedef struct {
    int task1;
    int task2;
} TabooMove;

TabooMove tabooList[TABOO_SIZE];

void addTabooMove(int task1, int task2);

int isTaboo(int task1, int task2);

void swapTasks(Task *tasks, int i, int j);

void tabooSearch(Task *tasks, int n);

void test_taboo(Task *tasks, int i, int n);

#endif //M2_PROJET_SYNTHESE_RECH_TABOO_H
