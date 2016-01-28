#ifndef invert2x2_llvm_h
#define invert2x2_llvm_h

static inline void __attribute__((__always_inline__, __nodebug__)) invert2x2(const float * src, float * dst)
{
    typedef __attribute__((__ext_vector_type__(4))) float float4;

    float4 tmp, adj, det;

    /* Load matrix: */

    tmp = * ((float4 *) src);

    /* Compute adjoint: */

    adj = - tmp;

    adj = __builtin_shufflevector(tmp, adj, 3, 5, 6, 0);

    /* Compute determinant: */

    tmp = __builtin_shufflevector(tmp, tmp, 0, 2, 1, 3);

    det = tmp * adj;

    tmp = __builtin_shufflevector(det, det, 1, 0, 3, 2);

    det = det + tmp;

    /* Multiply adjoint with reciprocal of determinant: */

    adj = adj / det;

    /* Store inverted matrix: */

    * ((float4 *) dst) = adj;
}

#endif /* invert2x2_llvm_h */
