#ifndef M2_PROJET_SYNTHESE_ALGO_GEN_H
#define M2_PROJET_SYNTHESE_ALGO_GEN_H

#include "aide.h"
#include "instance_gen.h"

#define POPULATION_SIZE 100 // Nombre d'individus de la population
#define TAUX_CROISEMENT 0.8
#define TAUX_MUTATION 0.1
#define NUM_GENERATIONS 1000

// Structure pour un individu (solution)
typedef struct {
    Task** sequence; // Pointeur vers un tableau de pointeurs vers Task
    int fitness;
} Individu;

// Prototypes des fonctions
void evaluerFitness(Individu* individu, int n);
void initialiserPopulation(Individu population[POPULATION_SIZE], Task *tasks, int i);
void selectionnerParTournoi(Individu population[POPULATION_SIZE], int taillePopulation, Individu **parentSelectionne);
void croiser(Individu **parent1, Individu **parent2, Individu *enfant1, Individu *enfant2, int n);
void muter(Individu *individu, int n);
void selectionElitiste(Individu population[], Individu enfants[], int taillePopulation);
void remplacementGenerationnel(Individu population[], Individu enfants[], int taillePopulation);
void trierParFitness(Individu population[], int taille);
void libererPopulation(Individu population[POPULATION_SIZE]);
int algo_gen(Task *tasks, int n);
void test_algo_gen(Task *tasks, int n);

#endif //M2_PROJET_SYNTHESE_ALGO_GEN_H
