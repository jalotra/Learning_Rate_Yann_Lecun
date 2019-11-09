# This file creates and compuets the norms for all the layers present in a model

# Import the uwimg library
from uwimg import * 

from model_definition import softmax_model
from import_data import get_data
# FIRST LOAD THE DATA
train_data = get_data()[0]
test_data = get_data()[1]


# Now iterate through the model layers
def iterate_over(model, iters, batchsize):
	# Create a model
	for iter in range(iters):
		calculate_G1(Model, data.X, data)
		print_matrix(Model.G1)
		psi = create_psi(data.X, data.y, 0.1)
		calculate_G2(Model, train.X, data, psi)
		# Now calculate the running average of Psi for all the layers in the model
		norm1 = 0
		for layers in Model.n:
			psi = running_average(psi, (Model.layers+iter).G1, (Model.layers+iter).G2)
			norm1 = calculate_delta_norm(norm1 ,psi)

	
if __name__ == "__main__":
	batchsize = 128
	data = random_batch(test_data ,batchsize)
	Model = softmax_model(data.X.cols, data.y.cols)
	iterate_over(Model, iters = 10, batchsize = 128)
