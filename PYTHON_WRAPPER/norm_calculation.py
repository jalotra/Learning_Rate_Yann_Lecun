from uwimg import *
from model_definitions import softmax_model, neural_net


def get_data():
	train = load_classification_data(c_char_p(train_file_path.encode('utf-8')), c_char_p(labels_path.encode('utf-8')), 1)
	test  = load_classification_data(c_char_p(test_file_path.encode('utf-8')),c_char_p(labels_path.encode('utf-8')) , 1)

	return (test, train)

# This python file runs the algorithm on the model
# def get_the_max_eigen_value(batch_size ):
# 	train_data = get_data()[0]
# 	model = softmax_model(train_data.X.cols, train_data.y.cols)
# 	for i in range(50):
# 		data b = random_batch(train_data, batch_size)
# 		calculate_gradient1(model, b.X)
# 		# Define the matrix psi
# 		create_psi(b.X.cols, b.y.cols)
# 		# Calculate gradient 2 by using psi 
# 		calculate_gradient2(model, b.X, psi)
# 		# Find the running avaerage
# 		psi = running_average()


