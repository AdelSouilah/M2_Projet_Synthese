#include "algo_gen.h"

void evaluerFitness(Individu *individu) {
    int retardTotal = 0;
    int tempsCompletion = 0;

    for (int j = 0; j < NBR_JOBS; j++) {
        Task *tache = individu->sequence[j];
        tempsCompletion += tache->pi;
        int retard = tempsCompletion > tache->di ? tempsCompletion - tache->di : 0;
        retardTotal += tache->pi * retard;
    }

    individu->fitness = retardTotal;
}

void initialiserPopulation(Individu population[POPULATION_SIZE], Task *tasks, int n) {
    printf("Initialisation de la population...\n");
    for (int i = 0; i < POPULATION_SIZE; i++) {
        // Initialiser avec l'ordre par défaut
        for (int j = 0; j < n; j++) {
            population[i].sequence[j] = &tasks[j]; // Stocker les adresses des tâches
        }

        // Mélanger la séquence pour créer une solution initiale aléatoire
        for (int j = 0; j < n; j++) {
            int indexAleatoire = rand() % n;
            Task *temp = population[i].sequence[j];
            population[i].sequence[j] = population[i].sequence[indexAleatoire];
            population[i].sequence[indexAleatoire] = temp;
        }

        evaluerFitness(&population[i]);

        // Log pour vérifier l'initialisation
        printf("Individu %d, Séquence initiale: ", i);
        for (int j = 0; j < n; j++) {
            printf("%d ", population[i].sequence[j]->i);
        }
        printf("\n");
    }
    printf("\n");
}

void selectionnerParTournoi(Individu population[POPULATION_SIZE], int taillePopulation, Individu **parentSelectionne) {
    int meilleurIndex = rand() % taillePopulation;
    for (int i = 0; i < 2; i++) { // Tournoi entre 2 individus
        int index = rand() % taillePopulation;
        if (population[index].fitness < population[meilleurIndex].fitness) {
            meilleurIndex = index;
        }
    }
    *parentSelectionne = &population[meilleurIndex];
}


void croiser(Individu **parent1, Individu **parent2, Individu *enfant1, Individu *enfant2) {
    // Sélectionner un point de croisement aléatoire, à l'exception des extrémités
    int pointCroisement = rand() % (NBR_JOBS - 2) + 1;
    int enfant1Index = pointCroisement, enfant2Index = pointCroisement;

    // Copie directe depuis les parents jusqu'au point de croisement
    for (int i = 0; i < pointCroisement; i++) {
        enfant1->sequence[i] = (*parent1)->sequence[i];
        enfant2->sequence[i] = (*parent2)->sequence[i];
    }

    printf("Croisement entre deux parents au point %d\n", pointCroisement);
    printf("Parent 1 avant croisement: ");
    for (int i = 0; i < NBR_JOBS; i++) {
        printf("%d ", (*parent1)->sequence[i]->i);
    }
    printf("\nParent 2 avant croisement: ");
    for (int i = 0; i < NBR_JOBS; i++) {
        printf("%d ", (*parent2)->sequence[i]->i);
    }

    // Pour la seconde partie, ajouter les tâches du parent opposé qui ne sont pas déjà présentes
    for (int i = 0; i < NBR_JOBS; i++) {
        Task* tacheParent2 = (*parent2)->sequence[i];
        Task* tacheParent1 = (*parent1)->sequence[i];

        // Vérifier si la tâche de parent2 est déjà dans enfant1
        int estDansEnfant1 = 0;
        for (int j = 0; j < enfant1Index; j++) {
            if (enfant1->sequence[j] == tacheParent2) {
                estDansEnfant1 = 1;
                break;
            }
        }
        if (!estDansEnfant1 && enfant1Index < NBR_JOBS) {
            enfant1->sequence[enfant1Index++] = tacheParent2;
        }

        // Vérifier si la tâche de parent1 est déjà dans enfant2
        int estDansEnfant2 = 0;
        for (int j = 0; j < enfant2Index; j++) {
            if (enfant2->sequence[j] == tacheParent1) {
                estDansEnfant2 = 1;
                break;
            }
        }
        if (!estDansEnfant2 && enfant2Index < NBR_JOBS) {
            enfant2->sequence[enfant2Index++] = tacheParent1;
        }
    }

    // Log pour vérifier les séquences des enfants après le croisement
    printf("\nEnfant 1 après croisement: ");
    for (int i = 0; i < NBR_JOBS; i++) {
        printf("%d ", enfant1->sequence[i]->i);
    }
    printf("\nEnfant 2 après croisement: ");
    for (int i = 0; i < NBR_JOBS; i++) {
        printf("%d ", enfant2->sequence[i]->i);
    }
    printf("\n");

    evaluerFitness(enfant1);
    evaluerFitness(enfant2);
}

void muter(Individu *individu) {
    // Parcourir chaque tâche de l'individu
    for (int i = 0; i < NBR_JOBS; i++) {
        // Générer un nombre aléatoire entre 0 et 1 pour décider si la mutation doit avoir lieu
        float prob = (float) rand() / RAND_MAX;
        if (prob < TAUX_MUTATION) {
            // Sélectionner une autre tâche aléatoirement pour l'échange
            int indexEchange = rand() % NBR_JOBS;
            printf("Mutation dans l'individu, échange entre les tâches %d et %d\n", individu->sequence[i]->i,
                   individu->sequence[indexEchange]->i);

            // Échanger les tâches à l'indice i et indexEchange
            Task *temp = individu->sequence[i];
            individu->sequence[i] = individu->sequence[indexEchange];
            individu->sequence[indexEchange] = temp;
        }
    }

    // Recalculer la fitness de l'individu après la mutation
    evaluerFitness(individu);
}

void selectionElitiste(Individu population[], Individu enfants[], int taillePopulation) {
    Individu tousIndividus[2 * taillePopulation];
    // Fusionner la population actuelle et les enfants
    for (int i = 0; i < taillePopulation; i++) {
        tousIndividus[i] = population[i];
        tousIndividus[i + taillePopulation] = enfants[i];
    }

    // Trier tous les individus par leur fitness (fonction de tri non montrée)
    trierParFitness(tousIndividus, 2 * taillePopulation);

    // Conserver les meilleurs individus pour la nouvelle population
    for (int i = 0; i < taillePopulation; i++) {
        population[i] = tousIndividus[i];
    }
}

void remplacementGenerationnel(Individu population[], Individu enfants[], int taillePopulation) {
    // Simplement copier les enfants dans la population, en remplaçant les parents
    for (int i = 0; i < taillePopulation; i++) {
        population[i] = enfants[i];
    }
}

// Fonction auxiliaire pour trier la population par fitness
// Cette fonction est une simplification. Vous devrez implémenter ou utiliser une fonction de tri adéquate.
void trierParFitness(Individu population[], int taille) {
    for (int i = 0; i < taille - 1; i++) {
        for (int j = 0; j < taille - i - 1; j++) {
            if (population[j].fitness > population[j + 1].fitness) {
                Individu temp = population[j];
                population[j] = population[j + 1];
                population[j + 1] = temp;
            }
        }
    }
}

// Main function
int algo_gen(Task *tasks, int n) {
    Individu population[POPULATION_SIZE];

    // Initialisation de la population
    initialiserPopulation(population, tasks, n);

    for (int generation = 0; generation < NUM_GENERATIONS; generation++) {
        Individu nouveauxIndividus[POPULATION_SIZE];

        // Boucle de reproduction
        for (int i = 0; i < POPULATION_SIZE; i += 2) {

            Individu *parent1;
            Individu *parent2;

            Individu enfant1, enfant2;

            // Sélection du premier parent
            selectionnerParTournoi(population, POPULATION_SIZE, &parent1);
            // Sélection du deuxième parent
            selectionnerParTournoi(population, POPULATION_SIZE, &parent2);

            // Croisement
            croiser(&parent1, &parent2, &enfant1, &enfant2);

            // Mutation
            muter(&enfant1);
            muter(&enfant2);

            evaluerFitness(&enfant1);
            evaluerFitness(&enfant2);

            // Ajouter les enfants à la nouvelle population
            nouveauxIndividus[i] = enfant1;
            if (i + 1 < POPULATION_SIZE) nouveauxIndividus[i + 1] = enfant2;
        }

        // Remplacement générationnel ou sélection élitiste
        remplacementGenerationnel(population, nouveauxIndividus, POPULATION_SIZE);
        // Ou, si vous utilisez la sélection élitiste (non illustrée ici)
        // selectionElitiste(population, enfants, POPULATION_SIZE);

        // Ici, vous pouvez ajouter du code pour enregistrer/afficher les résultats intermédiaires si nécessaire
    }

    // Trouver le meilleur individu de la population finale
    int meilleurIndex = 0;
    for (int i = 1; i < POPULATION_SIZE; i++) {
        if (population[i].fitness < population[meilleurIndex].fitness) {
            meilleurIndex = i;
        }
    }

    // Afficher la séquence du meilleur individu
    printf("Meilleure séquence: ");
    for (int i = 0; i < NBR_JOBS; i++) {
        printf("%d ",
               population[meilleurIndex].sequence[i]->i); // Assurez-vous que cela correspond à votre structure de données
    }
    printf("\nRetard total minimal: %d\n", population[meilleurIndex].fitness);

    // Retourner le retard du meilleur individu
    return population[meilleurIndex].fitness;
}

void test_algo_gen(Task *tasks, int n) {
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    int tardiness = algo_gen(tasks, n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    int tardiness2 = calculateWeightedTardiness(tasks, n);
    printf("Fake tardi : %d\n", tardiness2);
    save_tard_and_time_to_file("../output/result.csv", cpu_time_used, tardiness);
}
