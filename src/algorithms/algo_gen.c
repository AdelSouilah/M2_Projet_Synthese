#include "algo_gen.h"

void evaluerFitness(Individu* individu) {
    int retardTotal = 0;
    int tempsCompletion = 0;

    for (int j = 0; j < NBR_JOBS; j++) {
        Task* tache = individu->sequence[j];
        tempsCompletion += tache->pi;
        int retard = tempsCompletion > tache->di ? tempsCompletion - tache->di : 0;
        retardTotal += tache->pi * retard;
    }

    individu->fitness = retardTotal;
}

void initialiserPopulation(Individu population[POPULATION_SIZE], Task *tasks, int n) {
    for (int i = 0; i < POPULATION_SIZE; i++) {
        // Initialiser avec l'ordre par défaut
        for (int j = 0; j < n; j++) {
            population[i].sequence[j] = &tasks[j]; // Stocker les adresses des tâches
        }

        // Mélanger la séquence pour créer une solution initiale aléatoire
        for (int j = 0; j < n; j++) {
            int indexAleatoire = rand() % n;
            Task* temp = population[i].sequence[j];
            population[i].sequence[j] = population[i].sequence[indexAleatoire];
            population[i].sequence[indexAleatoire] = temp;
        }

        evaluerFitness(&population[i]);
    }
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


/*void croiserUnPoint(Individu parent1, Individu parent2, Individu *enfant1, Individu *enfant2) {
    int pointDeCroisement = rand() % (NBR_JOBS - 1) + 1; // Éviter les extrémités

    // Initialiser les enfants avec des valeurs non valides
    for (int i = 0; i < NBR_JOBS; i++) {
        enfant1->sequence[i] = -1;
        enfant2->sequence[i] = -1;
    }

    // Copier les segments avant le point de croisement
    for (int i = 0; i < pointDeCroisement; i++) {
        enfant1->sequence[i] = parent1.sequence[i];
        enfant2->sequence[i] = parent2.sequence[i];
    }

    // Compléter les séquences des enfants avec les jobs manquants
    for (int i = pointDeCroisement, j = pointDeCroisement, k = pointDeCroisement; i < NBR_JOBS;) {
        if (!contient(enfant1->sequence, NBR_JOBS, parent2.sequence[j])) {
            enfant1->sequence[i++] = parent2.sequence[j];
        }
        if (!contient(enfant2->sequence, NBR_JOBS, parent1.sequence[k])) {
            enfant2->sequence[i++] = parent1.sequence[k];
        }
        j = (j + 1) % NBR_JOBS;
        k = (k + 1) % NBR_JOBS;
    }

    evaluerFitness(enfant1);
    evaluerFitness(enfant2);
}

void muterParEchange(Individu *individu) {
    if ((double)rand() / RAND_MAX < TAUX_MUTATION) {
        int index1 = rand() % NBR_JOBS;
        int index2 = rand() % NBR_JOBS;

        // Échanger deux jobs
        int temp = individu->sequence[index1];
        individu->sequence[index1] = individu->sequence[index2];
        individu->sequence[index2] = temp;

        evaluerFitness(individu);
    }
}

void remplacerPopulation(Individu population[POPULATION_SIZE], Individu nouveauxIndividus[POPULATION_SIZE]) {
    // Tri des populations combinées basé sur la fitness
    // Pour simplifier, supposons une fonction de tri générique
    trierParFitness(population, POPULATION_SIZE);
    trierParFitness(nouveauxIndividus, POPULATION_SIZE);
// Conserver les N meilleurs individus entre l'ancienne et la nouvelle population
    Individu populationCombinee[2 * POPULATION_SIZE];
    for (int i = 0; i < POPULATION_SIZE; i++) {
        populationCombinee[i] = population[i];
        populationCombinee[i + POPULATION_SIZE] = nouveauxIndividus[i];
    }

// Trier la population combinée par fitness
    trierParFitness(populationCombinee, 2 * POPULATION_SIZE);

// Sélectionner les POPULATION_SIZE meilleurs pour la nouvelle génération
    for (int i = 0; i < POPULATION_SIZE; i++) {
        population[i] = populationCombinee[i];
    }
}
// Fonction auxiliaire pour vérifier si un job est déjà dans la séquence
int contient(int sequence[], int longueur, int job) {
    for (int i = 0; i < longueur; i++) {
        if (sequence[i] == job) {
            return 1; // Trouvé
        }
    }
    return 0; // Non trouvé
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
}*/

// Main function
int algo_gen(Task *tasks, int n) {
    Individu population[POPULATION_SIZE];

    // Initialisation de la population
    initialiserPopulation(population, tasks, n);

    for (int generation = 0; generation < NUM_GENERATIONS; generation++) {
        Individu nouveauxIndividus[POPULATION_SIZE];

        // Boucle de reproduction
        for (int i = 0; i < POPULATION_SIZE; i += 2) {

            Individu* parent1;
            Individu* parent2;

            Individu enfant1, enfant2;

            // Sélection du premier parent
            selectionnerParTournoi(population, POPULATION_SIZE, &parent1);
            // Sélection du deuxième parent
            selectionnerParTournoi(population, POPULATION_SIZE, &parent2);

            printf("Hello");
            // Croisement
     /*       croiser(parents[0], parents[1], &enfant1, &enfant2);

            // Mutation
            muter(&enfant1);
            muter(&enfant2);

            // Ajouter les enfants à la nouvelle population
            nouveauxIndividus[i] = enfant1;
            if (i + 1 < POPULATION_SIZE) nouveauxIndividus[i + 1] = enfant2;*/
        }

        // Remplacer l'ancienne population par la nouvelle
//        remplacerPopulation(population, nouveauxIndividus);
    }

    // Afficher la meilleure solution
    // ...

    return 0;
}

void test_algo_gen(Task *tasks, int n) {
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    algo_gen(tasks, n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    int tardiness = calculateWeightedTardiness(tasks, n);
    save_tard_and_time_to_file("../output/result.csv", cpu_time_used, tardiness);
}
