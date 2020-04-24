/* Wrapper functions */

#include <stdio.h>
#include "mem.h"
#include "WinMemFopen.h"


handle_struct* FsOpenMem (
	void *buffer,	// Buffer in memory to open as a file 
	UINT bufferSz	// Size of buffer 
					// Returns a pointer to handle_struct object representing the given buffer on sucess and NULL on failure. 
	) 
{
		if (!bufferSz) {
#ifdef DEBUG 
			printf("FsOpenMem: bufferSz is null\n"); 
#endif
			return NULL; 
		}
		if (!buffer) {
#ifdef DEBUG 
			printf("FsOpenMem: buffer is null\n");
#endif
			return NULL;
		}
		return OpenFileInMem((unsigned char*)buffer, bufferSz); 
}
	

LONG FsReadFromMemH (
	handle_struct* myHandleStruct,	// A pointer to a handle_struct object representing a block of memory, returned by FsOpenMem() 
	unsigned char* buffer,			// Buffer to read into  	
	UINT readBytes					// Number of bytes to read 
									// Returns number of bytes read on success, 0 if end-of-file is reached, and -1 on error. 
	) 
{
	if (!myHandleStruct) {
#ifdef DEBUG 
		printf("FsReadFromMem: Given handle_struct object is null\n");
#endif
		return -1; 
	}
	return ReadFromMem(myHandleStruct->fHandle, buffer, readBytes); 
}


LONG FsWriteToMemH (
	handle_struct* myHandleStruct,	// A pointer to a handle_struct representing a block of memory, returned by FsOpenMem() 
	unsigned char* buffer,			// A buffer from which bytes are read to be written to the memory file handle 	
	UINT writeBytes					// Number of bytes to write 
									// Returns the number of bytes written to the mem block represented by the handle_struct object, -1 on error. 
	) 
{
	if (!myHandleStruct) {
#ifdef DEBUG 
		printf("FsWriteToMem: Given handle_struct object is null\n");
#endif
		return -1;
	}
	return WriteToMem(myHandleStruct->fHandle, buffer, writeBytes); 
}



LONG FsSeekMemH (
	handle_struct* myHandleStruct,	// A pointer to a handle_struct representing a block of memory, returned by FsOpenMem()
	LONG offset,					// New offset to move fHandle to 
	int iOrigin						// SEEK_SET, SEEK_CUR, SEEK_END: from the beginning, current position and end of the fhandle respectively. 
									// Returns the new file position, in bytes, relative to the beginning of the file, -1 on error.


	)
{
	if (!myHandleStruct) {
#ifdef DEBUG 
		printf("FsSeekMemH: Given handle_struct object is null\n");
#endif
		return -1;
	}
	return SeekFromMem(myHandleStruct, offset, iOrigin);
}


BOOL FsCloseM (
	handle_struct** myHandleStruct	// A pointer to a handle_struct representing a block of memory, returned by FsOpenMem()
									// Returns true on success and false on failure. 
	)
{
	BOOL result = FALSE; 
	if (!*myHandleStruct) {
#ifdef DEBUG 
		printf("FsCloseMem: Given handle_struct object is null\n");
#endif
		return -1;
	}
	result = CloseFileInMem(myHandleStruct); 
	if (*myHandleStruct) *myHandleStruct = NULL;
	return result; 
}










