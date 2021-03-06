#include"../include/xfft_hop.h"

static void __hffte01_bk( xfft_kernel_t* const p, CUmodule module, int nop )
{
	xfft_create_kernel( &p[0], module, "d_hfft2x"	);
	xfft_create_kernel( &p[1], module, "d_hfft2x"	);
	xfft_kernel_sao( &p[0], XFFT_AM_P_P_I );
	xfft_kernel_sao( &p[1], XFFT_AM_P_P_I );
}
static void __hffte02_bk( xfft_kernel_t* const p, CUmodule module, int nop )
{
	xfft_create_kernel( &p[0], module, "d_hfft4x"	);
	xfft_create_kernel( &p[1], module, "d_hifft4x"	);
	xfft_kernel_sao( &p[0], XFFT_AM_P_P_I );
	xfft_kernel_sao( &p[1], XFFT_AM_P_P_I );
}
static void __hffte03_bk( xfft_kernel_t* const p, CUmodule module, int nop )
{
	xfft_create_kernel( &p[0], module, "d_hfft8x"	);
	xfft_create_kernel( &p[1], module, "d_hifft8x"	);
	xfft_kernel_sao( &p[0], XFFT_AM_P_P_I );
	xfft_kernel_sao( &p[1], XFFT_AM_P_P_I );
}
static void __hffte04_bk( xfft_kernel_t* const p, CUmodule module, int nop )
{
	xfft_create_kernel( &p[0], module, "d_hfft16x"	);
	xfft_create_kernel( &p[1], module, "d_hifft16x"	);
	xfft_kernel_sao( &p[0], XFFT_AM_P_P_I );
	xfft_kernel_sao( &p[1], XFFT_AM_P_P_I );
}
static void __hffte05_bk( xfft_kernel_t* const p, CUmodule module, int nop )
{
	xfft_create_kernel( &p[0], module, "d_hfft32x"	);
	xfft_create_kernel( &p[1], module, "d_hifft32x"	);
	xfft_kernel_sao( &p[0], XFFT_AM_P_P_P_I );
	xfft_kernel_sao( &p[1], XFFT_AM_P_P_P_I );
}
static void __hffte06_bk( xfft_kernel_t* const p, CUmodule module, int nop )
{
	xfft_create_kernel( &p[0], module, "d_hfft64x"	);
	xfft_create_kernel( &p[1], module, "d_hifft64x"	);
	xfft_kernel_sao( &p[0], XFFT_AM_P_P_P_I );
	xfft_kernel_sao( &p[1], XFFT_AM_P_P_P_I );
}
static void __hffte07_bk( xfft_kernel_t* const p, CUmodule module, int nop )
{
	xfft_create_kernel( &p[0], module, "d_hfft128x"	);
	xfft_create_kernel( &p[1], module, "d_hifft128x");
	xfft_kernel_sao( &p[0], XFFT_AM_P_P_P_I );
	xfft_kernel_sao( &p[1], XFFT_AM_P_P_P_I );
}
static void __hffte08_bk( xfft_kernel_t* const p, CUmodule module, int nop )
{
	xfft_create_kernel( &p[0], module, "d_hfft256x"	);
	xfft_create_kernel( &p[1], module, "d_hifft256x");
	xfft_kernel_sao( &p[0], XFFT_AM_P_P_P_I );
	xfft_kernel_sao( &p[1], XFFT_AM_P_P_P_I );
}
static void __hffte09_bk( xfft_kernel_t* const p, CUmodule module, int use_tex )
{
	const char* xnames=use_tex?"d_hfft512x_tex" :"d_hfft512x" ;
	const char* ynames=use_tex?"d_hifft512x_tex":"d_hifft512x";
	unsigned int mask=use_tex?XFFT_AM_P_P:XFFT_AM_P_P_P;
	xfft_create_kernel( &p[0], module, xnames );
	xfft_create_kernel( &p[1], module, ynames );
	xfft_kernel_sao( &p[0], mask );
	xfft_kernel_sao( &p[1], mask );
}
static void __hffte10_bk( xfft_kernel_t* const p, CUmodule module, int nop )
{
	xfft_create_kernel( &p[0], module, "d_hfft1024x"	);
	xfft_create_kernel( &p[1], module, "d_hifft1024x"	);
	xfft_kernel_sao( &p[0], XFFT_AM_P_P_P );
	xfft_kernel_sao( &p[1], XFFT_AM_P_P_P );
}
static void __hffte11_bk( xfft_kernel_t* const p, CUmodule module, int nop )
{
	xfft_create_kernel( &p[0], module, "d_hfft2048x"	);
	xfft_create_kernel( &p[1], module, "d_hifft2048x"	);
	xfft_kernel_sao( &p[0], XFFT_AM_P_P_P );
	xfft_kernel_sao( &p[1], XFFT_AM_P_P_P );
}
static void __hffte12_bk( xfft_kernel_t* const p, CUmodule module, int nop )
{
	xfft_create_kernel( &p[0], module, "d_hfft4096x"	);
	xfft_create_kernel( &p[1], module, "d_hifft4096x"	);
	xfft_kernel_sao( &p[0], XFFT_AM_P_P_P );
	xfft_kernel_sao( &p[1], XFFT_AM_P_P_P );
}
static void __hffte13_bk( xfft_kernel_t* const p, CUmodule module, int nop )
{
	xfft_create_kernel( &p[0], module, "d_hfft8192x"	);
	xfft_create_kernel( &p[1], module, "d_hifft8192x"	);
	xfft_kernel_sao( &p[0], XFFT_AM_P_P_P );
	xfft_kernel_sao( &p[1], XFFT_AM_P_P_P );
}
static void __hffte14_bk( xfft_kernel_t* const p, CUmodule module, int nop )
{
	xfft_create_kernel( &p[0], module, "d_hfft128Sx"	);
	xfft_create_kernel( &p[1], module, "d_hifft128Sx"	);
	xfft_create_kernel( &p[2], module, "d_hfft128Tx"	);
	xfft_create_kernel( &p[3], module, "d_hifft128Tx"	);
	xfft_kernel_sao( &p[0], XFFT_AM_P_P_P_I );
	xfft_kernel_sao( &p[1], XFFT_AM_P_P_P_I );
	xfft_kernel_sao( &p[2], XFFT_AM_P_P_P );
	xfft_kernel_sao( &p[3], XFFT_AM_P_P_P );
	xfft_kernel_sep_i32( &p[0], 3, 128 );
	xfft_kernel_sep_i32( &p[1], 3, 128 );
}
static void __hffte15_bk( xfft_kernel_t* const p, CUmodule module, int bat )
{
	xfft_create_kernel( &p[0], module, "d_hfft128Sx"	);
	xfft_create_kernel( &p[1], module, "d_hifft128Sx"	);
	xfft_create_kernel( &p[2], module, "d_hfft256Tx"	);
	xfft_create_kernel( &p[3], module, "d_hifft256Tx"	);
	xfft_kernel_sao( &p[0], XFFT_AM_P_P_P_I );
	xfft_kernel_sao( &p[1], XFFT_AM_P_P_P_I );
	xfft_kernel_sao( &p[2], XFFT_AM_P_P_P_I );
	xfft_kernel_sao( &p[3], XFFT_AM_P_P_P_I );
	xfft_kernel_sep_i32( &p[0], 3, 256 );
	xfft_kernel_sep_i32( &p[1], 3, 256 );
	xfft_kernel_sep_i32( &p[2], 3, 128 );
	xfft_kernel_sep_i32( &p[3], 3, 128 );
}
static void __hffte16_bk( xfft_kernel_t* const p, CUmodule module, int bat )
{
	xfft_create_kernel( &p[0], module, "d_hfft256Sx"	);
	xfft_create_kernel( &p[1], module, "d_hifft256Sx"	);
	xfft_create_kernel( &p[2], module, "d_hfft256Tx"	);
	xfft_create_kernel( &p[3], module, "d_hifft256Tx"	);
	xfft_kernel_sao( &p[0], XFFT_AM_P_P_P );
	xfft_kernel_sao( &p[1], XFFT_AM_P_P_P );
	xfft_kernel_sao( &p[2], XFFT_AM_P_P_P_I );
	xfft_kernel_sao( &p[3], XFFT_AM_P_P_P_I );
	xfft_kernel_sep_i32( &p[2], 3, 256 );
	xfft_kernel_sep_i32( &p[3], 3, 256 );
}
static void (*p_bk[])( xfft_kernel_t* const, CUmodule, int )=
{
	__hffte01_bk,
	__hffte02_bk,
	__hffte03_bk,
	__hffte04_bk,
	__hffte05_bk,
	__hffte06_bk,
	__hffte07_bk,
	__hffte08_bk,
	__hffte09_bk,
	__hffte10_bk,
	__hffte11_bk,
	__hffte12_bk,
	__hffte13_bk,
	__hffte14_bk,
	__hffte15_bk,
	__hffte16_bk
};
static void __hffte01_sgl( xfft_kernel_t* const p, int bat )
{
	unsigned int nb, nt;
	nb=(bat<128)?1:((bat+127)>>7);
	nt=(bat<128)?nAFFI(bat,32):128;
	xfft_kernel_sgl( &p[0], nb, 1 );
	xfft_kernel_sbl( &p[0], nt, 1 );
	xfft_kernel_sgl( &p[1], nb, 1 );
	xfft_kernel_sbl( &p[1], nt, 1 );
}
static void __hffte02_sgl( xfft_kernel_t* const p, int bat )
{
	unsigned int nb, nt;
	nb=(bat<128)?1:((bat+127)>>7);
	nt=(bat<128)?nAFFI(bat,32):128;
	xfft_kernel_sgl( &p[0], nb, 1 );
	xfft_kernel_sbl( &p[0], nt, 1 );
	xfft_kernel_sgl( &p[1], nb, 1 );
	xfft_kernel_sbl( &p[1], nt, 1 );
}
static void __hffte03_sgl( xfft_kernel_t* const p, int bat )
{
	unsigned int nb, nt;
	nb=(bat<128)?1:((bat+127)>>7);
	nt=(bat<128)?nAFFI(bat,32):128;
	xfft_kernel_sgl( &p[0], nb, 1 );
	xfft_kernel_sbl( &p[0], nt, 1 );
	xfft_kernel_sgl( &p[1], nb, 1 );
	xfft_kernel_sbl( &p[1], nt, 1 );
}
static void __hffte04_sgl( xfft_kernel_t* const p, int bat )
{
	unsigned int nb, nt;
	nb=(bat<128)?1:((bat+127)>>7);
	nt=(bat<128)?nAFFI(bat,32):128;
	xfft_kernel_sgl( &p[0], nb, 1 );
	xfft_kernel_sbl( &p[0], nt, 1 );
	xfft_kernel_sgl( &p[1], nb, 1 );
	xfft_kernel_sbl( &p[1], nt, 1 );
}
static void __hffte05_sgl( xfft_kernel_t* const p, int bat )
{
	unsigned int nb, dy, smemnb;
	nb=(bat<32)?1:((bat+31)>>5);
	dy=(bat<32)?(nAFFI(bat<<2,32)>>2):32;
	smemnb=dy*40*sizeof(float);
	xfft_kernel_sgl( &p[0], nb, 1 );
	xfft_kernel_sbl( &p[0], 8, dy );
	p[0].smemnb=smemnb;
	xfft_kernel_sgl( &p[1], nb, 1 );
	xfft_kernel_sbl( &p[1], 8, dy );
	p[1].smemnb=smemnb;
}
static void __hffte06_sgl( xfft_kernel_t* const p, int bat )
{
	unsigned int nb, dy, smemnb;
	nb=(bat<16)?1:((bat+15)>>4);
	dy=(bat<16)?(nAFFI(bat<<3,32)>>3):128;
	smemnb=dy*72*sizeof(float);
	xfft_kernel_sgl( &p[0], nb, 1 );
	xfft_kernel_sbl( &p[0], 8, dy );
	p[0].smemnb=smemnb;
	xfft_kernel_sgl( &p[1], nb, 1 );
	xfft_kernel_sbl( &p[1], 8, dy );
	p[1].smemnb=smemnb;
}
static void __hffte07_sgl( xfft_kernel_t* const p, int bat )
{
	unsigned int nb, dy, smemnb;
	nb=(bat<16)?1:((bat+15)>>4);
	dy=(bat<16)?(nAFFI(bat<<3,32)>>3):16;
	smemnb=dy*168*sizeof(float);
	xfft_kernel_sgl( &p[0], nb, 1 );
	xfft_kernel_sbl( &p[0], 8, dy );
	p[0].smemnb=smemnb;
	xfft_kernel_sgl( &p[1], nb, 1 );
	xfft_kernel_sbl( &p[1], 8, dy );
	p[1].smemnb=smemnb;
}
static void __hffte08_sgl( xfft_kernel_t* const p, int bat )
{
	unsigned int nb, dy, smemnb;
	nb=(bat<16)?1:((bat+15)>>4);
	dy=(bat<16)?(nAFFI(bat<<4,32)>>4):16;
	smemnb=dy*272*sizeof(float);
	xfft_kernel_sgl( &p[0], nb,  1 );
	xfft_kernel_sbl( &p[0], 16, dy );
	p[0].smemnb=smemnb;
	xfft_kernel_sgl( &p[1], nb,  1 );
	xfft_kernel_sbl( &p[1], 16, dy );
	p[1].smemnb=smemnb;
}
static void __hffte09_sgl( xfft_kernel_t* const p, int bat )
{
	xfft_kernel_sgl( &p[0], bat, 1 );
	xfft_kernel_sbl( &p[0],  64, 1 );
	xfft_kernel_sgl( &p[1], bat, 1 );
	xfft_kernel_sbl( &p[1],  64, 1 );
}
static void __hffte10_sgl( xfft_kernel_t* const p, int bat )
{
	xfft_kernel_sgl( &p[0], bat, 1 );
	xfft_kernel_sbl( &p[0],  64, 1 );
	xfft_kernel_sgl( &p[1], bat, 1 );
	xfft_kernel_sbl( &p[1],  64, 1 );
}
static void __hffte11_sgl( xfft_kernel_t* const p, int bat )
{
	xfft_kernel_sgl( &p[0], bat, 1 );
	xfft_kernel_sbl( &p[0], 128, 1 );
	xfft_kernel_sgl( &p[1], bat, 1 );
	xfft_kernel_sbl( &p[1], 128, 1 );
}
static void __hffte12_sgl( xfft_kernel_t* const p, int bat )
{
	xfft_kernel_sgl( &p[0], bat, 1 );
	xfft_kernel_sbl( &p[0], 256, 1 );
	xfft_kernel_sgl( &p[1], bat, 1 );
	xfft_kernel_sbl( &p[1], 256, 1 );
}
static void __hffte13_sgl( xfft_kernel_t* const p, int bat )
{
	xfft_kernel_sgl( &p[0], bat, 1 );
	xfft_kernel_sbl( &p[0], 512, 1 );
	xfft_kernel_sgl( &p[1], bat, 1 );
	xfft_kernel_sbl( &p[1], 512, 1 );
}
static void __hffte14_sgl( xfft_kernel_t* const p, int bat )
{
	xfft_kernel_sgl( &p[0], 4, bat	);
	xfft_kernel_sbl( &p[0], 32, 8	);
	xfft_kernel_sgl( &p[1], 4, bat	);
	xfft_kernel_sbl( &p[1], 32, 8	);
	xfft_kernel_sgl( &p[2], 16, bat );
	xfft_kernel_sbl( &p[2], 8, 8	);
	xfft_kernel_sgl( &p[3], 16, bat );
	xfft_kernel_sbl( &p[3], 8, 8	);
}
static void __hffte15_sgl( xfft_kernel_t* const p, int bat )
{
	xfft_kernel_sgl( &p[0], 8, bat );
	xfft_kernel_sbl( &p[0], 32, 8  );
	xfft_kernel_sgl( &p[1], 8, bat );
	xfft_kernel_sbl( &p[1], 32, 8  );
	xfft_kernel_sgl( &p[2], 8, bat );
	xfft_kernel_sbl( &p[2], 16, 16 );
	xfft_kernel_sgl( &p[3], 8, bat );
	xfft_kernel_sbl( &p[3], 16, 16 );
}
static void __hffte16_sgl( xfft_kernel_t* const p, int bat )
{
	xfft_kernel_sgl( &p[0], 8, bat );
	xfft_kernel_sbl( &p[0], 32, 16 );
	xfft_kernel_sgl( &p[1], 8, bat );
	xfft_kernel_sbl( &p[1], 32, 16 );
	xfft_kernel_sgl( &p[2], 16, bat);
	xfft_kernel_sbl( &p[2], 16, 16 );
	xfft_kernel_sgl( &p[3], 16, bat);
	xfft_kernel_sbl( &p[3], 16, 16 );
}
static void (*p_sgl[])( xfft_kernel_t* const, int )=
{ 
	__hffte01_sgl,
	__hffte02_sgl, 
	__hffte03_sgl, 
	__hffte04_sgl, 
	__hffte05_sgl, 
	__hffte06_sgl, 
	__hffte07_sgl, 
	__hffte08_sgl, 
	__hffte09_sgl,
	__hffte10_sgl,
	__hffte11_sgl,
	__hffte12_sgl,
	__hffte13_sgl,
	__hffte14_sgl,
	__hffte15_sgl,
	__hffte16_sgl
};

static __forceinline void hfft_bk( xfft_kernel_t* const p, CUmodule module, int tex, int i )
{
	p_bk[i]( p, module, tex );
}
static __forceinline void hfft_sgl( xfft_kernel_t* const p, int bat, int i )
{
	p_sgl[i]( p, bat );
}
void hfft_bki( xfft_kernel_t* const __restrict p, CUtexref* __restrict p_tex, CUmodule module, CUdeviceptr d_RF, int nk, int bat, int e )
{
	int i, n, use_tex;
	n=(1<<27)/((1<<(e+1))*bat);
	use_tex=(e==8)&(n>0);
	if(use_tex){
		cuModuleGetTexRef( p_tex, module, "d_tex" );
		cuTexRefSetFormat( *p_tex, CU_AD_FORMAT_FLOAT, 2 );
		cuTexRefSetFlags( *p_tex, CU_TRSF_READ_AS_INTEGER );
	}
	hfft_bk( p, module, use_tex, e );
	hfft_sgl( p, bat, e );
	for( i=0; i<nk; ++i )
	{
		if(e>3){
			xfft_kernel_sep_ptr( &p[i], 2-use_tex, d_RF );
		}
		if(e<8){
			xfft_kernel_sep_i32( &p[i], 2+(e>3), bat );
		}
	}
}