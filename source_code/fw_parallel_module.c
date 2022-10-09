#include "fw_parallel_module.h"
#include <pthread.h>
#include <stdlib.h>

// note, I very closely followed the sample code provided here: https://randu.org/tutorials/threads/

typedef struct _thread_data_t {
  int start_row;
  int end_row;
  graph_t graph;
} thread_data_t;


/* this is the function that each thread executes */
void *thr_func(void *arg) {
    thread_data_t *data = (thread_data_t *) arg;

    // perform work on the rows that this thread was assigned to
    for (int i = data->start_row; data->end_row; i++) {
        for (int j = 0; j < graph->N; j++) {    
            if (graph->dist[i][j] > graph->dist[i][k] + graph->dist[k][j]) {
                    graph->dist[i][j] = graph->dist[i][k] + graph->dist[k][j];
            }
        }
    }
    
    pthread_exit(NULL);
}


void run_fw_parallel(graph_t* graph, int num_threads) {
    int num_threads_to_spawn = (graph->N <= num_threads) ? graph->N : num_threads;
    int rows_per_thread = graph->N / num_threads_to_spawn;

    // first, create threads here
    thread_data_t thr_args[num_threads_to_spawn];
    pthread_t thread_ids[num_threads_to_spawn]; // so we can keep track of our threads


    // now, get threads executing on each k

    for (int k = 0; k < graph->N; k++) {
        
        // create argument we will supply to thread
        int start_row = rows_per_thread * k;
        int end_row = rows_per_thread * (k + 1); // up to but not including
        thr_args[k].start_row = start_row;
        thr_args[k].end_row = end_row;
        thr_args[k].graph = graph;

        if ((rc = pthread_create(&thread_ids[i], NULL, thr_func, &thr_args[i]))) {
            fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
            return EXIT_FAILURE;
        }


        // create threads, store their ids in the array so we have a reference to them


        // barrier - block until all threads complete this particular k
    }


    // join - block until all threads complete
    for (i = 0; i < num_threads_to_spawn; i++) {
        pthread_join(thread_ids[i], NULL);
    }
    return EXIT_SUCCESS;
}





// create threads + store references to them 

// 