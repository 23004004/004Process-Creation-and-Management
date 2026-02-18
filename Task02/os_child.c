#include <windows.h>
#include <stdio.h>
#include <tchar.h>

int main(int argc, char *argv[]) {
    DWORD pid = GetCurrentProcessId();

    if (argc > 1)
    {
        DWORD ppid = strtoul(argv[1], NULL, 10);
        printf("Child Process: PID=%lu, Parent PID=%lu\n", pid, ppid);
    }
    else
    {
        printf("Child Process: PID=%lu\n", pid);
    }
    

    return 0;
}
