
#include <Windows.h>
#include <stdio.h>
#include "WinMemFopen.h"

int main() {
	char fileBuffer[] = "u are gonna miss my love, by lou rawls. XXXX"; 
	handle_struct* trialHandle = NULL;
	char readBuf[5]; 
	char*writeStr = "FFFFF"; 
	LONG newOffset = 0; 

	trialHandle = FsOpenMem(fileBuffer, 44); 
	memset(readBuf, 0, 5); 
	FsReadFromMemH(trialHandle, readBuf, 5);
	memset(readBuf, 0, 5);
	FsReadFromMemH(trialHandle, readBuf, 5);
	newOffset = FsSeekMemH(trialHandle, 3, SEEK_CUR); 
	FsWriteToMemH(trialHandle, (unsigned char*)writeStr, 5);
	FsCloseM(&trialHandle); 

	return 0; 
}
