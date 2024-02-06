#ifndef M2_PROJET_SYNTHESE_HEUR_EDD_H
#define M2_PROJET_SYNTHESE_HEUR_EDD_H

#include "aide.h"

int compare_edd(const void *a, const void *b);

void edd_rule(Task *tasks, int n);

void test_edd(Task *tasks, int n);

#endif //M2_PROJET_SYNTHESE_HEUR_EDD_H
