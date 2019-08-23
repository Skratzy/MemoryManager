#ifndef _MEMMNGR_DEFINES_
#define _MEMMNGR_DEFINES_

#include <iostream>
#include <assert.h>
#include <malloc.h>

constexpr auto ARCH_BYTESIZE = sizeof(void*);

#define MEMMNGR_ASSERT(s) assert(s)

/*
	s: Size in bytes
*/
#define MEMMNGR_MALLOC(s) malloc(s)

/*
	s: Size in bytes
*/
#define MEMMNGR_MALLOC_POOL_ALLOC(s)
constexpr auto PERSISTENT_STACK_INDEX = 0;
constexpr auto FUNCTION_STACK_INDEX = 1;

#define MEMMNGR_FREE(s) free(s)
#define MEMMNGR_DELETE(s) delete s

/*
	s: Debug message - to be printed
	l: Severity level
		0 -> print the message
		1 -> print the message and abort
*/
/*#define MEMMNGR_DEBUG_MESSAGE(s, l) { \
	HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE); \
	CONSOLE_SCREEN_BUFFER_INFO conScrBufInf; \
	GetConsoleScreenBufferInfo(stdHandle, &conScrBufInf); \
	switch(l) { \
	case 0: \
		SetConsoleTextAttribute(stdHandle, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY); \
		std::cerr << "WARNING: " << s << std::endl; \
		SetConsoleTextAttribute(stdHandle, conScrBufInf.wAttributes); \
		break; \
	case 1:\
		SetConsoleTextAttribute(stdHandle, BACKGROUND_RED | BACKGROUND_INTENSITY);\
		std::cerr << "ERROR: " << s << std::endl;\
		SetConsoleTextAttribute(stdHandle, conScrBufInf.wAttributes);\
		abort();\
		break;\
	default: break;\
}}*/

/*
	s: Debug message - to be printed
	l: Severity level
		0 -> print the message
		1 -> print the message and abort
*/
#define MEMMNGR_DEBUG_MESSAGE(s, l) { \
	switch(l) { \
	case 0: \
		std::cerr << "WARNING: " << s << std::endl; \
		break; \
	case 1:\
		std::cerr << "ERROR: " << s << std::endl;\
		throw(s);\
		break;\
	default: break;\
}}

#endif //_MEMMNGR_DEFINES_