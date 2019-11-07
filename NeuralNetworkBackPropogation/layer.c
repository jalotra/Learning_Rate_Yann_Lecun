#include "layer.h"
#include "matrix_methods/matrix.h"
#include "main_algo.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double LRELU_CONST = 0.1;

// ACTIVATE MATRIX 
// INPUT MATRIX x 
// PROCESS -> Activates the matrix x with the ACTIVATION functions at the disposal 
// ACTIVATION FUNCTIONS AVAILABLE -> RELU, LRELU, SOFTMAX


void activate_matrix(matrix x, ACTIVATION a)
{
	// DEFINE A VARIBALE FOR SOFTMAX 
	if(a == SOFTMAX) double sum = 0;
	// Define RELU activation Function
	for(int i = 0; i < x.rows; i++)
	{
		for(int j = 0; j < x.cols; j++)
		{
			double * value = &x.data[i][j];

			// Defining the Rectified Linear Unit
			if(a == RELU)
			{
				if(*value < 0)
				{
					*value = 0;
				}
			}

			// Defining the Linear Rectified Unit
			if(a == LRELU)
			{
				if(*value < 0)
				{
					*value *= LRELU_CONST;
				}
			}

			// Defining the Softmax Activation FUnction
			if( a == SOFTMAX)
			{
				sum += *value;
			}

		}

		// Normalise the values
		if(a == SOFTMAX)
		{
			for(int i = 0; i < x.cols; i++)
			{
				x.data[i][j] /= sum; 
			}
		}	
	}

	// Free the value pointer
	free(value);
} 


// COMPUTING GRADIENT 
// LETS SAY WE HAVE A LOSS MATRIX COMING IN FROM THE OUTPUT OF THE LAYER 
// THEN WE WANT TO MULTIPLY IT BY THE 
// DERIVATIVE OF THE ACTIVATION FUNCTION
// FOR MORE DETAILS CHECK THIS LINK -> 

// matrix m: an activated layer output
// ACTIVATION a: activation function for a layer
// matrix d: delta of Loss wrt to output of the layer before activation gradient

// KEEP IN MIND THAT BOTH THE MATRICES i.e MATRIX m and MATRIX d are of the same dimensions.
void gradient_matrix(matrix m, matrix delta, ACTIVATION a)
{
	for(int i = 0; i < m.rows; i++)
	{
		for(int j = 0; j < m.cols; j++)
		{
			double *value = &m.data[i][j];
			if(a == SOFTMAX)
			{
				// Since I will be using the softmax layer only at the output loss
				// Along with the Cross-ENtropy LOss
				// TO avoid the numerical instabilisation
				// We combine both these steps
				            	// Check this link : https://math.stackexchange.com/questions/945871/derivative-of-softmax-loss-function?utm_medium=organic&utm_source=google_rich_qa&utm_campaign=google_rich_qa
				d.data[i][j] *= 1;
			}
			if(a == RELU)
			{
				if(*value < 0)
				{
					d.data[i][j] = 0;
				}
			}
			if(a == LRELU)
			{
				if(*value < 0)
				{
					d.data[i][j] *=  LRELU_CONST;
				}
			}
		}
	}

	// FREE the value pointer
	free(value);
}


// LETS DEFINE THE FORWARD PROPAGATION 
// THROUGH THE LAYER 
// layer *l : Pointer to the layer
// matrix in : Input to the layer 
// return : the output from the layer
void forward_layer(ayer *l, matrix in)
{
	l->in = in;

	// Check if the in cols == l->weights
	assert(in.cols == l->w.rows);

	// Multiply or do XW
	matrix out = matrix_mult_matrix(in, l->w);

	// Activate the produbt
	activate_matrix(out, l->activation);

	// Free the old matrix before writing out to l->out
	free_matrix(l->out);

	// Write out to l->out
	l->out = out;


	return out;
}

// LETS DEFINE THE BACKWARD PROGATION
matrix backward_layer(layer *l, matrix delta)
{
    // 1.4.1
    // delta is dL/dy
    // TODO: modify it in place to be dL/d(xw)
    // dL/d(xw) = dL/dy * dy/d(xw)
         // = dL/dy * df(xw)/d(xw)
         // = dL/dy * f'(xw)

	// The output of the current layer is already present in the l->out variable. 
	gradient_matrix(l->out, l->activation, delta);



    // 1.4.2
    // DERIVATIVE WITH RESPECT TO WEIGHTS
    // TODO: then calculate dL/dw and save it in l->dw
    free_matrix(l->dw);
    // matrix dw = make_matrix(l->w.rows, l->w.cols); // replace this
    // dL/dw = dL/d(xw) * d(xw)/dw
     //  = dL/d(xw) * x
    // Take transpose of the input layer and multiply it with the dl/d(x*w)

    // THIS DW CONTAINS THE GRADIENT THAT I AM INTERESTED IN
    matrix dw = matrix_mult_matrix(transpose_matrix(l->in), delta);
    l->dw = dw;

    
    // 1.4.3
    // TODO: finally, calculate dL/dx and return it
    // w = transpose_matrix(w);
    matrix dx = matrix_mult_matrix(delta, transpose_matrix(l->w));

    return dx;
}


// I AM NOT INTERESTED IN UPDATING THE WEIGHTS 
// Make a new layer for our model
// int input: number of inputs to the layer
// int output: number of outputs from the layer
// ACTIVATION activation: the activation function to use
layer make_layer(int input, int output, ACTIVATION activation)
{
    layer l;
    l.in  = make_matrix(1,1);
    l.out = make_matrix(1,1);
    //Weight Initialisation Case 1
    // Randomly Distributed
    // Works good with cross entropy
    l.w   = random_matrix(input, output, sqrt(2./input));

    // Weight Initialisation Type 2 
    // Normal Random
    // m - > mean
    // s - > std
    // Works good with MSE
    //l.w = normal_random_matrix(input, output, 0.1, 10);
    l.dw  = make_matrix(input, output);
    l.activation = activation;
    return l;
}


// RUNS MODEL FORWARD
matrix forward_model(model M, matrix X)
{
	int i;
	for(int i = 0; i < M.n; i++)
	{
		X = forward_layer(M.layers+i, X);
	}

	// RETURN THE OUTPUT OF THE MODEL M
	return X;
}

// RUNS MODEL BACKWARDS
void backward_model(model M, matrix delta)
{
	// delta -> the last layer loss
	matrix d = copy_matrix(delta);
    int i;
    for(i = m.n-1; i >= 0; --i){
        matrix prev = backward_layer(m.layers + i, d);
        free_matrix(d);
        d = prev;
    }
    free_matrix(d);
}


// CROSS ENTROPY LOSS
// Calculate the cross-entropy loss for a set of predictions
// matrix y: the correct values
// matrix p: the predictions
// returns: average cross-entropy loss over data points, 1/n Σ(-ylog(p))
double cross_entropy_loss(matrix y, matrix p)
{
    int i, j;
    double sum = 0;
    for(i = 0; i < y.rows; ++i){
        for(j = 0; j < y.cols; ++j){
            sum += -y.data[i][j]*log(p.data[i][j]);
        }
    }
    return sum/y.rows;
}


matrix Last_Layer_Loss_Cross_Entropy(data b, matrix p)
{
    matrix dL = axpy_matrix(-1, p, b.y);
    return dL;
}





