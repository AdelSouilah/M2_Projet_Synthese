#ifndef M2_PROJET_SYNTHESE_RECH_TABOO_H
#define M2_PROJET_SYNTHESE_RECH_TABOO_H

#include "aide.h"

#define NUM_NEIGHBORS 20
#define NUM_ITERATIONS 5

#define TABOO_SIZE 10

typedef struct {
    int task1;
    int task2;
} TabooMove;

extern TabooMove tabooList[TABOO_SIZE];

void addTabooMove(int task1, int task2);

int isTaboo(int task1, int task2);

void swapTasks(Task *tasks, int i, int j);

void tabooSearch(Task *tasks, int n);

void test_taboo(Task *tasks, int n);

#endif //M2_PROJET_SYNTHESE_RECH_TABOO_H
