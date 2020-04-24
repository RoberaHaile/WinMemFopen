#pragma once
#include <Windows.h>
#include <mmiscapi.h >
#pragma comment(lib, "Winmm.lib")

typedef struct _handle_struct{
	HMMIO			fHandle;
	MMIOINFO		*mmmioInfo; 
} handle_struct; 
