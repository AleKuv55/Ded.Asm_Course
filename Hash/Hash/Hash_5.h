//
//  Hash_5.h
//  Hash
//
//  Created by Alexandr Kuznetsov on 18.04.2018.
//  Copyright © 2018 Alexandr Kuznetsov. All rights reserved.
//

#ifndef Hash_5_h
#define Hash_5_h
unsigned int Hash_5(char* word)
{
    unsigned int hash = 0;
    
    while(*word != '\0')
    {
        if(hash % 2 == 0)
            hash = hash >> 1;
        else{
            hash = hash >> 1;
            hash += 2147483648; // 2^31
        }
        
        hash = hash ^ (*word++);
    }
    return hash % HASH_5;
}

#endif /* Hash_5_h */
