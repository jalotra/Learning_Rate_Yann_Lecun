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
// 1. IMPORTANT UPDATE THE WEIGHTS OF LAYER BY SOME PSI1 
// 2. THEN FORWARD PROPOGATE THROUGH THE MODEL 
// 3. ALSO BACKPROPOGATE BACKWARDS 
// 4. SAVE THE GRADIENT MATRIX CALCULATED THIS TIME IN A NEW MATRIX G2
// THE LAST TASK STILL REMAINS AND THAT IS TO MAKE SURE THAT AFTER THIS WE CHANGE THE WEIGHTS 
// TO THEIR ORIGINAL VALUE.     