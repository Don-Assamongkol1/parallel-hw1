#ifndef TYPES_H
#define TYPES_H

typedef struct {
    int N;
    int **adjacency_matrix;
    int **dist;  // dist and adjacency_matrix will point to the same 2D int array,
                 // I just find it conceptually easier to think of the two in separate steps
                 // adj for reading in initial input, dist for running FW
} graph_t;

#define INFINITY 1023001
#define MAX_LINE_LENGTH 100000
#define MAX_INT_LENGTH 1000
#define MAX_STRING_LENGTH 100

#endif 