//
//  Hash_4.h
//  Hash
//
//  Created by Alexandr Kuznetsov on 18.04.2018.
//  Copyright © 2018 Alexandr Kuznetsov. All rights reserved.
//

#ifndef Hash_4_h
#define Hash_4_h
unsigned int Hash_4(char* word)
{
    unsigned int h = 5381;
    
    for (; *word; word++) {
        h = (h << 5) + h + *word;
    }
    return h % HASH_4;
//    return h ;
};

#endif /* Hash_4_h */
