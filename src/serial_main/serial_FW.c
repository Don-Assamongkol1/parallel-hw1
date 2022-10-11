#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "fw_serial_module.h"
#include "input_module.h"
#include "output_module.h"
#include "stopwatch.h"
#include "types.h"

// compile using: gcc -Wall -Werror -O3 serial_FW.c input_module.c output_module.c fw_serial_module.c stopwatch.c -o serial_FW
// run using: ./serial_FW 1_sample_input.txt 128

int main(int argc, char **argv) {
    /* Parse command line args */
    if (argc != 3) {
        /* EXAMPLE: ./customer_software_serial sample_input.txt 128 */
        printf("ERROR!: expected two arguments: thread count and input filename\n");
        exit(1);
    }

    char *input_filename = argv[1];
    int num_threads = 1;

    /* STEP 1: PROCESS INPUT */
    graph_t *graph = calloc(1, sizeof(graph_t));
    process_input(input_filename, graph);

    /* STEP 2: RUN FW */
    graph->dist = graph->adjacency_matrix;

    run_fw_serial(graph);

    /* STEP 3: CREATE OUTPUT */
    create_output(false, num_threads, graph);
}