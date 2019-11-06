// This file declares what all has to be in a layer of a NEURAL NETWOK.


#ifndef LAYER_H
#define LAYER_H


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


// LETS DECLARES THE DIFFERENT ACTIVATION FUNCTIONS THAT I WILL BE IMPLEMENTING
// I HAVE THOUGHT OF IMPLEMENTING TWO ACTIVATION FUNCTIONS
// 1. RELU
// 2. LRELU

typedef enum {
	RELU, LRELU
}ACTIVATION ;


// LETS DEFINE THE MODEL
typedef struct 
{	
	int n;
	layer *layers;      // A pointer to all the layers that are represented by an array
	
};























#endif