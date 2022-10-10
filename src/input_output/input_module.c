#include "input_module.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void process_input(char *filename, graph_t *graph) {
    FILE *input_file = fopen(filename, "r");
    char line[MAX_LINE_LENGTH];

    if (NULL == fgets(line, MAX_LINE_LENGTH, input_file)) {
        printf("error reading file!\n");
        exit(1);  // reads the first line of the file
    }

    char *ptr = strtok(line, " ");
    int N = atoi(ptr);
    printf("have N=%d\n", N);
    graph->N = N;

    graph->adjacency_matrix = calloc(graph->N, sizeof(int *));

    for (int i = 0; i < graph->N; i++) {
        if (NULL == fgets(line, MAX_LINE_LENGTH, input_file)) {
            printf("error reading file!\n");
            exit(1);  // reads the first line of the file
        }

        int *row = calloc(graph->N, sizeof(int));
        char *delimeter = " ";
        int j = 0;
        char *ptr = strtok(line, delimeter);

        while (ptr != NULL) {
            if (ptr[0] == 'i') {
                row[j] = INFINITY;
            } else {
                row[j] = atoi(ptr);
            }
            ptr = strtok(NULL, delimeter);
            j += 1;
        }
        graph->adjacency_matrix[i] = row;
    }
}