#include "matrix_methods/matrix.h"
#include "NeuralNetworkBackPropogation/layer.h"

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


// Calculates the G1 matrix
void calculate_gradient1(model M, matrix X, data b) 
{
	// Forward Propogate through the model
	matrix X = forward_model(M, X);

	// Lets calculate the loss at the last layer
	matrix delta = Last_Layer_Loss_Cross_Entropy(b, p); // partial derivative of loss dL/dy
	// Now backpropogate Backwards
	backward_model(M, delta);

	// Now Backward model in itself calls the backward_layer
	// FUnction that saves the derivative wrt weights in dw 
	// Matrix 
	// My job is just to copy the dw matrix in the matrix G1
	for(int i = 0; i < M.n; i++)
	{
		// Free the matrix G1 first
		free_matrix(l->G1);
		l->G1 = l->dw;
	}

	return;

}

//calculates the G2 matrix
void calculate_gradient2(model M, matrix X, data b, matrix psi)
{
	// Now the task is first to update the weights 
	// Of all the layers by some psi
	for(int i = 0; i < M.n; i++)
	{
		// Save curent weights in l->v for use later
		free_matrix(M.layers+i->v);
		l->v = l->w;

		// FIrst free the matrix l->w
		free_matrix(M.layers+i->w);


		l->w = scale_matrix(alpha, psi)
	}

	// Now Forward Propogate 
	forward_model(M, X);

	// Calculate  the loss at the last layer
	matrix delta = Last_Layer_Loss_Cross_Entropy(b, p); // partial derivative of loss dL/dy

	// BackPropogate the Loss
	backward_model(M, delta);

	// Now the dw contains the matrix G2
	for(int i = 0; i < M.n; i++)
	{
		// Free the matrix G2
		free_matrix(G2);
		l->G2 = l->dw;
	}

	// Change the current weights with past weights
	l->w = l->v;

	return;
}

