// Defines the data batch

#ifndef DATA_H
#define DATA_H
#include "../matrix_methods/matrix.h"
#include "list.h"
#include "stdio.h"

typedef struct 
{	
	matrix X;          // X represents the input to any model
	matrix y;			// Y represents the output of any model
	
}data;

// METHODS USEFUL
data random_batch(data d, int n);
list *get_lines(char *filename);
data load_classification_data(char *images, char *label_file, int bias);
char *fgetline(FILE *fp);
void free_data(data d);

#endif