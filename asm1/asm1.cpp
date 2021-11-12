// asm1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <stdio.h>

int main()
{

    char* str;
    unsigned int n;
    const char* format_n = "%d";
    const char* format_str = "%s";
    const char* request_n = "Enter the n value\n";
    const char* request_str = "Enter the string\n";

    __asm {

        mov     eax, request_n
        push    eax
        call    printf
        add     esp, 4

        mov     eax, dword ptr[n]
        push    eax
        mov     eax, format_n
        push    eax
        call    scanf
        add     esp, 8

        mov     eax, 0

        mov     ecx, n

    }
}