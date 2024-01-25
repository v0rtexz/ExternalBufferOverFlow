#include <windows.h>

// Trigger our buffer overflow
extern "C" __declspec(dllexport) int trigger_buffer_overflow()
{
    char buff[10] = {0};

    strcpy(buff, "This String Will Overflow the Buffer");

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE;
}
