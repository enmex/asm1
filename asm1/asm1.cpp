// asm1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <stdio.h>

void _print_text(const char* text) {
    __asm {
        mov    eax, text
        push   eax
        call   printf
        add    esp, 4
        xor    eax, eax
    }
}

int main()
{

    char* text;
    unsigned int n;

    const char* format_n = "%d";
    const char* format_str = "%20s";

    const char* request_n = "Enter the n value\n";
    const char* request_str = "Enter the string\n";

    __asm {

        mov     eax, request_n
        push    eax
        call    printf
        add     esp, 4
        xor     eax, eax

        lea     eax, n
        push    eax
        mov     eax, format_n
        push    eax
        call    scanf
        add     esp, 8
        xor     eax, eax

        mov     eax, request_str
        push    eax
        call    printf
        add     esp, 4
        xor     eax, eax

        lea     eax, text
        push    eax
        mov     eax, format_str
        push    eax
        call    scanf
        add     esp, 8
        xor     eax, eax

        mov     ebx, n

    PRINT_STRING:
        lea     eax, text
        push    eax
        call    printf
        add     esp, 4
        xor     eax, eax
        
        dec     ebx
        cmp     ebx, 0     
        jne     PRINT_STRING

        jmp     END

    END:
        ret     0
    }
}