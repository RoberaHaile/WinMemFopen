
#include <Windows.h>
#include <stdio.h>
#include "WinMemFopen.h"

int main() {
	/* targetBuffer[] will be the memory buffer which will be opened as a file. 
	* readBuf[] will be our buffer into which will read from our target buffer 
	* writeBuf[] will be our string which we will write into our target buffer. 
	*/ 

	char targetBuffer[] = "u are gonna miss my love, by lou rawls. XXXX"; 
	handle_struct* myHandle = NULL;
	char readBuf[5]; 
	char*writeStr = "FFFFF"; 
	LONG newOffset = 0; 

	myHandle = FsOpenMem(targetBuffer, 44); 				// open targetBuffer[] and represent it with myHandle->fHandle.
	memset(readBuf, 0, 5);		 
	FsReadFromMemH(myHandle, readBuf, 5);					// readBuf will be "u are". 
	memset(readBuf, 0, 5);
	FsReadFromMemH(myHandle, readBuf, 5);					// reaBuf will be " gonn". 
	newOffset = FsSeekMemH(myHandle, 3, SEEK_CUR); 			// myHandle->fHandle new offset will be 13 relative from the beginning. 
	FsWriteToMemH(myHandle, (unsigned char*)writeStr, 5);	// targetBuffer[] will be "u are gonna mFFFFFy love, by lou rawls. XXXX"
	FsCloseM(&myHandle); 									// close and free myHandle struct and its member myHandle->mmioInfo. 

	return 0; 
}
