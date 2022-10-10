#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fw_parallel_module.h"
#include "input_module.h"
#include "output_module.h"
#include "stopwatch.h"
#include "types.h"

// compile using: gcc -Wall -Werror -O3 parallel_FW.c input_module.c output_module.c fw_parallel_module.c stopwatch.c -pthread -o parallel_FW
// run using: ./parallel_FW 1_sample_input.txt 128

int main(int argc, char **argv) {
    printf("Beginning parallel_FW\n");

    /* Parse command line args */
    if (argc != 3) {
        /* EXAMPLE: ./customer_software_serial sample_input.txt 128 */
        printf("ERROR!: expected two arguments: thread count and input filename\n");
        exit(1);
    }

    char *input_filename = argv[1];
    int num_threads = atoi(argv[2]);

    /* STEP 1: PROCESS INPUT */
    printf("beginning step 1\n");
    graph_t *graph = calloc(1, sizeof(graph_t));
    process_input(input_filename, graph);
    printf("finished with step 1\n");

    /* STEP 2: RUN FW */
    printf("beginning step 2\n");
    graph->dist = graph->adjacency_matrix;

    StopWatch_t *stopwatch = malloc(sizeof(StopWatch_t));
    startTimer(stopwatch);

    printf("before run_fw_parallel \n");
    run_fw_parallel(graph, num_threads);
    printf("after run_fw_parallel \n");

    
    stopTimer(stopwatch);
    double elapsed_time = getElapsedTime(stopwatch);
    free(stopwatch);
    printf("elapsed_time: %f\n", elapsed_time);

    printf("finished with step 2\n");


    /* STEP 3: CREATE OUTPUT */
    printf("beginning step 3\n");
    create_output(true, num_threads, graph);
    printf("finished with step 2\n");


    printf("End of parallel_FW\n");
}