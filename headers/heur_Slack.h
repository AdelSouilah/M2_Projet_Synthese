#ifndef M2_PROJET_SYNTHESE_HEUR_SLACK_H
#define M2_PROJET_SYNTHESE_HEUR_SLACK_H

#include "aide.h"

int compare_slack(const void *a, const void *b);

void minimum_slack_rule(Task *tasks, int n);

void test_slack(Task *tasks, int n);

#endif //M2_PROJET_SYNTHESE_HEUR_SLACK_H
