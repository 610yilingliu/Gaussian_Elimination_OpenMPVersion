#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <stdbool.h>
#include <string.h>

// The size of the matrix
#define SIZE 3
// the random number will be generated in range [-RANGE, RANGE]
#define RANGE 3
// divide the generated number, converted it into float. For example, if range = 10 and SCALE = 10, random number will between [-, 1]
#define SCALE 1

clock_t start_t,finish_t;
double total_t;

float matrix[SIZE][SIZE];
float vec[SIZE][1];
float answers[SIZE][1];
// generate matrix with random number. input: number of thread
extern void matrix_generator(int);
extern void vector_generator(int);
// find row with largest number in specific column. input: number of threads, column index. If the maximun abs in that row is 0, exit.
extern int find_maxrow(int, int);
// 2 rows to exchange. input: row1, row2
extern void swap(int, int);
// eliminate matrix with given row. input: number of threads, given row index to use, column for elimination
extern void eliminate(int, int, int);
// input: number of threads
extern void eliminate_all(int);
// input: nthread
extern void calculate(int);