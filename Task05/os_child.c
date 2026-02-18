#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#define SHM_NAME "shared_memory"
#define SHM_SIZE 1024

int main() {

    HANDLE hMapFile;
    LPVOID pBuf;

    // Abrir memoria compartida existente
    hMapFile = OpenFileMappingA(
        FILE_MAP_ALL_ACCESS,
        FALSE,
        SHM_NAME);


    if (hMapFile == NULL)
    {
        printf("Could not open file mapping object (%lu).\n", GetLastError());
        return 1;
    }

    // Mapear memoria
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

    printf("Child Process: Read \"%s\"\n", (char*)pBuf);

    
    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}
