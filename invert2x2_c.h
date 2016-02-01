#ifndef invert2x2_c_h
#define invert2x2_c_h

static inline void invert2x2(const float * src, float * dst)
{
    float det;

    /* Compute adjoint: */

    dst[0] = + src[3];
    dst[1] = - src[1];
    dst[2] = - src[2];
    dst[3] = + src[0];

    /* Compute determinant: */

    det = src[0] * dst[0] + src[1] * dst[2];

    /* Multiply adjoint with reciprocal of determinant: */

    det = 1.0f / det;

    dst[0] *= det;
    dst[1] *= det;
    dst[2] *= det;
    dst[3] *= det;
}

#endif /* invert2x2_c_h */
