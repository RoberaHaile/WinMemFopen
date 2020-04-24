#pragma once 
#include "memstruct.h"

handle_struct* OpenFileInMem(unsigned char* buffer, UINT bufferSz); 
LONG ReadFromMem(HMMIO fHandle, unsigned char* buffer, LONG bytesToread); 
LONG WriteToMem(HMMIO fHandle, unsigned char* buffer, LONG bytesToWrite); 
LONG SeekFromMem(handle_struct* myHandleStruct, LONG offset, int iOrigin); 
BOOL CloseFileInMem(handle_struct** myHandleStruct); 


#define DEBUG 1 