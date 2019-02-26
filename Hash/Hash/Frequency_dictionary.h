//
//  Frequency_dictionary.h
//  Hash
//
//  Created by Alexandr Kuznetsov on 18.04.2018.
//  Copyright © 2018 Alexandr Kuznetsov. All rights reserved.
//

#ifndef Frequency_dictionary_h
#define Frequency_dictionary_h

#define HASH_1 26
#define HASH_2 20
#define HASH_3 40
#define HASH_4 40
#define HASH_5 40

#define SUM( a, b )\
int c = a + b ; \
    printf (#a);

#define ASM_INPUT_CMP( string_one, string_two, result ) \
         __asm__ ("xor %%rax, %%rax;" \
         "L1:;"\
         "lodsb;"\
         "test %%al, %%al;"\
         "jz EQU;"\
         "xorb (%%rdi), %%al ;"\
         "jnz EXIT;"\
         "inc %%rdi;"\
         "jmp L1;"\
         \
         "EQU:;"\
         "xorb (%%rdi), %%al;"\
         "EXIT:;"\
         "mov %%eax, %[result] ;"\
         \
         :[result] "=r" (result)\
         :[] "S" (string_one), [] "D" (string_two)\
         :\
         );\

#include <memory.h>
#include "List.h"
#include "Hash_1.h"
#include "Hash_2.h"
#include "Hash_3.h"
#include "Hash_4.h"
#include "Hash_5.h"

int ReadFile(FILE** pFile)
{
    *pFile = fopen( "Shakspear.txt", "r");
    if (*pFile == NULL)
    {
        fputs("Ошибка файла  ", stderr);
        exit(1);
    }
    return 0;
}

int leight_of_buf(FILE* pFile)
{
    int length;
    fseek(pFile, 0, SEEK_END);
    length = ftell(pFile);
    rewind(pFile);
    return length;
}

char* makebuf(FILE* pFile, int* Size, int* number_word)
{
    int length = leight_of_buf(pFile);
    char* buf = (char*) calloc(sizeof(char), length); // выделение памяти для массива
    if (buf == 0)
    {
        printf("Error calloc in buffer");
        exit(1);
    }
    
    fread(buf, sizeof(char), length, pFile); // запись файла в массив
    
    char* buf_no_signs = (char*) calloc(sizeof(char), length); // убираем запятые и заглавные
    
    int j = 0;
    for (int i = 0; i < length; i++)
    {
        if ( ((buf[i] >= 'a') && (buf[i] <= 'z')) )
        {
            buf_no_signs[j] = buf[i];
            j++;
        }
        else if ((buf[i] == ' ') || (buf[i] == 10))
        {
            buf_no_signs[j] = '\0';
            j++;
            //buf_no_signs[j] = ' ';
            //j++;
            (*number_word)++;
        }
        else if ((buf[i] >= 65) && (buf[i] <= 90))
        {
            buf_no_signs[j] = buf[i] + 32;
            j++;
        }
        
    }
    *Size = j; // зафиксировали длину массива
    free(buf);
    return buf_no_signs;
}

char** make_array_point(char* buffer, int* number_word, int* Size)
{
    char** pointer_words = (char**) calloc(sizeof(char*), (*number_word));
    int n = 0;
    for ( int k = 0; k < (*number_word); k++)
    {
        pointer_words[k] = buffer + n;
        printf("%s \n", buffer + n);
        for (; (n < (*Size)) && (buffer[n] != '\0'); n++)
        {}
        n++;
    }
        
    return pointer_words;
}

/*List** Make_Hash_Table()
{
    List** array = (List**) calloc(sizeof(List*), HASH_2);
    if (array == NULL)
    {
        printf("List array is NULL");
    }
    for (int i = 0; i < HASH_2; i++)
    {
        array[i] = Constructor();
    }
    return array;
}*/

//
//
//          The Do FUNCTION _ DO EVERYTHING
//
//

int Do(char* buffer, int* number_word, int* Size)
{
    char** pointer_words = make_array_point(buffer, number_word, Size);
    
    List** array = (List**) calloc(sizeof(List*), HASH_1);
    if (array == NULL)
    {
        printf("List array is NULL");
    }
    
    for (int i = 0; i < HASH_1; i++)
    {
        array[i] = Constructor();
    }
    
    Node* now = NULL;
    int x = 0;
    int hash_result = 0;
    int the_same = 0;

    for ( int i = 0; i < *number_word; i++)
    {
        char* tmp = pointer_words[i];
        
        hash_result = Hash_1(tmp);
        
        the_same = 0;
        now = array[hash_result] -> head;
        
        if (now == NULL)
        {
            PushForward(array[hash_result], tmp);
            now = array[hash_result] -> head;
            the_same++;
        }
        else
        {
            while (now)
            {
//                if (strcmp(tmp, now -> value) == 0)
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
                         "EXIT:;"
                         "mov %%eax, %[x] ;"
                         
                         :[x] "=r" (x)
                         :[a] "S" (tmp), [b] "D" (now -> value)
                         :
                         );
//                ASM_INPUT_CMP(tmp, now -> value, x)
                if(x == 0)
                {
                    the_same++;
                }
                now = now -> next;
            }
        }
        if (the_same == 0)
            PushForward(array[hash_result], tmp);
        
        
    }
    
    for ( int i = 0; i < HASH_1; i++)
    {
        printf(" %d \n", array[i] -> size);
    }
    
    
    /*for (int i = 0; i < HASH_4; i++)
    {
        Destructor(&array[i]);
    }
    free(array);*/
    return 0;
}
#endif /* Frequency_dictionary_h */
