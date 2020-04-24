#pragma once
#include "memstruct.h"

handle_struct* FsOpenMem(void* buffer, UINT bufferSz);
LONG FsReadFromMemH(handle_struct* myHandleStruct, unsigned char* buffer, UINT readBytes); 
LONG FsWriteToMemH(handle_struct* myHandleStruct, unsigned char* buffer, UINT writeBytes);
LONG FsSeekMemH(handle_struct* myHandleStruct, LONG offset, int iOrigin); 
BOOL FsCloseM(handle_struct** myHandleStruct); 