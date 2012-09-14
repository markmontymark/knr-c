#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
 
int main() 
{
    setlocale(LC_ALL,"");
    wchar_t myChar1 = L'Ω';
    wchar_t myChar2 = 0x2126;  // hexadecimal encoding of char Ω using UTF-16
    wchar_t myString1[] = L"♠♣♥♦";
    wchar_t myString2[] = { 0x2660, 0x2663, 0x2665, 0x2666, 0x0000 };
    // hex encoding of null-terminated string ♠♣♥♦ using UTF-16
 
    wprintf(L"This is char: %lc \n",myChar1);
    wprintf(L"This is char: %lc \n",myChar2);
    wprintf(L"This is a long string: %ls \n",myString1);
    wprintf(L"This is a long string: %ls \n",myString2);
}
