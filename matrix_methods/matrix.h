// THis file contains all the methods related to just matrix calculations.
// Also how to define a matrix in memory.

#ifndef MATRIX_H
#define MATRIX_H 



// Matrix definition
typedef struct 
{
	int rows;
	int cols;
	double ** data;
}matrix;


// Methods to take in consideration
matrix make_matrix(int rows, int cols);
matrix copy_matrix(matrix originalMatrix);
void print_matrix(matrix originalMatrix);
void free_matrix(matrix m);
matrix axpy_matrix(double a, matrix x, matrix y)



matrix scale_matrix(double s, matrix A);
matrix matrix_mult_matrix(matrix A, matrix B);        // Multiplies two matrices
matrix matrix_elmult_matrix(matrix a, matrix b);		// Element wise multiplication of two matrices                          // Prints matrix
matrix random_matrix(int rows, int cols, double s);
matrix transpose_matrix(matrix m);
double box_muller_normal_random(double m, double s);
matrix normal_random_matrix(int, int, double, double);

#endif