#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


// matrix defintions

matrix make_matrix(int rows, int cols)
{
	// Create a matrix on heap.
	matrix m;
	m.cols = cols;
	m.rows = rows;
	m.data = calloc(m.rows, sizeof(* double));
	int i ;
	for(i = 0; i < m.rows; i++)
	{
		m.data[i] = calloc(m.cols, sizeof(double));
	}

	return m;
}


matrix copy_matrix(matrix originalMatrix)
{
	m = make_matrix(originalMatrix.rows, originalMatrix.cols);
	// Copy the data matrix.
	int i,j;
	for(int i = 0; i < m.rows; i++)
	{
		for(int j =0; j < m.cols; j++)
		{
			m.data[i][j] = originalMatrix[i][j];
		}
	}

	return m;
}

void print_matrix(matrix originalMatrix)
{
	int i,j;

	printf("The number of rows present are : %d \n", originalMatrix.rows)
	printf("The number of cols present are : %d \n", originalMatrix.cols)

	for(int i = 0; i < originalMatrix.rows ; i++)
	{
		for(int j = 0; j < originalMatrix.cols; j++)
		{
			printf("%f \t", originalMatrix.data[i][j]);
		}
	}
}


void free_matrix(matrix m)
{
	// FRee everything present in matrix m 
	int i;
	if(m.data)
	{
		for(int i = 0; i < m.rows; i++)
		{
			free(m.data[i]);
		}
	}
	// FInally free the m.data pointer 
	free(m.data);

}

matrix axpy_matrix(double a, matrix x, matrix y)
{
	// axpy stands for a*x + y
	matrix x = scale_matrix(a, x);
	int i,j;
	// Check if the # rows and #cols of both matrices match up
	assert(x.cols == y.cols);
	assert(x.rows == y.rows);

	// If true 
	// Work starts
	for(i = 0; i < x.rows; i++)
	{
		for(j = 0; j < x.cols; j++)
		{
			x.data[i][j] += y.data[i][j]; 
		}
	}

return x;
}

matrix scale_matrix(double a, matrix x)
{
	int i, j;
	for(i = 0; i < x.rows; i++)
	{
		for(j = 0; j < x.cols; j++)
		{
			x.data[i][j] *= a; 
		}
	}

	return x;
}


// SOME IMPORTANT MATRIX RELATED METHODS
// 1. Matrix multiplication
// 2. Matrix element wise multiplication
// 3. Matrix transpose
// 4. Some random initialisation methods
// 4.1 -> Random initialisation
// 4.2 -> Random Normal Initialisation

// Lets work them out

matrix matrix_mult_matrix(matrix a, matrix b)
{
	// Multiplication is just the dot product of all the row vectors in the first matrix and 
	// the column vector in the second matrix

	// Multiplication works in certain criteria only 
	// THat criteria is that the # cols in matrix a == # rows in matrix b
	//(n1, n2)* (n2, n3) --> Possible
	assert(a.cols == b.rows);
	int i,j,k;

	matrix m = make_matrix(a.rows, b.cols);

	for(i = 0; i < m.rows; i++)
	{
		for(j = 0; j < m.cols; j++)
		{
			for(k = 0; k < a.cols; k++)
			{
				m.data[i][j] = a.data[i][k]*b.data[k][j];
			}
		}
	}

	return m;
} 

matrix matrix_elmult_matrix(matrix a, matrix b)
{
	// Check the dimensions first
	assert(a.cols == b.cols);
	assert(a.rows == a.rows);

	// Lets do the multiplication in-place
	int i,j;
	for(i = 0; i < a.rows; i++)
	{
		for(j = 0; j < a.cols; j++)
		{
			a.data[i][j] *= b.data[i][j]; 
		}
	}
}

matrix transpose_matrix(matrix x)
{
	// Change the rows to cols
	// Change the data matrix also
	matrix m = make_matrix(x.cols, x.rows);
	int i, j;
	for(i = 0; i < m.cols; i++)
	{
		for(j = 0; j < m.rows; j++)
		{
			m.data[i][j] = x.data[j][i];  
		}
	} 
}

// Random Methods that I am copying from Joseph Redmon

// NORMAL RANDOM MATRIX DEFINTION
double box_muller_normal_random(double m, double s)   /* normal random variate generator */
{                       /* mean m, standard deviation s */
    double x1, x2, w, _y1;
    double y2;
    int use_last = 0;

    if (use_last)               /* use value from previous call */
    {
        _y1 = y2;
        use_last = 0;
    }
    else
    {
        do {
            x1 = 2.0 * drand48() - 1.0;
            x2 = 2.0 * drand48() - 1.0;
            w = x1 * x1 + x2 * x2;
        } while ( w >= 1.0 );

        w = sqrt( (-2.0 * log( w ) ) / w );
        _y1 = x1 * w;
        y2 = x2 * w;
        use_last = 1;
    }

        double result = ( m + _y1 * s );

    return result;
}

matrix normal_random_matrix(int rows, int cols, double m, double s)
{
    matrix mat = make_matrix(rows, cols);
    
    int i, j;
    for(i = 0; i < rows; ++i){
        for(j = 0; j < cols; ++j){
            mat.data[i][j] =  (double) box_muller_normal_random(m , s);    
        }
    }
    return mat;
}


// RANDOM MATRIX DEFINITION
matrix random_matrix(int rows, int cols, double s)
{
    matrix m = make_matrix(rows, cols);
    int i, j;
    for(i = 0; i < rows; ++i){
        for(j = 0; j < cols; ++j){
            m.data[i][j] = 2*s*(rand()%1000/1000.0) - s;    
        }
    }
    return m;
}