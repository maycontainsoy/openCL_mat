#compilers
CC=icc

#includes

#libs
#OPENCL_LIBS = -L/usr/local/lib64/ -libOpenCL.so 
LIBS = -L$(OPENCL_LIBS) -lOpenCL

all: 
	$(CC) -I $(OPENCL_INCLUDE) -O3 main.cpp bhsparse.cpp bhsparse_opencl.cpp basiccl.cpp -o spgemm $(LIBS)
