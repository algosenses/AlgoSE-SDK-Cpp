#ifndef ALGOSE_UTILS_H
#define ALGOSE_UTILS_H

#include <string.h>
#include <thread>
#include <cassert>
#include "Defines.h"

namespace AlgoSE
{

#ifdef __PLATFORM_WINDOWS__

std::wstring s2ws(const std::string& s);
#define getTickCount  GetTickCount
#define snprintf      _snprintf
#include <direct.h>
#define GetCurrentDir _getcwd

#define LIBRARY_POINTER_TYPE     HMODULE
#define GET_PROC_ADDR            GetProcAddress
#define LOAD_LIBRARY(X)          LoadLibrary(X)
#define FREE_LIBRARY             FreeLibrary

#else

#define s2ws(s) (s)
#define stricmp  strcasecmp
#define _stricmp strcasecmp
#define strnicmp strncasecmp
#define _snprintf snprintf
#define strncpy_s strncpy
unsigned long getTickCount();
#define GetCurrentDir getcwd

#include <dlfcn.h>
#define LIBRARY_POINTER_TYPE     void*
#define GET_PROC_ADDR            dlsym
#define LOAD_LIBRARY(X)          dlopen(X, RTLD_NOW)
#define FREE_LIBRARY             dlclose

#endif

int _snprintf_s(
   char *buffer,
   size_t sizeOfBuffer,
   size_t count,
   const char *format,
   ...
);

ALGOSE_API char* printInt(int num, char out[]);

void SetThreadName(std::thread* thread, const char* threadName);
void SetThreadName(const char* threadName);

class ALGOSE_API hiresclock
{
public:
    // Returns the number of 10/th microseconds 
    // (or 100-nanoseconds intervals if you will) since epoch (UTC).
    static std::uint64_t now(); // in 0.1us
    static void timestamping(void* addr);
    static std::uint64_t getTimeDelta(std::uint64_t start);
};

} // namespace AlgoSE

#endif // ALGOSE_UTILS_H