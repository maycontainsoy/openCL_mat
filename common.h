/* ************************************************************************
* The MIT License (MIT)
* Copyright 2014-2015 weifengliu
 
*  Permission is hereby granted, free of charge, to any person obtaining a copy
*  of this software and associated documentation files (the "Software"), to deal
*  in the Software without restriction, including without limitation the rights
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the Software is
*  furnished to do so, subject to the following conditions:
 
*  The above copyright notice and this permission notice shall be included in
*  all copies or substantial portions of the Software.
 
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
*  THE SOFTWARE.
* ************************************************************************ */
//////////////////////////////////////////////////////////////////////////
// < A CUDA/OpenCL General Sparse Matrix-Matrix Multiplication Program >
//
// < See paper:
// Weifeng Liu and Brian Vinter, "An Efficient GPU General Sparse
// Matrix-Matrix Multiplication for Irregular Data," Parallel and
// Distributed Processing Symposium, 2014 IEEE 28th International
// (IPDPS '14), pp.370-381, 19-23 May 2014
// for details. >
//////////////////////////////////////////////////////////////////////////

#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <math.h>

#include <sys/time.h>
#include <sys/types.h>
#include <dirent.h>

#ifdef __APPLE__
#include "OpenCL/opencl.h"
#else
#include "CL/cl.h"
#endif

#define BHSPARSE_SUCCESS 0

using namespace std;

typedef int     index_type;
typedef double   value_type;

#define NUM_PLATFORMS     9

#define NAIVE             0
#define BHSPARSE_CUDA     1
#define BHSPARSE_OPENCL   2

#define WARPSIZE_NV  32
#define WARPSIZE_AMD 64

#define NUM_BANKS 32

#define WARPSIZE_NV_2HEAP 64

#define TUPLE_QUEUE 6
#define MERGELIST_INITSIZE 256

#define MERGEPATH_LOCAL     0
#define MERGEPATH_LOCAL_L2  1
#define MERGEPATH_GLOBAL    2

#define GROUPSIZE_32   32
#define GROUPSIZE_128  128
#define GROUPSIZE_256  256
#define GROUPSIZE_512  512
#define GROUPSIZE_1024 1024

#define NUM_SEGMENTS 128

struct bhsparse_timer {
    timeval t1, t2;
    struct timezone tzone;

    void start() {
        gettimeofday(&t1, &tzone);
    }

    double stop() {
        gettimeofday(&t2, &tzone);
        double elapsedTime = 0;
        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
        elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
        return elapsedTime;
    }
};

#endif // COMMON_H