// asm1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <stdio.h>
#include <stdlib.h>

char* concat(const char* text, int n, int size_text)
{
    //ЗАДАЧА 4
    //Создать строку, полученную копированием исходной строки заданное число раз.

    char* result = NULL;

    __asm {
        lea     edi, result
        mov     edx, 0

        ; text == null
        mov     eax, text
        cmp     eax, 0
        je      STR_IS_NULL

        ;malloc for result
        mov     eax, size_text
        mov     ebx, n
        mul     ebx

        push    eax
        call    malloc
        add     esp, 4

        inc     eax

        cmp     eax, 0
        je      MALLOC_NULL

        xor     edi, edi
        xor     ecx, ecx
        mov     ebx, text

    ;for(ecx = 0; ecx < n; ecx++)
    FOR_I:
        cmp     ecx, n
        jge     ADD_NULL_CHAR
        inc     ecx
        xor     esi, esi

    ;for (esi = 0; esi < size_text; esi++)
    FOR_J:
        cmp     esi, size_text
        jge     FOR_I

        mov     dl, [ebx][esi]
        mov     [eax][edi], dl

        inc     esi
        inc     edi
        
        jmp     FOR_J

    STR_IS_NULL:
        xor     eax, eax
        jmp     END

    ADD_NULL_CHAR:
        mov     byte ptr [eax][edi], '\0'
        jmp     END

    MALLOC_NULL:
        jmp     END

    END:
        mov     result, eax
        xor     eax, eax
    }
    return result;
}