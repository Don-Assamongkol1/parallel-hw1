#include "output_module.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void create_output(bool is_parallel, int num_threads, graph_t* graph) {

    // output files take the form N_4_T_1_parallel_output.txt 
    // for N=4, T=1. If you're serial, you'll just have T=1. 

    char buffer[MAX_STRING_LENGTH];
    char output_filename[MAX_LINE_LENGTH] = "tests/";

    strncat(output_filename, "N_", MAX_STRING_LENGTH);
    sprintf(buffer, "%d_", graph->N);  
    strncat(output_filename, buffer, MAX_STRING_LENGTH);

    strncat(output_filename, "T_", MAX_STRING_LENGTH);
    sprintf(buffer, "%d_", num_threads);  
    strncat(output_filename, buffer, MAX_STRING_LENGTH);
    if (is_parallel) {
        strncat(output_filename, "parallel_output.txt", MAX_STRING_LENGTH);
    } else {
        strncat(output_filename, "serial_output.txt", MAX_STRING_LENGTH);
    }

    remove(output_filename);
    FILE* output_file = fopen(output_filename, "a");
    if (output_file == NULL) {
        printf("Error opening output file");
        exit(1);
    }

    for (int u = 0; u < graph->N; u++) {
        char output_row_weights[MAX_LINE_LENGTH] = "";

        for (int v = 0; v < graph->N; v++) {
            if (graph->dist[u][v] == INFINITY) {
                strncat(output_row_weights, "i ", MAX_STRING_LENGTH);
            } else {
                sprintf(buffer, "%d ", graph->dist[u][v]);  // used to format int (pos/neg) to string
                strncat(output_row_weights, buffer, MAX_STRING_LENGTH);
            }
        }
        fputs(output_row_weights, output_file);
        fputs("\n", output_file);
    }
    fclose(output_file);

    // clean up memory
    for (int i = 0; i < graph->N; i++) {
        free(graph->dist[i]);
    }
    free(graph->dist);
    free(graph);
}