#ifndef M2_PROJET_SYNTHESE_INSTANCE_INFO_H
#define M2_PROJET_SYNTHESE_INSTANCE_INFO_H

#include <stdio.h>
#include <math.h> // Pour la fonction sqrt()
#include "task.h"

#define NUM_TASKS 5 // Nombre de tâches

// Fonction pour calculer la moyenne des durées (pi) et des dates de fin (di)
void calculateAverages(Task *tasks, int numTasks, double *avgDuration, double *avgDeadline);

// Fonction pour calculer la variance des durées (pi) et des dates de fin (di)
void calculateVariance(Task *tasks, int numTasks, double avgDuration, double avgDeadline, double *varianceDuration, double *varianceDeadline);

// Fonction pour calculer l'écart type des durées (pi) et des dates de fin (di)
void calculateStandardDeviation(double varianceDuration, double varianceDeadline, double *stdDevDuration, double *stdDevDeadline);

// Fonction pour calculer toutes les valeurs
void calculateAllValues(Task *tasks, int n);

#endif //M2_PROJET_SYNTHESE_INSTANCE_INFO_H
