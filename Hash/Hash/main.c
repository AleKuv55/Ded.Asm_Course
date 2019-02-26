//
//  main.c
//  Hash
//
//  Created by Alexandr Kuznetsov on 18.04.2018.
//  Copyright © 2018 Alexandr Kuznetsov. All rights reserved.
//

#include <stdio.h>
#include "Frequency_dictionary.h"

int main()
{
    FILE* pFile = NULL;
    ReadFile(&pFile);
    
    int Size = 0;                           // количество символов
    int number_word = 0;                    // количество слов
    
    char* buffer = makebuf(pFile, &Size, &number_word); // создали массив
    fclose(pFile);
    
    Do(buffer, &number_word, &Size);
   
    return 0;
}
