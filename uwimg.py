from ctypes import *
import math
import random
import os


def c_array(ctype, values):
    arr = (ctype*len(values))()
    arr[:] = values
    return arr

# class IMAGE(Structure):
#     _fields_ = [("w", c_int),
#                 ("h", c_int),
#                 ("c", c_int),
#                 ("data", POINTER(c_float))]


#lib = CDLL("/home/pjreddie/documents/455/libuwimg.so", RTLD_GLOBAL)
lib = CDLL(os.path.join(os.getcwd(), "libuwimg.so"), RTLD_GLOBAL) 



# LETS DEFINE ALL THE LIBRARY FUNCTIONS THAT THE YANN LECUN PAPER WILL USE 
class IMAGE(Structure):
    _fields_ = [("w", c_int),
                ("h", c_int),
                ("c", c_int),
                ("data", POINTER(c_float))]
    def __add__(self, other):
        return add_image(self, other)
    def __sub__(self, other):
        return sub_image(self, other)

class POINT(Structure):
    _fields_ = [("x", c_float),
                ("y", c_float)]

class DESCRIPTOR(Structure):
    _fields_ = [("p", POINT),
                ("n", c_int),
                ("data", POINTER(c_float))]

class MATRIX(Structure):
    _fields_ = [("rows", c_int),
                ("cols", c_int),
                ("data", POINTER(POINTER(c_double))),
                ("shallow", c_int)]

class DATA(Structure):
    _fields_ = [("X", MATRIX),
                ("y", MATRIX)]

(RELU, LRELU, SOFTMAX) = range(3    )
class LAYER(Structure):
    _fields_ = [("in", MATRIX),
                ("dw", MATRIX),
                ("w", MATRIX),
                ("v", MATRIX),
                ("out", MATRIX),
                ("G1", MATRIX),
                ("G2", MATRIX),
                ("activation", c_int)]

class MODEL(Structure):
    _fields_ = [("layers", POINTER(LAYER)),
                ("n", c_int)]



def make_model(layers):
    m = MODEL()
    m.n = len(layers)
    m.layers = (LAYER*m.n) (*layers)
    return m

#######################################################################
make_image = lib.make_image
make_image.argtypes = [c_int, c_int, c_int]
make_image.restype = IMAGE

free_image = lib.free_image
free_image.argtypes = [IMAGE]

load_image_lib = lib.load_image
load_image_lib.argtypes = [c_char_p]
load_image_lib.restype = IMAGE

def load_image(f):
    return load_image_lib(f.encode('ascii'))

save_image_lib = lib.save_image
save_image_lib.argtypes = [IMAGE, c_char_p]

def save_image(im, f):
    return save_image_lib(im, f.encode('ascii'))


'''
Using METHODS DEFINED IN THE process_image.c '''
get_pixel = lib.get_pixel
get_pixel.argtypes = [IMAGE, c_int, c_int, c_int]
get_pixel.restype = c_float

set_pixel = lib.set_pixel
set_pixel.argtypes = [IMAGE, c_int, c_int, c_int, c_float]


copy_image = lib.copy_image
copy_image.argtypes = [IMAGE]
copy_image.restype = IMAGE
# ###########################################################################



#####################################################################################
# NUERAL NETWORK STUFF
forward_model = lib.forward_model
forward_model.argtypes = [MODEL, MATRIX]
forward_model.restype = MATRIX

load_classification_data = lib.load_classification_data
load_classification_data.argtypes = [c_char_p, c_char_p, c_int]
load_classification_data.restype = DATA

make_layer = lib.make_layer
make_layer.argtypes = [c_int, c_int, c_int]
make_layer.restype = LAYER

# For the claculation of gradients
calculate_G1 = lib.calculate_gradient1
calculate_G1.argtypes = [MODEL, MATRIX, DATA]
calculate_G1.restype = None

calculate_G2 = lib.calculate_gradient2
calculate_G2.argtypes = [MODEL, MATRIX, DATA, MATRIX]
calculate_G2.restype = None

# FInding the Runnig avaregae of Psi
# matrix running_average(matrix, matrix, matrix);
running_average = lib.running_average
running_average.argtypes = [MATRIX, MATRIX, MATRIX]
running_average.restype = MATRIX

# For calculate the norm of psi AT each step
# int calculate_delta_norm(double norm1, matrix psi)
calculate_delta_norm = lib.calculate_delta_norm
calculate_delta_norm.argtypes = [c_double, MATRIX]
calculate_delta_norm.restype = c_double 

# TO define PSI
# matrix create_psi(int rows, int cols, double s)
# {
#     return random_matrix(rows, cols, s);
# }
create_psi = lib.create_psi
create_psi.argtypes = [c_int, c_int, c_double]
create_psi.restype = MATRIX

if __name__ == "__main__":
    # create_test_photos_directory()
    # Testing pre-build methods
    im = load_image("data/dog.jpg")
    save_image(im, test_photos_directory + "hey")
    # Testing custom process_image.c methods
    new_image = copy_image(im)
    print("----------------------------------------------------------------")
    pixel_value = get_pixel(new_image, im.w//2, im.h//2, 0)
    print("The pixel value at the CHW (0, im.h//2, im.w//2) is :", pixel_value)
    # print(pixel_value)

    print('Copying the dog_image into a new_image')
    sqaure_box_dimension = 50
    for i in range(1,sqaure_box_dimension):
        for j in range(1,sqaure_box_dimension):
            set_pixel(new_image, im.w//2 - i, im.h//2 - j, 0, 1.0)
            set_pixel(new_image, im.w//2 - i, im.h//2 - j, 1, 1.0)
            set_pixel(new_image, im.w//2 - i, im.h//2 - j, 2, 1.0)
    print('Setting some pixels in the pixels white')
    print('See the resultant image in the new_hey image')
    save_image(new_image, test_photos_directory + "new_hey")
    print("----------------------------------------------------------------")

