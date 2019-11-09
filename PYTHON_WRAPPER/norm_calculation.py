from uwimg import *
import time
import sys

# Model Definitions
def softmax_model(inputs, outputs):
    l = [make_layer(inputs, outputs, SOFTMAX)]
    return make_model(l)

def neural_net(inputs, outputs):
    print (inputs)
    l = [make_layer(inputs, 32, RELU),
    		make_layer(32, 16,RELU),
		#make_layer(16, 8, RELU),
            make_layer(16, outputs, SOFTMAX)]
    return make_model(l)

def save_to_file(filepath, process_to_run):

	orig_stdout = sys.stdout
	with open('filepath', 'w') as f:
		sys.stdout = f

		process_to_run

		sys.stdout = orig_stdout
		f.close()


if __name__ == "__main__":
	# save_to_file("results/mnist_Relu_Activation", neural_on_mnist_dataset())
	pass
	