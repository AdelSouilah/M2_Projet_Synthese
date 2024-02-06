#ifndef M2_PROJET_SYNTHESE_HEUR_SPT_H
#define M2_PROJET_SYNTHESE_HEUR_SPT_H

#include "aide.h"

int compare_spt(const void *a, const void *b);

void spt_rule(Task *tasks, int n);

void test_spt(Task *tasks, int i, int n);

#endif //M2_PROJET_SYNTHESE_HEUR_SPT_H
