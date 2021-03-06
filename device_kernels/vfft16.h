#include"vfft.h"

#define CUDA_VFFT16X(dir,e,nt) CUDA_VFFTX_DECL(16,,dir,32,e,)\
{                                                            \
    float2 c[16], temp;                                      \
    unsigned int slot=blockIdx.x/((1<<e)/nt);                \
    unsigned int bidx=blockIdx.x&(((1<<e)/nt)-1);            \
    size_t p=blockIdx.y*512*(1<<e)+bidx*nt+threadIdx.x;      \
    d_i+=(p+slot*16*(1<<e));                                 \
    d_o+=(p+slot*(1<<e));                                    \
    mLOAD16(c,d_i,(1<<e),)                                   \
    mFFT16(c,dir)                                            \
    mISTORE16(d_o,c,32*(1<<e),)                              \
}

CUDA_VFFT16X(, 1,  2)
CUDA_VFFT16X(, 2,  4)
CUDA_VFFT16X(, 3,  8)
CUDA_VFFT16X(, 4, 16)
CUDA_VFFT16X(, 5, 32)
CUDA_VFFT16X(, 6, 64)
CUDA_VFFT16X(, 7,128)
CUDA_VFFT16X(, 8,256)
CUDA_VFFT16X(, 9,256)
CUDA_VFFT16X(,10,256)
CUDA_VFFT16X(,11,256)
CUDA_VFFT16X(,12,256)
CUDA_VFFT16X(,13,256)
CUDA_VFFT16X(,14,256)
CUDA_VFFT16X(,15,256)
CUDA_VFFT16X(,16,256)

CUDA_VFFT16X(i, 1,  2)
CUDA_VFFT16X(i, 2,  4)
CUDA_VFFT16X(i, 3,  8)
CUDA_VFFT16X(i, 4, 16)
CUDA_VFFT16X(i, 5, 32)
CUDA_VFFT16X(i, 6, 64)
CUDA_VFFT16X(i, 7,128)
CUDA_VFFT16X(i, 8,256)
CUDA_VFFT16X(i, 9,256)
CUDA_VFFT16X(i,10,256)
CUDA_VFFT16X(i,11,256)
CUDA_VFFT16X(i,12,256)
CUDA_VFFT16X(i,13,256)
CUDA_VFFT16X(i,14,256)
CUDA_VFFT16X(i,15,256)
CUDA_VFFT16X(i,16,256)