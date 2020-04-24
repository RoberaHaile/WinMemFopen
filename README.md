# WinMemFopen

## Table of content 
###   Introduction 
###   Use cases 
###   How to use 
###   Examples
###   License 


## Introduction 
WinMemFOpen is a proof-of-concept implementation that enables treating memory buffers as files, and perform file I/O operations as if they were disk-based files. 

Windows doesn't have an easy API which is equivalent to Linux's fmemopen(), which opens a memory buffer or a string as a stream and perform file I/0 on it. 

One solution is to implement [fmemopen()](http://man7.org/linux/man-pages/man3/fmemopen.3.html) along with open, close, read, write and seek functions.
Another Solution is to use existing Windows APIs and re-purpose them for our needs. This projects follows the later. 

WinMemFopen leverages a set of memory file I/O API available in Windows, which are primarily used for multimedia file operations. For more information, see [Performing memory file I/0](https://docs.microsoft.com/en-us/windows/win32/multimedia/performing-memory-file-i-o). 

## Use cases 
One might use WinMemFopen for any purpose which requires treating memory blocks as a file, such as dealing with large memory buffers, working with streams (such as audio or video applications), or for performance reasons where writing and reading to a disk repeatedly is to be avoided.  

It can also be used to avoid using standard WinAPI file I/O calls such as CreateFile, ReadFile, and WriteFile to evade monitoring for such API calls. In addition, it might come handy when avoiding touching the disk is desirable :). Furthermore, it can be extended with encryption and compression cabapilities to meet additional needs. 

## How to use 
Just include "WinMemFopen.h" in your project and call the functions. 
Add "#define DEBUG 1" in mem.h to enable printing debugging information in functions. 

## Example
The file "example.c" shows usage of the functions.

## License 
The project is licensed under GPLv2.0 license. 