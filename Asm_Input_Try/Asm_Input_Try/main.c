//
//  main.c
//  Asm_Input_Try
//
//  Created by Alexandr Kuznetsov on 21.04.2018.
//  Copyright © 2018 Alexandr Kuznetsov. All rights reserved.
//

#include <stdio.h>
#include <string.h>
int main()
{
    char* a = "abcd";
    char* b = "abcdddd";
    int x = 0;
 
   /* __asm__ __volatile__ (//".intel_syntax noprefix \n\t"
                          "xor %%rax, %%rax \n\t"
                          //"mov %%eax, %[x] \n\t"
                          "mov $20, %%rcx \n\t"
                          "repe cmpsb \n\t"
                          
                          "jne Done \n\t"
                          "inc %%eax\n"
                          "mov %%eax, %[x] \n\t"
                          "jmp equal\n"
                          
                          "Done: xor %%rax, %%rax \n\t"
                          "mov %%eax, %[x] \n\t"
                          "equal: \n\t"
                          
                          //"mov %%rax, $0 \n\t"
                          //"ret\n\t"
            //".att_syntax\n\t"
                          : [x] "=r" (x)
                          : "S" (a), "D" (b)
                          :
                          );*/
    
    __asm__ ("xor %%rax, %%rax;"
             "L1:;"
             "lodsb;"
             "test %%al, %%al;"
             "jz EQU;"
             "xorb (%%rdi), %%al ;"
             "jnz EXIT;"
             "inc %%rdi;"
             "jmp L1;"
             
             "EQU:;"
             "xorb (%%rdi), %%al;"
             //"mov %%eax, %[x] ;"
             "EXIT:;"
             "mov %%eax, %[x] ;"

             :[x] "=r" (x)
             :[a] "S" (a), [b] "D" (b)
             :
             );
    printf("%d", x);
    return 0;
}
/*
 xor rax, rax
 mov rcx, 20
 repe cmpsb
 jne done
 inc rax
 done:


 __asm__ __volatile__ (//".intel_syntax noprefix \n\t"
 "xor rax, rax \n\t"
 "mov rcx, 40 \n\t"
 "repe cmpsb \n\t"
 
 "jne Done \n\t"
 "inc rax\n"
 "mov %0, rax\n"
 "jmp equal\n"
 
 "Done: mov %0, rax \n\t"
 
 "equal: \n\t"
 //"ret\n\t"
 //".att_syntax\n\t"
 : "=r" (x)
 : "S" (a), "D" (b)
 :
 );
/*__asm__ (
 "mov eax, %1\n\t"
 "mov %0, eax\n\t"
 : "=r"(b)
 : "r"(a)
 : "%eax");*/

/*s ассемблерная вставка */
/* выходные операнды */
/* входные операнды */
/* разрушаемые регистры */


/*"Next:\n\t"
 "mov rax, [esi]\n\t"
 "mov rdx, [edi]\n\t"
 "cmpsb"
 "inc rsi\n\t"
 "inc rdi\n\t"
 
 "cmp rax, rdx\n\t"
 "jne End\n\t"
 
 "and rax, rdx\n\t"
 "cmp rax, 0\n\t"
 "je Equal\n\t"
 
 "jmp Next\n\t"
 "cmp rax, 0\n\t"
 "je End\n\t"
 "cmp rdx, 0\n\t"
 "je End\n\t"
 
 "End: mov %0, 0 \n\t"
 "jmp Finish \n\t"
 // "ret\n\t"
 
 "Equal:\n\t"
 "mov rax, [rsi] \n\t"
 "mov rdx, [rdi] \n\t"
 "xor rax, rdx \n\t"
 "mov %0, rax\n\t"
 "Finish:"*/
