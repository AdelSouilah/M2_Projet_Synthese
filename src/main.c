// n, p, d, moyenne de P, moyenne de D, variance de P, variance de D, écart type.
// n, p entre 10 et 100, d = p + 3 a 20, nombre d'instances

#include "aide.h"
#include "heur_EDD.h"
#include "heur_LPT.h"
#include "heur_MinCost.h"
#include "heur_Slack.h"
#include "heur_SPT.h"
#include "instance_gen.h"

int main() {
    srand(time(0));

    int n = 100;
    Task task[n];

    // Génération de 10 instances
    for (int i = 0; i < 10; i++) {
        generate_tasks(task, n, 10, 100, 2, 20);
        print_task_to_file(task, n, "../output/instances.csv");
        test_edd(task, n);
        test_lpt(task, n);
        test_spt(task, n);
        test_slack(task, n);
        test_minCost(task, n);
    }

    return 0;
}