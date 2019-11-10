// This file declares what all has to be in a layer of a NEURAL NETWOK.


#ifndef LAYER_H
#define LAYER_H
#include "../input_data/data.h"


// LETS DECLARES THE DIFFERENT ACTIVATION FUNCTIONS THAT I WILL BE IMPLEMENTING
// I HAVE THOUGHT OF IMPLEMENTING TWO ACTIVATION FUNCTIONS
// 1. RELU
// 2. LRELU

typedef enum {
	RELU, LRELU, SOFTMAX
}ACTIVATION ;


// A LAYER WILL CONTAINS THESE MANY DATA MEMBERS 
typedef struct{
	matrix in;
	matrix out;
	matrix dw;            // Current weight gradient  
 	matrix w;             // CURRENT WEIGHTS
 	matrix v;             // PAST weights
	ACTIVATION activation;

	matrix G1;
	matrix G2;
} layer;



// LETS DEFINE THE MODEL
typedef struct 
{	
	int n;
	layer *layers;      // A pointer to all the layers that are represented by an array
	
}model;


// Lets declare all the methods 
void activate_matrix(matrix x, ACTIVATION a);
void gradient_matrix(matrix m, ACTIVATION a, matrix delta);
matrix  forward_layer(layer *l, matrix in);
matrix backward_layer(layer *l, matrix delta);
layer make_layer(int input, int output, ACTIVATION activation);
matrix forward_model(model M, matrix X);
void backward_model(model M, matrix delta);
double cross_entropy_loss(matrix y, matrix p);
matrix Last_Layer_Loss_Cross_Entropy(data b, matrix p);


#endif