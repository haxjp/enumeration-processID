#include <windows.h>
#include <iostream>
#include <tchar.h>
#include <psapi.h>
using namespace std;


void PrintProcessNameAndID(DWORD processID)
{
    char szProcessName[260] = "nope";
    char aaa[260] = "Minecraft.Windows.exe";
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
        PROCESS_VM_READ,
        FALSE, processID);

    if (NULL != hProcess)
    {
        HMODULE hMod;

        DWORD cbNeeded;

        if (EnumProcessModules(hProcess, &hMod, sizeof(hMod),
            &cbNeeded))
        {
            GetModuleBaseName(hProcess, hMod, szProcessName,
                sizeof(szProcessName) / sizeof(TCHAR));

            switch(strcmp(szProcessName,aaa)){
            case 0: cout  << "\x1b[38;2;255;0;00m" << szProcessName << " " << processID << "\n" << "\x1b[m";
                break;

            default: cout << szProcessName << " " << processID << "\n";
                break;
            }
        }
    }



    CloseHandle(hProcess);
}

char aaa[1024];

int main(void)
{

    DWORD aProcesses[512], cbNeeded, cProcesses;
    unsigned int i = 0;

    if (EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded) == 0)//‚±‚±‚Å‚·‚×‚Ä‚ÌPID‚ðŽæ“¾
    {
        return 1;
    }

    cProcesses = cbNeeded / 4;

    for (; i < cProcesses; i += 2)
    {
            PrintProcessNameAndID(aProcesses[i]);
    }

    return 0;
}