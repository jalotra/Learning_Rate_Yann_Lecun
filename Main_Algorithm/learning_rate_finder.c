#include "../matrix_methods/matrix.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

#define loop_for(i, n) for(int i = 0; i < n ; i++)


// LETS START WITH THE ALGORITHM
// GLOBAL VARIABLES
double alpha = 0.01;
double gammaa = 0.01;

// Returns the L2 norm
double calculate_norm(matrix x)
{
	assert(x.rows >= 1 && x.cols >= 1);
	double ans = 0;  
	loop_for(i, x.rows)
	{
		loop_for(j, x.cols)
		{
			ans += (x.data[i][i])*(x.data[i][j]);
		}
	}

	return sqrt(ans) ;
}

// Creates a Random Vector 
// The reason for this vector to be random so that we dont have a vector which is orthogonal to the hessian matrix
matrix create_psi(int rows, int cols, double s)
{
	return random_matrix(rows, cols, s);
}


// Calculates the running average of the vector psi
matrix running_average(matrix psi, matrix gradient1, matrix gradient2)
{
	// Scale with 1 - gammaa
	psi = scale_matrix((1.0 - gammaa), psi);

	// change g1 to be the differnece in the gradients 
	gradient1 = axpy_matrix(-1, gradient1, gradient2);

	// Scale g1 with gammaa/alpha
	// assert(gammaa/alpha != nan);
	gradient1 = scale_matrix(gammaa/alpha, gradient1);

	// add psi and gradient
	return axpy_matrix(1, psi, gradient1); 

}


// Number of iterations
void iterate_over(int iters, matrix psi, matrix gradient1, matrix gradient2)
{
	double norm1 = 0;
	loop_for(i, iters)
	{
		psi = running_average(psi, gradient1, gradient2);
		double norm2 = calculate_norm(psi);
		printf("%f The norm of psi for this layer is : \n",calculate_norm(psi));

		// IF NORM OF PSI IS LESS THAN 10% ERROR THEN BREAK 
		// WE HAVE GOT THE MAX EIGEN VALUE 
		if((norm2 - norm1) / norm1 < 0.1)
		{
			break;
		} 
		norm1 = norm2;
	}
}




int main(int argc, char const *argv[])
{
	matrix m = make_matrix(3,3);
	print_matrix(m);
	return 0;
}