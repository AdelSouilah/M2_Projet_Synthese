#include "instance_info.h"
#include "instance_gen.h"

// Fonction pour calculer la moyenne des durées (pi) et des dates de fin (di)
void calculateAverages(Task *tasks, int numTasks, double *avgDuration, double *avgDeadline) {
    int totalDuration = 0;
    int totalDeadline = 0;

    for (int i = 0; i < numTasks; i++) {
        totalDuration += tasks[i].pi;
        totalDeadline += tasks[i].di;
    }

    *avgDuration = (double) totalDuration / numTasks;
    *avgDeadline = (double) totalDeadline / numTasks;
}

// Fonction pour calculer la variance des durées (pi) et des dates de fin (di)
void calculateVariance(Task *tasks, int numTasks, double avgDuration, double avgDeadline, double *varianceDuration,
                       double *varianceDeadline) {
    double sumSquaredDeviationDuration = 0;
    double sumSquaredDeviationDeadline = 0;

    for (int i = 0; i < numTasks; i++) {
        sumSquaredDeviationDuration += pow(tasks[i].pi - avgDuration, 2);
        sumSquaredDeviationDeadline += pow(tasks[i].di - avgDeadline, 2);
    }

    *varianceDuration = sumSquaredDeviationDuration / numTasks;
    *varianceDeadline = sumSquaredDeviationDeadline / numTasks;
}

// Fonction pour calculer l'écart type des durées (pi) et des dates de fin (di)
void calculateStandardDeviation(double varianceDuration, double varianceDeadline, double *stdDevDuration,
                                double *stdDevDeadline) {
    *stdDevDuration = sqrt(varianceDuration);
    *stdDevDeadline = sqrt(varianceDeadline);
}

void calculateAllValues(Task *tasks, int n) {
    double avgDuration, avgDeadline;
    double varianceDuration, varianceDeadline;
    double stdDevDuration, stdDevDeadline;

    calculateAverages(tasks, n, &avgDuration, &avgDeadline);
    calculateVariance(tasks, n, avgDuration, avgDeadline, &varianceDuration, &varianceDeadline);
    calculateStandardDeviation(varianceDuration, varianceDeadline, &stdDevDuration, &stdDevDeadline);

/*    printf("Moyenne des durees (pi): %.2f\n", avgDuration);
    printf("Moyenne des dates de fin (di): %.2f\n", avgDeadline);
    printf("Variance des durees (pi): %.2f\n", varianceDuration);
    printf("Variance des dates de fin (di): %.2f\n", varianceDeadline);
    printf("Ecart type des durees (pi): %.2f\n", stdDevDuration);
    printf("Ecart type des dates de fin (di): %.2f\n", stdDevDeadline);*/
    save_inst_info_to_file("../output/result.csv", avgDuration, avgDeadline, varianceDuration, varianceDeadline,
                           stdDevDuration, stdDevDeadline);
}