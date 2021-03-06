#include"hfft.h"

__global__ void __launch_bounds__(256,2) d_hfft4096x( float2* d_o, const float2* __restrict__ d_i, const float2* __restrict__ d_RF )
{																	
	__shared__ float smem[16*289];									
	float2 c[16], RF[16], temp;										
	d_i+=((blockIdx.x<<12)+threadIdx.x);							
	d_o+=((blockIdx.x<<12)+threadIdx.x);							
	const unsigned int lane=threadIdx.x&15;							
	const unsigned int slot=threadIdx.x>>4;		
	float* sstu=&smem[threadIdx.x];									
	float* sldu=&smem[272*slot+lane];	
	float* sstv=&smem[15*(slot&1)+289*slot+lane];
	float* sldv=&smem[15*(lane&1)+289*lane+17*slot];								
	RF[0]=d_RF[threadIdx.x];	
	mCALRF16(RF)									
	mLOAD16(c,d_i,256,)
	mFFT16(c,)													
	mHMRF16(c,RF)													
	RF[0]=d_RF[lane<<4];											
	mPERMUTE(16,sstu,sldu,c,272,16,0xf)									
	mCALRF16(RF)													
	mFFT16(c,)													
	mHMRF16(c,RF)
	mPERMUTE(16,sstv,sldv,c,17,1,0x7)
	mFFT16(c,)
	mISTORE16(d_o,c,256,)											
}
__global__ void __launch_bounds__(256,2) d_hifft4096x( float2* d_o, const float2* __restrict__ d_i, const float2* __restrict__ d_RF )
{																	
	__shared__ float smem[16*289];									
	float2 c[16], RF[15], temp;										
	d_i+=((blockIdx.x<<12)+threadIdx.x);							
	d_o+=((blockIdx.x<<12)+threadIdx.x);							
	const unsigned int lane=threadIdx.x&15;							
	const unsigned int slot=threadIdx.x>>4;							
	float* sstu=&smem[threadIdx.x];									
	float* sldu=&smem[272*slot+lane];	
	float* sstv=&smem[15*(slot&1)+289*slot+lane];
	float* sldv=&smem[15*(lane&1)+289*lane+17*slot];								
	RF[0]=d_RF[threadIdx.x];
	RF[0].y=-RF[0].y;
	mLOAD16(c,d_i,256,)												
	mCALRF16(RF)													
	mFFT16(c,i)													
	mHMRF16(c,RF)													
	RF[0]=d_RF[lane<<4];
	RF[0].y=-RF[0].y;
	mPERMUTE(16,sstu,sldu,c,272,16,0xf)									
	mCALRF16(RF)													
	mFFT16(c,i)													
	mHMRF16(c,RF)
	mPERMUTE(16,sstv,sldv,c,17,1,0x7)
	mFFT16(c,i)													
	mISTORE16(d_o,c,256,)											
}