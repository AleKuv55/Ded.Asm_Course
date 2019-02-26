//
//  Hash_3.h
//  Hash
//
//  Created by Alexandr Kuznetsov on 18.04.2018.
//  Copyright © 2018 Alexandr Kuznetsov. All rights reserved.
//

#ifndef Hash_3_h
#define Hash_3_h
#include <memory.h>

int Hash_3(char* word)
{
    int sum_ascii_codes = 0;
    for(int i = 0; i < strlen(word); i++)
    {
        sum_ascii_codes = sum_ascii_codes + word[0];
    }
    return sum_ascii_codes % HASH_3;
};

#endif /* Hash_3_h */
