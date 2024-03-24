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
#include "algo_gen.h"

int main() {
    srand(time(0));

    int n = 100;
    Task tasks[n];

    // Génération de 10 instances
    for (int i = 0; i < 10; i++) {
        generate_tasks(tasks, n, 10, 100, 2, 50);
        print_task_to_file(tasks, n, "../output/instances.csv");
        save_id_to_file("../output/result.csv", i);

/*        test_edd(tasks, n);
        test_lpt(tasks, n);
        test_spt(tasks, n);
        test_slack(tasks, n);
        test_minCost(tasks, n);
        test_taboo(tasks, n);*/
        test_algo_gen(tasks, n);

        calculateAllMetaValues(tasks, n);
    }

    // TODO
    //  - ajouter taboo genetique assigment pour branch and bound
    //  - ajouter des ratios de performances pour comparer les algos
    return 0;
}