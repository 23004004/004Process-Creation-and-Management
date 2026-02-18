#include <windows.h>
#include <stdio.h>

void CreateChildProcess(void);

HANDLE hReadPipe = NULL;
HANDLE hWritePipe = NULL;

int main()
{
    SECURITY_ATTRIBUTES saAttr;

    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    if (!CreatePipe(&hReadPipe, &hWritePipe, &saAttr, 0)) {
        printf("CreatePipe failed\n");
        return 1;
    }

    SetHandleInformation(hWritePipe, HANDLE_FLAG_INHERIT, 0);

    CreateChildProcess();

    return 0;
}

void CreateChildProcess(void)
{
    PROCESS_INFORMATION piProcInfo;
    STARTUPINFOA siStartInfo;
    BOOL bSuccess = FALSE;
    char message[] = "Hello from Parent";

    ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));
    ZeroMemory(&siStartInfo, sizeof(STARTUPINFOA));

    siStartInfo.cb = sizeof(STARTUPINFOA);

    siStartInfo.hStdInput  = hReadPipe;
    siStartInfo.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    siStartInfo.hStdError  = GetStdHandle(STD_ERROR_HANDLE);
    siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

    // Crear proceso hijo
    bSuccess = CreateProcessA(
        "os_child.exe",
        NULL,
        NULL,
        NULL,
        TRUE,   // permitir herencia
        0,
        NULL,
        NULL,
        &siStartInfo,
        &piProcInfo);

    if (!bSuccess) {
        printf("CreateProcess failed\n");
        return;
    }

    CloseHandle(hReadPipe);

    printf("Parent Process: Writing \"%s\"\n", message);

    DWORD bytesWritten;
    WriteFile(hWritePipe, message, sizeof(message), &bytesWritten, NULL);

    CloseHandle(hWritePipe);

    WaitForSingleObject(piProcInfo.hProcess, INFINITE);

    CloseHandle(piProcInfo.hProcess);
    CloseHandle(piProcInfo.hThread);
}
