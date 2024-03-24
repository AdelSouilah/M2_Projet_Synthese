#ifndef M2_PROJET_SYNTHESE_ALGO_GEN_H
#define M2_PROJET_SYNTHESE_ALGO_GEN_H

#include "aide.h"
#include "instance_gen.h"

#define POPULATION_SIZE 100 // Nombre d'individus de la population
#define NBR_JOBS 100
#define TAUX_CROISEMENT 0.8
#define TAUX_MUTATION 0.1
#define NUM_GENERATIONS 1000

// Structure pour un individu (solution)
typedef struct {
    Task* sequence[NBR_JOBS]; // Tableau de pointeurs vers Task
    int fitness;
} Individu;

// Prototypes des fonctions
void evaluerFitness(Individu* individu);
void initialiserPopulation(Individu population[POPULATION_SIZE], Task *ptr, int i);
void selectionner(Individu population[POPULATION_SIZE], Individu parents[2]);
void croiser(Individu parent1, Individu parent2, Individu* enfant1, Individu* enfant2);
void muter(Individu* individu);
void remplacerPopulation(Individu population[POPULATION_SIZE], Individu nouveauxIndividus[POPULATION_SIZE]);
void selectionnerParTournoi(Individu population[POPULATION_SIZE], Individu *parent);
void croiserUnPoint(Individu parent1, Individu parent2, Individu *enfant1, Individu *enfant2);
void muterParEchange(Individu *individu);
int contient(int sequence[], int longueur, int job);
void trierParFitness(Individu population[], int taille);
int algo_gen(Task *tasks, int n);
void test_algo_gen(Task *tasks, int n);

#endif //M2_PROJET_SYNTHESE_ALGO_GEN_H