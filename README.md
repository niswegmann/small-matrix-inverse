# About
**Small Matrix Inverse** (*SMI*) is a portable, [SIMD](https://en.wikipedia.org/wiki/SIMD) optimised library for [matrix inversion](https://en.wikipedia.org/wiki/Invertible_matrix) of 2, 3, and 4 order (square) matrices. It is written in pure [C99](https://en.wikipedia.org/wiki/C99) combined with LLVM/SSE/NEON [compiler intrinsics](https://en.wikipedia.org/wiki/Intrinsic_function). The 4x4 routines are based on Intel's "[Streaming SIMD Extensions - Inverse of 4x4 Matrix](ftp://download.intel.com/design/pentiumiii/sml/24504301.pdf)."

# Installation
Simply copy the relevant headers (e.g. "[invert2x2-llvm.h](https://github.com/niswegmann/small-matrix-inverse/blob/master/invert2x2_llvm.h)" or "[invert4x4-sse.h](https://github.com/niswegmann/small-matrix-inverse/blob/master/invert4x4_sse.h)") into your project.

# Usage

SMI is straightforward to use. Include the appropriate header and you're good to go:

    #include "invert4x4-llvm.h"
    ...
    float M[16] __attribute__((aligned(16))) =
        {
            + 1.0f, + 2.0f, - 1.0f, + 3.0f,
            - 5.0f, + 1.0f, - 4.0f, - 2.0f,
            - 3.0f, + 8.0f, + 2.0f, - 4.0f,
            + 7.0f, - 9.0f, - 4.0f, - 6.0f
        };
    
    float Minv[16] __attribute__((aligned(16)));
    
    invert4x4(M, Minv);
    ...

The input matrix must be non-singular and can be in either row-major or column-major order -- it doesn't matter since for all singular matrices **M** *transpose*(*invert*(*transpose*(**M**))) is equal to *invert*(**M**). If
the input matrix is singular, the result is undefined. For the sake of efficiency remember to align input and output buffers.

# Benchmark
SMI hasn't been proberly benchmarked yet. However, initial tests indicates a 50% to 100% performance increase over the matrix inverse routines in Apple's new SIMD library (<simd/simd.h>) which targets 2x-, 3x-, and 4x- vectors/matrices.

# Supported Architectures
The goal is to support all commen architectures for 2x2, 3x3, and 4x4 matrices. LLVM covers both x86, x86-64, and ARMv7, but specialised versions for ARM NEON are planned.

Here's an overview of the currently supported architectures:

|     | LLVM | SSE  | NEON |
| --- | ---- | ---- | ---- |
| 2x2 |  ✓   |  -   |  -   |
| 3x3 |  -   |  -   |  -   |
| 4x4 |  ✓   |  ✓   |  -   |

# Contributing
Send any comments, chocolate, and/or suggestions to nis@primal-audio.com.

# License
SMI is licenced under CC0 1.0 Universal.
