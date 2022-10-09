#include "fw_serial_module.h"

void run_fw_serial(graph_t* graph) {
    for (int k = 0; k < graph->N; k++) {
        for (int i = 0; i < graph->N; i++) {
            for (int j = 0; j < graph->N; j++) {
                if (graph->dist[i][j] > graph->dist[i][k] + graph->dist[k][j]) {
                    graph->dist[i][j] = graph->dist[i][k] + graph->dist[k][j];
                }
            }
        }
    }
}