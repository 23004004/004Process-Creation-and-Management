#include <windows.h>
#include <stdio.h>
#include <tchar.h>

int main(int argc, char *argv[]) {
    DWORD pid = GetCurrentProcessId();

    if (argc > 2)
    {
        DWORD ppid = strtoul(argv[1], NULL, 10);
        int childNumber = atoi(argv[2]);
        printf("Child %d: PID=%lu, Parent PID=%lu\n", childNumber, pid, ppid);
    }
    else
    {
        printf("Child Process: PID=%lu\n", pid);
    }
    

    return 0;
}
