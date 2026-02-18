#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#define SHM_NAME "shared_memory"
#define SHM_SIZE 1024

int main()
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    HANDLE hMapFile;
    LPVOID pBuf;

    char message[] = "Shared Memory Example";

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

    //Memoria compartida
    hMapFile = CreateFileMappingA(
        INVALID_HANDLE_VALUE,   // usar memoria del sistema
        NULL,
        PAGE_READWRITE,
        0,
        SHM_SIZE,
        SHM_NAME);


    if (hMapFile == NULL)
    {
        printf("Could not create file mapping object (%lu).\n", GetLastError());
        return 1;
    }

    pBuf = MapViewOfFile(
        hMapFile,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        SHM_SIZE);

    if (pBuf == NULL)
    {
        printf("Could not map view of file (%lu).\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    // Escribir en memoria compartida
    printf("Parent Process: Writing \"%s\"\n", message);
    CopyMemory(pBuf, message, sizeof(message));

    if (!CreateProcessA(
            "os_child.exe",
            NULL,
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &si,
            &pi))
    {
        printf("CreateProcess failed (%lu).\n", GetLastError());
        return 1;
    }

    WaitForSingleObject( pi.hProcess, INFINITE );
    
     // Limpieza
    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}