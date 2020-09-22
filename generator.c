#include "heads.h"

void matrix_generator(int nthreads) {
    if (nthreads == 1) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                matrix[i][j] = (double)(rand() % (RANGE * 2) - RANGE) / SCALE;
            }
        }
    }
    else {
#pragma omp parallel for num_threads(nthreads)
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                matrix[i][j] = (double)(rand() % (RANGE * 2) - RANGE) / SCALE;
            }
        }
    }
}

void vector_generator(int nthreads) {
    if (nthreads == 1) {
        for (int i = 0; i < SIZE; i++) {
            vec[i][0] = (double)(rand() % (RANGE * 2) - RANGE) / SCALE;
        }
    }
    else {
#pragma omp parallel for num_threads(nthreads)
        for (int i = 0; i < SIZE; i++) {
            vec[i][0] = (double)(rand() % (RANGE * 2) - RANGE) / SCALE;
        }
    }
}