#include "fw_parallel_module.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

// note, I very closely followed the sample code provided here: https://randu.org/tutorials/threads/

typedef struct _thread_args_t {
  int start_row;
  int end_row;
  graph_t* graph;
} thread_args_t;


pthread_barrier_t barrier;

/* this is the function that each thread executes */
void *thr_func(void *input) {
    thread_args_t *args = (thread_args_t *) input;
    int start_row = args->start_row;
    int end_row = args->end_row;
    graph_t* graph = args->graph;

    // perform work on the rows that this thread was assigned to
    for (int k = 0; k < graph->N; k++) {
        for (int i = start_row; end_row; i++) {
            for (int j = 0; j < graph->N; j++) {    
                if (graph->dist[i][j] > graph->dist[i][k] + graph->dist[k][j]) {
                    graph->dist[i][j] = graph->dist[i][k] + graph->dist[k][j];
                }
            }
        }
        pthread_barrier_wait(&barrier); // wait for all threads to finish a given k
    }

    printf("thread function has completed\n");
    pthread_exit(NULL);
}


int run_fw_parallel(graph_t* graph, int num_threads) {
    printf("start of run_fw_parallel\n");
    int num_threads_to_spawn = (graph->N <= num_threads) ? graph->N : num_threads;
    int rows_per_thread = graph->N / num_threads_to_spawn;

    printf("num_threads_to_spawn: %d\n", num_threads_to_spawn);
    printf("rows_per_thread: %d\n", rows_per_thread);

    // first, create threads here
    thread_args_t thr_args[num_threads_to_spawn];
    pthread_t thread_ids[num_threads_to_spawn]; // so we can keep track of our threads

    pthread_barrier_init(&barrier, NULL, num_threads_to_spawn);
    printf("now spawning threads...\n");
    for (int i = 0; i < num_threads_to_spawn; i++) {
        thr_args[i].start_row = i * rows_per_thread;
        thr_args[i].end_row = (i + 1) * rows_per_thread;
        thr_args[i].graph = graph;

        printf("thr_args[i].start_row: %d\n", thr_args[i].start_row);

        if (pthread_create(&(thread_ids[i]), NULL, &thr_func, (void *) &thr_args[i]) != 0) {
            printf("error creating thread!\n");
            return 1;
        }
    }
    pthread_barrier_destroy(&barrier);

    printf("now joining threads...\n");
    // join the threads back together
    for (int i = 0; i < num_threads_to_spawn; i++) {
        if (pthread_join(thread_ids[i], NULL) != 0) {
            printf("error joining thread!\n");
            return 1;
        }
    }
    
    return EXIT_SUCCESS;
}

