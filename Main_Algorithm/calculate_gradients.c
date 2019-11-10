#include "../matrix_methods/matrix.h"
#include "../NeuralNetworkBackPropogation/layer.h"
// Include the data header file
#include "../input_data/data.h"
#include "main_algo.h"

#include <assert.h>
#include <stdio.h>
#include <math.h>


// Now that I have created the defintion of a Neural Network.
// The main task remains and that is to store the gradeints G1 AND G2.
// HOW is it to be done?
// G1 is calculated in this way:
// FORWARD PROP THROUGH THE MODEL AND BACKPROPOGATE IN THE REVERSE DIRECTION
// CALCULATE THE DERIVATIVE WRT WEIGHTS AND MAKE THIS MATRIX AS G1

// How to calculate the matrix G2?
// 1. UPDATE THE WEIGHTS OF EVERY LAYER BY SOME PSI1 
// 2. THEN FORWARD PROPOGATE THROUGH THE MODEL 
// 3. ALSO BACKPROPOGATE BACKWARDS 
// 4. SAVE THE GRADIENT MATRIX CALCULATED THIS TIME IN A NEW MATRIX G2
// THE LAST TASK STILL REMAINS AND THAT IS TO MAKE SURE THAT AFTER THIS WE CHANGE THE WEIGHTS 
// TO THEIR ORIGINAL VALUE.    

const double const1_alpha = 0.01;
const double const2_gamma = 0.01;

// Calculates the G1 matrix
void calculate_gradient1(model M, data d, int batchsize) 
{
	data b = random_batch(d, batchsize);
	// printf("%s\n", "WORKINGS");
	// Forward Propogate through the model
	matrix out  = forward_model(M, b.X);
	// printf("ROWS : %d  COLS : %d", out.rows, out.cols);


	// Lets calculate the loss at the last layer
	matrix delta = sub_matrix(b.y, out); // partial derivative of loss dL/dy

	// print_matrix(delta);
	// Now backpropogate Backwards
	backward_model(M, delta);

	// Now Backward model in itself calls the backward_layer
	// FUnction that saves the derivative wrt weights in dw 
	// Matrix 
	// My job is just to copy the dw matrix in the matrix G1
	// for(int i = 0; i < M.n; i++)
	// {
	// 	// Free the matrix G1 first
	// 	free_matrix((M.layers+i)->G1);
	// 	(M.layers+i)->G1 = (M.layers+i)->dw;
	// }

	// FREE THE OUTPUT MATRIX
	free_matrix(out);

	return;

}

//calculates the G2 matrix
void calculate_gradient2(model M, data d, matrix psi, int batchsize)
{
	data b = random_batch(d, batchsize);
	// Now the task is first to update the weights 
	// Of all the layers by some psi
	for(int i = 0; i < M.n; i++)
	{
		// Save curent weights in l->v for use later
		free_matrix((M.layers+i)->v);
		(M.layers+i)->v = (M.layers+i)->w;

		// FIrst free the matrix l->w
		free_matrix((M.layers+i)->w);


		(M.layers+i)->w = scale_matrix(const1_alpha, normalise_psi(psi));
	}

	// Now Forward Propogate 
	matrix output = forward_model(M, b.X);

	// Calculate  the loss at the last layer
	matrix delta = Last_Layer_Loss_Cross_Entropy(b, output); // partial derivative of loss dL/dy

	// BackPropogate the Loss
	backward_model(M, delta);

	// Now the dw contains the matrix G2
	for(int i = 0; i < M.n; i++)
	{
		// Free the matrix G2
		free_matrix((M.layers+i)->G2);
		(M.layers+i)->G2 = (M.layers+i)->dw;
	}

	// Change the current weights with past weights
	for(int i = 0; i < M.n; i++)
	{
		(M.layers+i)->w = (M.layers+i)->v;
	}
	// l->w = l->v;

	// FRee the output matrix
	free_matrix(output);

	return;
}

