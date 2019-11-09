# This file creates and compuets the norms for all the layers present in a model

# Import the uwimg library
from uwimg import * 

from model_definition import softmax_model
from norm_calculation import get_data
# FIRST LOAD THE DATA
train_data = get_data()[0]
test_data = get_data()[1]

# Create a model
Model = softmax_model(train_data.X.cols, train_data.y.cols)
# Now iterate through the model layers
def iterate_over(model, iters):
	for iter in range(iters):
		calculate_G1(Model, train_data.X, train_data)
		print_matrix(Model.G1)
		psi = create_psi(train_data.X, train_data.y, 0.1)
		calculate_G2(Model, train.X, train_data, psi)
		# Now calculate the running average of Psi for all the layers in the model
		for layers in Model.n:
			norm1 = 0
			psi = running_average(psi, gradient1, gradient2)
			norm1 = calculate_delta_norm(norm1 ,psi)

	
if __name__ == "__main__":
	iterate_over(Model, 10)
