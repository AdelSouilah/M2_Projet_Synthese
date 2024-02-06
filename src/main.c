// n, p, d, moyenne de P, moyenne de D, variance de P, variance de D, écart type.
// n, p entre 10 et 100, d = p + 3 a 20, nombre d'instances

#include "aide.h"
#include "heur_EDD.h"
#include "heur_LPT.h"
#include "heur_MinCost.h"
#include "heur_Slack.h"
#include "heur_SPT.h"
#include "instance_gen.h"
#include "rech_taboo.h"
#include "instance_info.h"

int main() {
    srand(time(0));

    int n = 100;
    Task tasks[n];

    // Génération de 10 instances
    for (int i = 0; i < 10; i++) {
        generate_tasks(tasks, n, 10, 100, 2, 50);
        print_task_to_file(tasks, n, "../output/instances.csv");
        save_id_to_file("../output/result.csv", i);

        test_edd(tasks, i, n);
        test_lpt(tasks, i, n);
        test_spt(tasks, i, n);
        test_slack(tasks, i, n);
        test_minCost(tasks, i, n);
        test_taboo(tasks, i, n);

        calculateAllValues(tasks, n);
    }

    // TODO
    //  - ajouter taboo genetique assigment pour branch and bound
    //  - ajouter des ratios de performances pour comparer les algos
    return 0;
}