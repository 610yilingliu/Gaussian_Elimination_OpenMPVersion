#include "heads.h"

void calculate(int nthreads) {
    if (nthreads == 1) {
        for (int i = SIZE - 1; i > -1; i--) {
            // case matrix[i][i] == 0 is already rejected while eliminating
            double curans = (double)vec[i][0] / matrix[i][i];
            answers[i][0] = curans;
            for (int j = i - 1; j > -1; j--) {
                double divider = (double)matrix[j][i] / matrix[i][i];
                vec[j][0] -= vec[i][0] * divider;
            }
        }
    }
    else {
        for (int i = SIZE - 1; i > -1; i--) {
            // case matrix[i][i] == 0 is already rejected while eliminating
            double curans = (double)vec[i][0] / matrix[i][i];
            answers[i][0] = curans;
#pragma omp parallel for num_threads(nthreads)
            for (int j = i - 1; j > -1; j--) {
                double divider = (double)matrix[j][i] / matrix[i][i];
                vec[j][0] -= vec[i][0] * divider;
            }
        }
    }
}

void exporting(double* arr_2d, int rownum, int colnum, char* fname) {
    // save in csv mode, split by ','
    // 2d array visiting solution: https://stackoverflow.com/questions/16724368/how-to-pass-a-2d-array-by-pointer-in-c
    FILE* fp = NULL;
    fp = fopen(fname, "w");
    double* p = (double*)arr_2d;
    for (int i = 0; i < rownum; i++) {
        for (int j = 0; j < colnum; j++) {
            double ele = p[i * colnum + j];
            fprintf(fp, "%f,", ele);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

int main(int argc, char* argv[]) {
    printf("Start Processing......\n");
    printf("Matrix size: %i * %i\n", SIZE, SIZE);
    start_t = clock();
    void *matrix_pointer = matrix;
    void *vector_pointer = vec;
    void *answer_pointer = answers;
    if (argc == 1) {
        matrix_generator(1);
        exporting(matrix_pointer, SIZE, SIZE, "matrix.csv");
        vector_generator(1);
        exporting(vector_pointer, SIZE, 1, "vector.csv");
        for (int j = 0; j < SIZE; j++) {
            int r = find_maxrow(1, j);
            swap(r, j);
        }
        exporting(matrix_pointer, SIZE, SIZE, "converted_matrix.csv");
        exporting(vector_pointer, SIZE, 1, "converted_vector.csv");
        eliminate_all(1);
        exporting(matrix_pointer, SIZE, SIZE, "eliminated_matrix.csv");
        exporting(vector_pointer, SIZE, 1, "eliminated_vector.csv");
        calculate(1);
        exporting(answer_pointer, SIZE, 1, "answer.csv");
    }
    else {
        int nthreads = 0;
        if (argc == 3 && (argv[1][0] == '-' && argv[1][1] == 'p')){
            
            for(int i = 0; i < strlen(argv[2]); i++){
                if (argv[2][i] < '0' || argv[2][i] > '9') {
                    printf("Invalid argument!\n");
                    printf("%s\n", argv[2][i]);
                    printf("%i\n", strlen(argv[2]));
                    exit(EXIT_FAILURE);
                }
            }
            nthreads = atoi(argv[2]);
            if(nthreads == 0){
                printf("Invalid argument!\n");
                exit(EXIT_FAILURE);
            }
            printf("You are using %i threads\n", nthreads);
        
        }
        else{
            printf("Invalid argument!\n");
            exit(EXIT_FAILURE);
        }
        matrix_generator(nthreads);
        exporting(matrix_pointer, SIZE, SIZE, "matrix.csv");
        vector_generator(nthreads);
        exporting(vector_pointer, SIZE, 1, "vector.csv");
        for (int j = 0; j < SIZE; j++) {
            int r = find_maxrow(nthreads, j);
            swap(r, j);
        }
        exporting(matrix_pointer, SIZE, SIZE, "converted_matrix.csv");
        exporting(vector_pointer, SIZE, 1, "converted_vector.csv");
        eliminate_all(nthreads);
        exporting(matrix_pointer, SIZE, SIZE, "eliminated_matrix.csv");
        exporting(vector_pointer, SIZE, 1, "eliminated_vector.csv");
        calculate(nthreads);
        exporting(answer_pointer, SIZE, 1, "answer.csv");
    }
    finish_t = clock();
    total_t = (double)(finish_t - start_t) / CLOCKS_PER_SEC;
    printf("Spent time:%f \n",total_t);
    printf("Finished, please check answer.csv to see what the answer is\n");
    return 0;
}