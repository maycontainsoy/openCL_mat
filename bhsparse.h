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

#ifndef BHSPARSE_H
#define BHSPARSE_H

#include "bhsparse_opencl.h"

class bhsparse
{
public:
    bhsparse();
    int initPlatform(bool *spgemm_platform);
    int initData(int m, int k, int n,
             int nnzA, value_type *csrValA, index_type *csrRowPtrA, index_type *csrColIndA,
             int nnzB, value_type *csrValB, index_type *csrRowPtrB, index_type *csrColIndB,
             index_type *csrRowPtrC, bool use_host_mem);
    int spgemm();
    int warmup();

    int get_nnzC();
    int get_C(index_type *csrColIndC, value_type *csrValC);

    int freePlatform();
    int free_mem();

private:
    bool *_spgemm_platform;

    bhsparse_opencl *_bh_sparse_opencl;

    bhsparse_timer _stage1_timer;
    bhsparse_timer _stage2_timer;
    bhsparse_timer _stage3_timer;
    bhsparse_timer _stage4_timer;

    int spgemm_opencl();

    int statistics();

    int compute_nnzC_Ct_opencl();

    int copy_Ct_to_C_opencl();

    int _m;
    int _k;
    int _n;

    size_t _nnzCt_full;

    // A
    int    _nnzA;
    int   *_h_csrRowPtrA;
    int   *_h_csrColIndA;
    value_type *_h_csrValA;

    // B
    int    _nnzB;
    int   *_h_csrRowPtrB;
    int   *_h_csrColIndB;
    value_type *_h_csrValB;

    // C
    int    _nnzC;
    int   *_h_csrRowPtrC;
    int   *_h_csrColIndC;
    value_type *_h_csrValC;

    // Ct
    //int    _nnzCt;
    int   *_h_csrRowPtrCt;
    //int   *_h_csrColIndCt;
    //value_type *_h_csrValCt;

    // statistics
    int   *_h_counter;
    int   *_h_counter_one;
    int   *_h_counter_sum;
    int   *_h_queue_one;

};

#endif // BHSPARSE_H