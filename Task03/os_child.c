#include <windows.h>
#include <stdio.h>

#define BUFSIZE 4096 
 
int main(void) 
{ 
   CHAR chBuf[BUFSIZE]; 
   DWORD dwRead; 
   HANDLE hStdin; 
 
   hStdin = GetStdHandle(STD_INPUT_HANDLE); 

   if (hStdin == INVALID_HANDLE_VALUE) ExitProcess(1); 

    ReadFile(hStdin, chBuf, BUFSIZE, &dwRead, NULL);

    chBuf[dwRead] = '\0';

    printf("Child Process: Received \"%s\"\n", chBuf);
    return 0;
}