#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct {
    int i;
    int di;
    int pi;
} Task;

void generate_tasks(Task *tasks, int n, int pi_min, int pi_max, int di_min, int di_max) {
    for (int i = 0; i < n; ++i) {
        tasks[i].i = i;
        tasks[i].pi = (rand() %(pi_max - pi_min + 1)) + pi_min;
        tasks[i].di = tasks[i].pi + (rand() %(di_max - di_min + 1)) + di_min;
    }
}

void print_to_file(Task *tasks, int n, char *filename) {
    FILE *file = fopen(filename, "a");
    fprintf(file, "\n");
    for (int i = 0; i < n - 1; i++) {
        fprintf(file, "%d,%d;",tasks[i].di, tasks[i].pi);
    }
    fprintf(file, "%d,%d",tasks[n - 1].di, tasks[n - 1].pi);
    fclose(file);
}

void display_tasks(Task *tasks, int n) {
    printf("ID\tDeadline\tDuration/Weight\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\n", tasks[i].i, tasks[i].di, tasks[i].pi);
    }
    printf("\n");
}

int compare_edd(const void *a, const void *b) {
    Task *taskA = (Task *) a;
    Task *taskB = (Task *) b;
    return taskA->di - taskB->di;
}

void edd_rule(Task *tasks, int n) {
    qsort(tasks, n, sizeof(Task), compare_edd);
}

int main() {
    clock_t start, end;
    double cpu_time_used;

    srand(time(0));
    int n = 100;
    Task task[n];
    for (int i = 0; i < 10; i++) {
        generate_tasks(task, n, 10, 100, 2, 20);
        print_to_file(task, n, "../Instance.csv");
    }

    // Test de la règle EDD
    printf("Ordo EDD:\n");
    start = clock();
    edd_rule(task, n);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("time : %f\n", cpu_time_used);
//    display_tasks(task, n);
    print_to_file(task, n, "../Instance.csv");
    return 0;
}