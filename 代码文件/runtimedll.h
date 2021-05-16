#ifndef RUNTIMEDLL_H
#define RUNTIMEDLL_H

#include <windows.h>
#include <string>

#define COMMAND_NOT_EXEC  1
#define COMPILE_SUCCESS   0
#define COMPILE_FAIL     -1

namespace RuntimeDll {
    int compileDll(std::string dllname);
    HINSTANCE getDll(std::string dllname);
    FARPROC getFirstFuncInDll(HINSTANCE hinst);
};

#endif // RUNTIMEDLL_H
