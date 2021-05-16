#include "runtimedll.h"
using std::string;

int RuntimeDll::compileDll(std::string dllname)
{
    static const int maxlen = 100;

    // init structs
    STARTUPINFO info;
    PROCESS_INFORMATION procInfo;
    ZeroMemory(&info, sizeof(info));
    info.cb = sizeof(info);
    ZeroMemory(&procInfo, sizeof(procInfo));

    // init command lines
    string c1 = "g++ -c " + dllname + ".cpp";
    string c2 = "g++ -shared -o " + dllname + ".dll " + dllname + ".o";
    TCHAR cmd1[maxlen], cmd2[maxlen];
    std::copy(c1.begin(), c1.end(), cmd1);
    std::copy(c2.begin(), c2.end(), cmd2);
    cmd1[c1.size()] = cmd2[c2.size()] = TEXT('\0');

    // execute g++ command
    DWORD exitCode;
    // cmd1
    if (!CreateProcess(NULL, cmd1, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &info, &procInfo))
        return COMMAND_NOT_EXEC;
    // Wait until child process exits.
    WaitForSingleObject(procInfo.hProcess, INFINITE);
    GetExitCodeProcess(procInfo.hProcess, &exitCode);
    // Close process and thread handles.
    CloseHandle(procInfo.hProcess);
    CloseHandle(procInfo.hThread);
    if (exitCode)       // if fail
        return COMPILE_FAIL;
    // cmd2
    if (!CreateProcess(NULL, cmd2, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &info, &procInfo))
        return COMMAND_NOT_EXEC;
    // Wait until child process exits.
    WaitForSingleObject(procInfo.hProcess, INFINITE);
    GetExitCodeProcess(procInfo.hProcess, &exitCode);
    // Close process and thread handles.
    CloseHandle(procInfo.hProcess);
    CloseHandle(procInfo.hThread);
    if (exitCode)       // if fail
        return COMPILE_FAIL;
    // compile success
    return COMPILE_SUCCESS;
}

HINSTANCE RuntimeDll::getDll(std::string dllname)
{
    static const int maxlen = 100;
    HINSTANCE hinst = NULL;
    TCHAR libname[maxlen];
    std::copy(dllname.begin(), dllname.end(), libname);
    libname[dllname.size()] = TEXT('\0');
    // open dll
    hinst = LoadLibrary(libname);
    // if LoadLibrary fails, hinst remains NULL
    return hinst;
}

FARPROC RuntimeDll::getFirstFuncInDll(HINSTANCE hinst)
{
    return GetProcAddress(hinst, MAKEINTRESOURCEA(1));
}