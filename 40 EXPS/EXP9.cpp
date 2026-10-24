#include <stdio.h>
#include <windows.h>

int main()
{
    HANDLE hMap;
    char *p;

    hMap = CreateFileMapping(
        INVALID_HANDLE_VALUE,
        NULL,
        PAGE_READWRITE,
        0,
        1024,
        "MySharedMemory"
    );

    if (hMap == NULL)
    {
        printf("Error creating shared memory\n");
        return 1;
    }

    p = (char *)MapViewOfFile(
        hMap,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        1024
    );

    if (p == NULL)
    {
        printf("Error attaching shared memory\n");
        CloseHandle(hMap);
        return 1;
    }

    sprintf(p, "Hello, Shared Memory!");

    printf("Data written to shared memory: %s\n", p);

    UnmapViewOfFile(p);
    CloseHandle(hMap);

    return 0;
}
