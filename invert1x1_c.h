#ifndef invert1x1_c_h
#define invert1x1_c_h

static inline void invert1x1(const float * src, float * dst)
{
    /* Compute adjoint and multiply with reciprocal of determinant: */

    dst[0] = 1.0f / src[0];
}

#endif /* invert1x1_c_h */
