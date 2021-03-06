#ifndef __xfft_h__
#define __xfft_h__

#include<cuda.h>
#pragma comment(lib,"cuda.lib")

#if defined(_MSC_VER)&&(defined(_WIN32)||defined(_WIN64))
	#if defined(_DLL)||defined(_WINDLL)
		#define XFFTAPIENTRY __declspec(dllexport)
	#else
		#define XFFTAPIENTRY __declspec(dllimport)
	#endif
	#if	defined(_M_X64)||defined(_M_AMD64)||defined(__x86_64)||defined(_M_IA64)||defined(__LP64__)
		#define XFFTAPICALL
	#else
		#define XFFTAPICALL __stdcall
	#endif
#else
	#define XFFTAPIENTRY
	#define XFFTAPICALL
#endif

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum xfftStatus{
	xfftSuccess=0,
	xfftErrorInvalidDriver,
	xfftErrorInvalidDevice,
	xfftErrorInvalidValue,
	xfftErrorOutOfMemory,
	xfftErrorOutOfDeviceMemory,
	xfftErrorOutMaxSizeSupported
} xfftStatus_t;

typedef struct __xfftOp*	xfftOp;

XFFTAPIENTRY xfftStatus_t	XFFTAPICALL xfftInit();
XFFTAPIENTRY xfftStatus_t	XFFTAPICALL xfftSetDevice( int );
XFFTAPIENTRY xfftStatus_t	XFFTAPICALL xfftCreateOp1d( xfftOp*, int, int, int );
XFFTAPIENTRY xfftStatus_t	XFFTAPICALL xfftCreateOp2d( xfftOp*, int, int, int, int );
XFFTAPIENTRY xfftStatus_t	XFFTAPICALL xfftCreateOp3d( xfftOp*, int, int, int, int, int );
XFFTAPIENTRY xfftStatus_t	XFFTAPICALL xfftBindStream( xfftOp, CUstream );
XFFTAPIENTRY xfftStatus_t	XFFTAPICALL xfftExec( xfftOp, CUdeviceptr*, CUdeviceptr, CUdeviceptr, int );
XFFTAPIENTRY xfftStatus_t	XFFTAPICALL xfftDestroy( xfftOp );
XFFTAPIENTRY xfftStatus_t	XFFTAPICALL xfftExit();

#ifdef __cplusplus
}
#endif

#endif