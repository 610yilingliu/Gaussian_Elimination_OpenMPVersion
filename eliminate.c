#include "heads.h"

void eliminate(int base, int target, int col) {
    float base_num = matrix[base][col];
    float multi = (float)matrix[target][col] / base_num;
    // start from col to reduce time complexity.(item before col is already become 0) 
    if(multi != 0){
        for (int i = col; i < SIZE; i++) {
            // function discussed in readme.md
            matrix[target][i] -= matrix[base][i] * multi;
        }
        vec[target][0] -= vec[base][0] * multi;
    }
}

void eliminate_all(int nthreads) {
    if (nthreads == 1) {
        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = i + 1; j < SIZE; j++) {
                eliminate(i, j, i);
            }
        }
    }
    else {
        omp_set_num_threads(nthreads);
        int i, j;
#pragma omp parallel for private(j)
        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = i + 1; j < SIZE; j++) {
                eliminate(i, j, i);
            }
        }
    }
}