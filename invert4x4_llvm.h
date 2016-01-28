#ifndef invert4x4_llvm_h
#define invert4x4_llvm_h

static inline void invert4x4(const float * src, float * dst)
{
    typedef __attribute__((__ext_vector_type__(4))) float float4;

    float4 row0, row1, row2, row3;
    float4 col0, col1, col2, col3;
    float4 det, tmp1;

    /* Load: */

    col0 = ((float4 *) src)[0];
    col1 = ((float4 *) src)[1];
    col2 = ((float4 *) src)[2];
    col3 = ((float4 *) src)[3];

    /* Transpose: */

    tmp1 = __builtin_shufflevector(col0, col2, 0, 4, 1, 5);
    row1 = __builtin_shufflevector(col1, col3, 0, 4, 1, 5);

    row0 = __builtin_shufflevector(tmp1, row1, 0, 4, 1, 5);
    row1 = __builtin_shufflevector(tmp1, row1, 2, 6, 3, 7);

    tmp1 = __builtin_shufflevector(col0, col2, 2, 6, 3, 7);
    row3 = __builtin_shufflevector(col1, col3, 2, 6, 3, 7);

    row2 = __builtin_shufflevector(tmp1, row3, 0, 4, 1, 5);
    row3 = __builtin_shufflevector(tmp1, row3, 2, 6, 3, 7);

    /* Compute adjoint: */

    row1 = __builtin_shufflevector(row1, row1, 2, 3, 0, 1);
    row3 = __builtin_shufflevector(row3, row3, 2, 3, 0, 1);

    tmp1 = row2 * row3;
    tmp1 = __builtin_shufflevector(tmp1, tmp1, 1, 0, 7, 6);

    col0 = row1 * tmp1;
    col1 = row0 * tmp1;

    tmp1 = __builtin_shufflevector(tmp1, tmp1, 2, 3, 4, 5);

    col0 = row1 * tmp1 - col0;
    col1 = row0 * tmp1 - col1;
    col1 = __builtin_shufflevector(col1, col1, 2, 3, 4, 5);

    tmp1 = row1 * row2;
    tmp1 = __builtin_shufflevector(tmp1, tmp1, 1, 0, 7, 6);

    col0 = row3 * tmp1 + col0;
    col3 = row0 * tmp1;

    tmp1 = __builtin_shufflevector(tmp1, tmp1, 2, 3, 4, 5);

    col0 = col0 - row3 * tmp1;
    col3 = row0 * tmp1 - col3;
    col3 = __builtin_shufflevector(col3, col3, 2, 3, 4, 5);

    tmp1 = __builtin_shufflevector(row1, row1, 2, 3, 4, 5) * row3;
    tmp1 = __builtin_shufflevector(tmp1, tmp1, 1, 0, 7, 6);
    row2 = __builtin_shufflevector(row2, row2, 2, 3, 4, 5);

    col0 = row2 * tmp1 + col0;
    col2 = row0 * tmp1;

    tmp1 = __builtin_shufflevector(tmp1, tmp1, 2, 3, 4, 5);

    col0 = col0 - row2 * tmp1;
    col2 = row0 * tmp1 - col2;
    col2 = __builtin_shufflevector(col2, col2, 2, 3, 4, 5);

    tmp1 = row0 * row1;
    tmp1 = __builtin_shufflevector(tmp1, tmp1, 1, 0, 7, 6);

    col2 = row3 * tmp1 + col2;
    col3 = row2 * tmp1 - col3;

    tmp1 = __builtin_shufflevector(tmp1, tmp1, 2, 3, 4, 5);

    col2 = row3 * tmp1 - col2;
    col3 = col3 - row2 * tmp1;

    tmp1 = row0 * row3;
    tmp1 = __builtin_shufflevector(tmp1, tmp1, 1, 0, 7, 6);

    col1 = col1 - row2 * tmp1;
    col2 = row1 * tmp1 + col2;

    tmp1 = __builtin_shufflevector(tmp1, tmp1, 2, 3, 4, 5);

    col1 = row2 * tmp1 + col1;
    col2 = col2 - row1 * tmp1;

    tmp1 = row0 * row2;
    tmp1 = __builtin_shufflevector(tmp1, tmp1, 1, 0, 7, 6);

    col1 = row3 * tmp1 + col1;
    col3 = col3 - row1 * tmp1;

    tmp1 = __builtin_shufflevector(tmp1, tmp1, 2, 3, 4, 5);

    col1 = col1 - row3 * tmp1;
    col3 = row1 * tmp1 + col3;

    /* Compute determinant: */

    det = row0 * col0;
    det = __builtin_shufflevector(det, det, 2, 3, 4, 5) + det;
    det = __builtin_shufflevector(det, det, 1, 0, 7, 6) + det;

    /* Compute reciprocal of determinant: */

    det = 1.0f / det;

    /* Multiply matrix of cofactors with reciprocal of determinant: */

    col0 = col0 * det;
    col1 = col1 * det;
    col2 = col2 * det;
    col3 = col3 * det;

    /* Store: */

    ((float4 *) dst)[0] = col0;
    ((float4 *) dst)[1] = col1;
    ((float4 *) dst)[2] = col2;
    ((float4 *) dst)[3] = col3;
}

#endif /* invert4x4_llvm_h */
