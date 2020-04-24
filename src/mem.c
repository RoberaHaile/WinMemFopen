#include <stdio.h>
#include "mem.h" 

BOOL DestroyHandleStruct(handle_struct *myHandleStruct) {
	if (myHandleStruct) {
		if (myHandleStruct->mmmioInfo) {
			if (myHandleStruct->mmmioInfo->pchBuffer) {
				myHandleStruct->mmmioInfo->pchBuffer = NULL; 
			}
			free(myHandleStruct->mmmioInfo); 
			myHandleStruct->mmmioInfo = NULL; 
		}
		free(myHandleStruct);
		myHandleStruct = NULL; 
		return TRUE; 
	}
	return FALSE; 
}


BOOL InitHandleStruct(handle_struct *myHandleStruct, unsigned char* buffer, UINT bufferSz) {
	if (!myHandleStruct) {

#ifdef DEBUG 
		printf("null handle_sruct\n");
#endif
		return FALSE;
	}

	if (!myHandleStruct->mmmioInfo) {

#ifdef DEBUG 
		printf("null mmioinfo struct\n");
#endif
		return FALSE;
	}
	myHandleStruct->fHandle = NULL; 
	myHandleStruct->mmmioInfo->dwFlags = 0;
	myHandleStruct->mmmioInfo->pIOProc = NULL;
	myHandleStruct->mmmioInfo->wErrorRet = 0;
	myHandleStruct->mmmioInfo->htask = NULL;
	myHandleStruct->mmmioInfo->pchNext = NULL;
	myHandleStruct->mmmioInfo->pchEndRead = NULL;
	myHandleStruct->mmmioInfo->pchEndWrite = NULL;
	myHandleStruct->mmmioInfo->lBufOffset = 0;
	myHandleStruct->mmmioInfo->lDiskOffset = 0;
	myHandleStruct->mmmioInfo->dwReserved1 = 0;
	myHandleStruct->mmmioInfo->dwReserved2 = 0;
	myHandleStruct->mmmioInfo->hmmio = NULL;
	myHandleStruct->mmmioInfo->adwInfo[0] = 0;
	myHandleStruct->mmmioInfo->adwInfo[1] = 0;
	myHandleStruct->mmmioInfo->adwInfo[2] = 0;
	myHandleStruct->mmmioInfo->adwInfo[3] = 0;

	myHandleStruct->mmmioInfo->pchBuffer = buffer;
	myHandleStruct->mmmioInfo->cchBuffer = bufferSz;
	myHandleStruct->mmmioInfo->fccIOProc = FOURCC_MEM;
	return TRUE;
}


handle_struct* OpenFileInMem(unsigned char *buffer, UINT bufferSz) {
	HMMIO handleMe = NULL;
	handle_struct* myHandleStruct = (handle_struct*)malloc(sizeof(handle_struct));
	myHandleStruct->mmmioInfo = (MMIOINFO*)malloc(sizeof(MMIOINFO)); 
	
	if (!InitHandleStruct(myHandleStruct, buffer, bufferSz)) {
#ifdef DEBUG
		printf("handle_struct initialization failed\n");
#endif 
		DestroyHandleStruct(myHandleStruct); 
		return NULL;
	}

	if ((handleMe = mmioOpen(NULL, myHandleStruct->mmmioInfo, MMIO_READWRITE)) == NULL) {
#ifdef DEBUG
		printf("%d: \n", myHandleStruct->mmmioInfo->wErrorRet);
#endif
		DestroyHandleStruct(myHandleStruct); 
		return NULL;
	}
	myHandleStruct->fHandle = handleMe; 
	return myHandleStruct;
}

LONG ReadFromMem(HMMIO fHandle, unsigned char *buffer, LONG bytesToread) {
	LONG result = -1; 
	result = mmioRead(fHandle, buffer, bytesToread);
	if (result == 0) {
#ifdef DEBUG 
		printf("ReadFromMem: End-of-file reached\n"); 
#endif 
	}
	return result; 
}

LONG WriteToMem(HMMIO fHandle, unsigned char* buffer, LONG bytesToWrite) {
	return mmioWrite(fHandle, buffer, bytesToWrite);	
}

LONG SeekFromMem(handle_struct* myHandleStruct, LONG offset, int iOrigin) { 
	LONG currentOffset = 0; 
	UINT seekEnd = 0; 
	seekEnd = myHandleStruct->mmmioInfo->cchBuffer;
	currentOffset = mmioSeek(myHandleStruct->fHandle, 0, SEEK_CUR);

	/* Seeking to an invalid location in the file, such as past the end of the file, might not cause mmioSeek() to return an error, 
	 * but it might cause subsequent I/O operations on the file to fail. 
	 * So we have to implement our own check so  that it doesn't happen. */
	if (((currentOffset + offset) >= (LONG)seekEnd) || (currentOffset + offset < 0)) {
#ifdef DEBUG
		printf("SeekFromMem: Invalid seek offset given\n"); 
#endif 
		return -1; 
	}

	return mmioSeek(myHandleStruct->fHandle, offset, iOrigin); 
}


BOOL CloseFileInMem(handle_struct** myHandleStruct) {
	handle_struct* hs = *myHandleStruct; 
	if (hs) {
		if (!mmioClose(hs->fHandle, MMIO_FHOPEN)) { // mmioclose() returns 0 on sucess
			DestroyHandleStruct(hs);
			hs = NULL; 
			return TRUE;
		}
	}
	return FALSE; 
}

