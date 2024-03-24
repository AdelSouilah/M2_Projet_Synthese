#ifndef M2_PROJET_SYNTHESE_HEUR_LPT_H
#define M2_PROJET_SYNTHESE_HEUR_LPT_H

#include "aide.h"

int compare_lpt(const void *a, const void *b);

void lpt_rule(Task *tasks, int n);

void test_lpt(Task *tasks, int n);

#endif //M2_PROJET_SYNTHESE_HEUR_LPT_H
