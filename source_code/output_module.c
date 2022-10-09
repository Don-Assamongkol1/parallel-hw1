#include "output_module.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void create_output(char* output_filename, graph_t* graph) {
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
                char buffer[MAX_STRING_LENGTH];
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