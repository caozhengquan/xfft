#include"../include/xfft_op.h"
#include"../include/xfft_hop.h"
#include"../include/xfft_vop.h"
#include"../include/xfft_patch.h"

int xfft_createOp_1d( xfftOp_t* const __restrict Op, xfft_context_t* const __restrict p_ctx, int n, int bat, float2* __restrict p_temp )
{
	size_t nb;
	int size;
	Op->nk=(n<=8192)?2:4;
	if((Op->p_kernel=(xfft_kernel_t*)malloc(Op->nk*sizeof(xfft_kernel_t)))==0)
		return XFFT_ERROR_OUT_OF_MEMORY;
	Op->nx=n;
	Op->ny=1;
	Op->nz=1;
	Op->bat=bat;
	Op->eh=__bffs(n)-1;
	size=xfft_get_size_HRF( Op->eh );
	xfft_context_bind( p_ctx );
	if(size>0)
	{
		nb=nAFFI(size*sizeof(float2),p_ctx->alignment);
		if(cuMemAlloc(&Op->d_HRF,nb)!=CUDA_SUCCESS){
			free(Op->p_kernel);
			Op->p_kernel=0;
			return XFFT_ERROR_OUT_OF_DEVICE_MEMORY;
		}	
		xfft_calcHRF( p_temp, size, 1.0/n );
		cuMemcpyHtoD( Op->d_HRF, p_temp, size*sizeof(float2) );
	}	
	hfft_bki( Op->p_kernel, &Op->texref, p_ctx->module, Op->d_HRF, Op->nk, bat, Op->eh );
	return XFFT_SUCCESS;
}
int xfft_createOp_2d( xfftOp_t* const __restrict Op, xfft_context_t* const __restrict p_ctx, int nx, int ny, int bat, float2* __restrict p_temp )
{
	size_t nb; 
	int is_patch, hnk, vnk, nh, nv;
	is_patch=(nx==ny)&(nx<=64);
	if(!is_patch){		
		hnk=(nx<=8192)?2:4;
		vnk=(ny<  512)?2:4;
		Op->nk=hnk+vnk;
	} else {	
		Op->nk=2;
	}
	if((Op->p_kernel=(xfft_kernel_t*)malloc(Op->nk*sizeof(xfft_kernel_t)))==0)
		return XFFT_ERROR_OUT_OF_MEMORY;
	Op->nx=nx;
	Op->ny=ny;
	Op->nz=1;
	Op->bat=bat;
	Op->eh=__bffs(nx)-1;
	Op->eu=__bffs(ny)-1;
	nh=xfft_get_size_HRF( Op->eh );
	nv=xfft_get_size_VRF( Op->eu );
	nv=is_patch?0:nv;
	xfft_context_bind( p_ctx );
	if((nh+nv)>0)
	{
		nb=nAFFI(nh*sizeof(float2),p_ctx->alignment);
		if(cuMemAlloc(&Op->d_HRF,nb+nv*sizeof(float2))!=CUDA_SUCCESS){
			free(Op->p_kernel);
			Op->p_kernel=0;
			return XFFT_ERROR_OUT_OF_DEVICE_MEMORY;
		}	
		if(nx>16){
			xfft_calcHRF( p_temp, nh, 1.0/nx );
			cuMemcpyHtoD( Op->d_HRF, p_temp, nh*sizeof(float2) );
		}
		if(nv!=0){		
			Op->d_VRF=Op->d_HRF+nb; 
			xfft_calcVRF( p_temp, Op->eu );
			cuMemcpyHtoD( Op->d_VRF, p_temp, nv*sizeof(float2) );
		}
	}
	if(!is_patch){	
		hfft_bki( Op->p_kernel, &Op->texref, p_ctx->module, Op->d_HRF, hnk, ny*bat, Op->eh );
		vfft_bki( &Op->p_kernel[hnk], p_ctx->module, Op->d_VRF, vnk, bat, Op->eh, Op->eu );
	} else {
		fft2d_patch_bki( Op->p_kernel, p_ctx->module, Op->d_HRF, bat, Op->eh );
	}
	return XFFT_SUCCESS;
}
int xfft_createOp_3d( xfftOp_t* const __restrict Op, xfft_context_t* const __restrict p_ctx, int nx, int ny, int nz, int bat, float2* __restrict p_temp )
{
	size_t hnb, unb; 
	int is_patch, hnk, unk, vnk, nh, nu, nv;
	is_patch=(nx==ny)&(nx<=64);
	if(!is_patch){
		hnk=(nx<=8192)?2:4;		
		unk=(ny<512)?2:4;
		Op->nk=hnk+unk;
	} else {	
		hnk=2; unk=0; Op->nk=2; 
	}
	vnk=(nz<512)?2:4;
	Op->nk+=vnk;
	if((Op->p_kernel=(xfft_kernel_t*)malloc(Op->nk*sizeof(xfft_kernel_t)))==0)
		return XFFT_ERROR_OUT_OF_MEMORY;
	Op->nx=nx;
	Op->ny=ny;
	Op->nz=nz;
	Op->bat=bat;
	Op->eh=__bffs(nx)-1;
	Op->eu=__bffs(ny)-1;
	Op->ev=__bffs(nz)-1;
	nh=xfft_get_size_HRF( Op->eh );
	nu=xfft_get_size_VRF( Op->eu );
	nv=xfft_get_size_VRF( Op->ev );
	nu=is_patch?0:nu;
	xfft_context_bind( p_ctx );
	if((nh+nu+nv)>0)
	{
		hnb=nAFFI(nh*sizeof(float2),p_ctx->alignment);
		unb=nAFFI(nu*sizeof(float2),p_ctx->alignment);
		if(cuMemAlloc(&Op->d_HRF,hnb+unb+nv*sizeof(float2))!=CUDA_SUCCESS){
			free(Op->p_kernel);
			Op->p_kernel=0;
			return XFFT_ERROR_OUT_OF_DEVICE_MEMORY;
		}		
		Op->d_URF=Op->d_HRF+hnb; 
		Op->d_VRF=Op->d_URF+unb; 
		if(nx>16){
			xfft_calcHRF( p_temp, nh, 1.0/nx );
			cuMemcpyHtoD( Op->d_HRF, p_temp, nh*sizeof(float2) );
		}			
		if(nu!=0){
			xfft_calcVRF( p_temp, Op->eu );
			cuMemcpyHtoD( Op->d_URF, p_temp, nu*sizeof(float2) );
		}
		if(nv!=0){	
			if((Op->eu!=Op->ev)|is_patch){
				xfft_calcVRF( p_temp, Op->ev );
				cuMemcpyHtoD( Op->d_VRF, p_temp, nv*sizeof(float2) );
			} else {
				Op->d_VRF=Op->d_URF;
			}
		}
	}
	if(!is_patch){	
		hfft_bki( Op->p_kernel, &Op->texref, p_ctx->module, Op->d_HRF, hnk, ny*nz*bat, Op->eh );
		vfft_bki( &Op->p_kernel[hnk], p_ctx->module, Op->d_URF, unk, nz*bat, Op->eh, Op->eu );
	} else {
		fft2d_patch_bki( Op->p_kernel, p_ctx->module, Op->d_HRF, nz*bat, Op->eh );
	}
	vfft_bki( &Op->p_kernel[hnk+unk], p_ctx->module, Op->d_VRF, vnk, bat, Op->eh+Op->eu+1, Op->ev );
	return XFFT_SUCCESS;
}
void xfft_bind_stream( xfftOp_t* const Op, CUstream s )
{
	int i=0;
	do{ Op->p_kernel[i].stream=s; }while((++i)<Op->nk);
}
CUdeviceptr xfft_exec( xfftOp_t* const Op, CUdeviceptr d_a, CUdeviceptr d_b, int dir )
{
	CUdeviceptr d_x, d_y, d_z; 
	int i, n, use_tex, is_patch, in_place;
	n=Op->nx*Op->ny*Op->nz*Op->bat;
	use_tex=(Op->nx==512)&(((1<<27)/n)>0);
	is_patch=(Op->nx==Op->ny)&(Op->nx<=64);
	if(use_tex){
		cuTexRefSetAddress( 0, Op->texref, d_a, sizeof(float2)*n );
	}
	d_x=d_a; d_y=d_b; d_z=d_x; i=dir;
	in_place=use_tex|is_patch;
	xfft_kernel_sep_ptr( &Op->p_kernel[i], 0, in_place?d_x:d_y );
	if(!in_place){
		xfft_kernel_sep_ptr( &Op->p_kernel[i], 1, d_x );
		d_x=d_y; d_y=d_z;
	}
	xfft_kernel_launch( &Op->p_kernel[i] );	
	while((i+=2)<Op->nk){
		xfft_kernel_sep_ptr( &Op->p_kernel[i], 0, d_y );
		xfft_kernel_sep_ptr( &Op->p_kernel[i], 1, d_x );
		xfft_kernel_launch( &Op->p_kernel[i] );
		d_z=d_y; d_y=d_x; d_x=d_z;
	}
	return d_z;
}
void xfft_release( xfftOp_t* const Op )
{
	if(Op->p_kernel){
		free(Op->p_kernel);
		Op->p_kernel=0;
		cuMemFree(Op->d_HRF);
	}
}