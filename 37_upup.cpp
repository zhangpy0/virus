#include<bits/stdc++.h>
#include<Windows.h>
using namespace std;

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
    if (!IsRunAsAdministrator())
    {
        CHAR szPath[MAX_PATH];
        if (GetModuleFileName(NULL, szPath,sizeof(szPath)/sizeof(szPath[0])))
        {


            SHELLEXECUTEINFO sei = { sizeof(sei) };

            sei.lpVerb = "runas";
            sei.lpFile = szPath;
            sei.hwnd = NULL;
            sei.nShow = SW_SHOWDEFAULT;

            if (!ShellExecuteEx(&sei))
            {
                DWORD dwError = GetLastError();
                if (dwError == ERROR_CANCELLED)
                    //Annoys you to Elevate it LOL
                    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ElevateNow, 0, 0, 0);
            }
        }
    }            
    if (IsRunAsAdministrator())
    {
        cout<<"Already Elevated"<<endl;
    }
}

int main()
{
    ElevateNow();
    cout<<IsRunAsAdministrator();
    cout<<"please wait...";
    getchar();
    return 0;
}