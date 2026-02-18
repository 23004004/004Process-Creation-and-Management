#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#define NUM_CHILDREN 3

int main()
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi[NUM_CHILDREN];

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);


    DWORD ppid = GetCurrentProcessId();
    printf("Parent Process: PID=%lu\n", ppid);

    for (int i = 0; i < NUM_CHILDREN; i++)
    {
        ZeroMemory(&pi[i], sizeof(PROCESS_INFORMATION));

        char cmdLine[100];
        snprintf(cmdLine, sizeof(cmdLine),
                 "os_child.exe %lu %d",
                 ppid, i + 1);

        if (!CreateProcessA(
                NULL,
                cmdLine,
                NULL,
                NULL,
                FALSE,
                0,
                NULL,
                NULL,
                &si,
                &pi[i]))
        {
            printf("CreateProcess failed (%lu).\n", GetLastError());
            return 1;
        }
    }

    for (int i = 0; i < NUM_CHILDREN; i++)
    {
        WaitForSingleObject(pi[i].hProcess, INFINITE);
        CloseHandle(pi[i].hProcess);
        CloseHandle(pi[i].hThread);
    }

    return 0;
}