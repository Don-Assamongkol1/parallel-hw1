#include "fw_serial_module.h"
#include <stdio.h>
#include <stdlib.h>
#include "stopwatch.h"

void run_fw_serial(graph_t* graph) {

    StopWatch_t *stopwatch = malloc(sizeof(StopWatch_t));
    startTimer(stopwatch);


    for (int k = 0; k < graph->N; k++) {
        for (int i = 0; i < graph->N; i++) {
            for (int j = 0; j < graph->N; j++) {
                if (graph->dist[i][j] > graph->dist[i][k] + graph->dist[k][j]) {
                    graph->dist[i][j] = graph->dist[i][k] + graph->dist[k][j];
                }
            }
        }
    }

    stopTimer(stopwatch);
    double elapsed_time = getElapsedTime(stopwatch);
    printf("elapsed_time: %f\n", elapsed_time);
    free(stopwatch);
}