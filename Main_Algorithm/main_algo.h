#ifndef MAIN_ALGO_H
#define MAIN_ALGO_H

// Lets define all the function signatures present

// FIRST FOR learning_rate_finder.c
double calculate_norm(matrix);
matrix create_psi(int, int, double);
matrix running_average(matrix, matrix, matrix);
void calculate_delta_norm(double , matrix, matrix, matrix );

// NOW FOR calculate_gradients.c
void calculate_gradient1(model, matrix, matrix);
void calculate_gradient2(model, matrix, matrix, double);



#endif 