
# OPENCV=0
OPENMP=0
DEBUG=0
	
# All the objects to be made
OBJ=load_image.o process_image.o args.o data.o list.o calculate_gradients.o learning_rate_finder.o \
		matrix.o layer.o
EXOBJ=test.o

VPATH=./src/ ./input_data ./Main_Algorithm ./matrix_methods ./NeuralNetworkBackPropogation : ./	
SLIB=libuwimg.so
ALIB=libuwimg.a
EXEC=uwimg
OBJDIR=./obj/

CC=gcc
AR=ar
ARFLAGS=rcs
OPTS=-Ofast
LDFLAGS= -lm -pthread 
COMMON= -Iinclude/ -Isrc/ -flto
CFLAGS=-Wall -Wno-unknown-pragmas -Wfatal-errors -fPIC

ifeq ($(OPENMP), 1) 
CFLAGS+= -fopenmp
endif

ifeq ($(DEBUG), 1) 
OPTS=-O0 -g
COMMON= -Iinclude/ -Isrc/ 
endif

CFLAGS+=$(OPTS)

# ifeq ($(OPENCV), 1) 
# COMMON+= -DOPENCV
# CFLAGS+= -DOPENCV
# LDFLAGS+= `pkg-config --libs opencv` 
# COMMON+= `pkg-config --cflags opencv` 
# endif

EXOBJS = $(addprefix $(OBJDIR), $(EXOBJ))
OBJS = $(addprefix $(OBJDIR), $(OBJ))
DEPS = $(wildcard src/*.h) Makefile 

all: obj $(SLIB) $(ALIB) $(EXEC)
#all: obj $(EXEC)


$(EXEC): $(EXOBJ) $(OBJS)
	$(CC) $(COMMON) $(CFLAGS) $^ -o $@ $(LDFLAGS) 

$(ALIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(SLIB): $(OBJS)
	$(CC) $(CFLAGS) -shared $^ -o $@ $(LDFLAGS)

$(OBJDIR)%.o: %.c $(DEPS)
	$(CC) $(COMMON) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj

.PHONY: clean

clean:
	rm -rf $(OBJS) $(SLIB) $(ALIB) $(EXEC) $(EXOBJ) $(OBJDIR)/*