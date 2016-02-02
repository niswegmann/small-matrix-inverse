#ifndef invert3x3_c_h
#define invert3x3_c_h

static inline void invert3x3(const float * src, float * dst)
{
    float det;

    /* Compute adjoint: */

    dst[0] = + src[4] * src[8] - src[5] * src[7];
    dst[1] = - src[1] * src[8] + src[2] * src[7];
    dst[2] = + src[1] * src[5] - src[2] * src[4];
    dst[3] = - src[3] * src[8] + src[5] * src[6];
    dst[4] = + src[0] * src[8] - src[2] * src[6];
    dst[5] = - src[0] * src[5] + src[2] * src[3];
    dst[6] = + src[3] * src[7] - src[4] * src[6];
    dst[7] = - src[0] * src[7] + src[1] * src[6];
    dst[8] = + src[0] * src[4] - src[1] * src[3];

    /* Compute determinant: */

    det = src[0] * dst[0] + src[1] * dst[3] + src[2] * dst[6];

    /* Multiply adjoint with reciprocal of determinant: */

    det = 1.0f / det;

    dst[0] *= det;
    dst[1] *= det;
    dst[2] *= det;
    dst[3] *= det;
    dst[4] *= det;
    dst[5] *= det;
    dst[6] *= det;
    dst[7] *= det;
    dst[8] *= det;
}

#endif /* invert3x3_c_h */
