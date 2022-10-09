#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fw_serial_module.h"
#include "input_module.h"
#include "output_module.h"
#include "stopwatch.h"
#include "types.h"

// compile using: gcc -Wall -Werror -O3 serial_FW.c input_module.c output_module.c fw_serial_module.c stopwatch.c -o serial_FW

int main(int argc, char **argv) {
    printf("Beginning serial_FW\n");

    /* Parse command line args */
    if (argc != 3) {
        /* EXAMPLE: ./customer_software_serial sample_input.txt 128 */
        printf("ERROR!: expected two arguments: thread count and input filename\n");
        exit(1);
    }

    char *input_filename = argv[1];
    // int num_threads = atoi(argv[2]);

    /* STEP 1: PROCESS INPUT */
    graph_t *graph = calloc(1, sizeof(graph_t));
    process_input(input_filename, graph);

    /* STEP 2: RUN FW */
    graph->dist = graph->adjacency_matrix;

    StopWatch_t *stopwatch = malloc(sizeof(StopWatch_t));
    startTimer(stopwatch);
    run_fw_serial(graph);
    stopTimer(stopwatch);
    double elapsed_time = getElapsedTime(stopwatch);
    printf("elapsed_time: %f\n", elapsed_time);

    /* STEP 3: CREATE OUTPUT */
    char file_index = input_filename[0];  // filenames are like 1_sample_input
    char output_filename[200] = "X_experimental_output_serial.txt";
    output_filename[0] = file_index;
    create_output(output_filename, graph);

    printf("End of serial_FW\n");
}