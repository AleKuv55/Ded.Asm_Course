//
//  List.h
//  Hash
//
//  Created by Alexandr Kuznetsov on 18.04.2018.
//  Copyright © 2018 Alexandr Kuznetsov. All rights reserved.
//

#ifndef List_h
#define List_h

#include <stdlib.h>

typedef char* T;

typedef struct Node_
{
    T value;
    struct Node_ *next;
    struct Node_ *prev;
} Node;

typedef struct List_
{
    int size;
    Node* tail;
    Node* head;
} List;

List* Constructor()
{
    List* MyList = (List*) calloc(1, sizeof(List));
    MyList -> size = 0;
    MyList -> head = MyList -> tail = NULL;
    return MyList;
}

int Destructor(List** MyList)                        // Don't know why **
{
    Node* tmp = (*MyList) -> head;
    Node* next = NULL;
    
    while (tmp)
    {
        next = tmp -> next;
        free(tmp);
        tmp = next;
    }
    free(*MyList);
    *MyList = NULL;
    return 0;
}

int PushForward(List* MyList, T data)                  // Insert at the beggining
{
    Node* tmp = (Node*) calloc(1, sizeof(Node));
    if (tmp == NULL){
        printf("PushForward");
        exit(1);
    }
    
    tmp -> value = data;
    tmp -> next = MyList -> head;
    tmp -> prev = NULL;
    
    if (MyList -> head)
    {
        MyList -> head -> prev = tmp;
    }
    MyList -> head = tmp;
    
    if (MyList -> tail == NULL)
    {
        MyList -> tail = tmp;
    }
    MyList -> size++;
    return 0;
}


T popFront(List* MyList) {
    Node *prev;
    T tmp;
    if (MyList -> head == NULL) {
        exit(2);
    }
    
    prev = MyList -> head;
    MyList -> head = MyList -> head -> next;
    if (MyList -> head) {
        MyList -> head -> prev = NULL;
    }
    if (prev == MyList -> tail) {
        MyList -> tail = NULL;
    }
    tmp = prev -> value;
    free(prev);
    
    MyList -> size--;
    return tmp;                             // Looks Strange
}



void PushBack(List* MyList, T value)
{
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) {
        printf("PushBack");
        exit(3);
    }
    tmp -> value = value;
    tmp -> next = NULL;
    tmp -> prev = MyList -> tail;
    if (MyList -> tail) {
        MyList -> tail -> next = tmp;
    }
    MyList -> tail = tmp;
    
    if (MyList -> head == NULL) {
        MyList -> head = tmp;
    }
    MyList->size++;
}

T popBack(List* MyList) {
    Node* next;
    T tmp;
    if (MyList -> tail == NULL) {
        exit(4);
    }
    
    next = MyList -> tail;
    MyList -> tail = MyList -> tail -> prev;
    if (MyList -> tail)
    {
        MyList -> tail -> next = NULL;
    }
    if (next == MyList -> head)
    {
        MyList -> head = NULL;
    }
    tmp = next -> value;
    free(next);
    
    MyList -> size--;
    return tmp;
}



Node* getNth(List* MyList, int index)
{
    Node* tmp = NULL;
    int i = 0;
    
    if (index < MyList -> size/2)
    {
        i = 0;
        tmp = MyList -> head;
        while (tmp && i < index)
        {
            tmp = tmp -> next;
            i++;
        }
    }
    else {
        i = MyList -> size - 1;
        tmp = MyList -> tail;
        while (tmp && i > index)
        {
            tmp = tmp -> prev;
            i--;
        }
    }
    
    return tmp;
}

int insert(List* MyList, int index, T value) {
    Node *elm = NULL;
    Node *ins = NULL;
    elm = getNth(MyList, index);
    if (elm == NULL)
    {
        exit(5);
    }
    ins = (Node*) calloc(1, sizeof(Node));
    ins -> value = value;
    ins -> prev = elm;
    ins -> next = elm -> next;
    if (elm -> next)
    {
        elm -> next -> prev = ins;
    }
    elm -> next = ins;
    
    if (!elm -> prev)
    {
        MyList -> head = elm;
    }
    
    if (!elm -> next)
    {
        MyList -> tail = elm;
    }
    
    MyList -> size++;
    
    return 0;
}

T deleteNth(List* MyList, int index) {
    Node* elm = NULL;
    T tmp = 0;
    elm = getNth(MyList, index);
    if (elm == NULL)
    {
        exit(5);
    }
    if (elm -> prev)
    {
        elm -> prev -> next = elm -> next;
    }
    if (elm -> next)
    {
        elm -> next -> prev = elm -> prev;
    }
    tmp = elm -> value;
    
    if (!elm -> prev)
    {
        MyList -> head = elm -> next;
    }
    if (!elm -> next)
    {
        MyList -> tail = elm -> prev;
    }
    
    free(elm);
    
    MyList -> size--;
    
    return tmp;
}

int Dump(List* MyList)
{
    Node* tmp = MyList -> head;
    int i = 0;
    while (tmp)
    {
        
        printf("\n%d. %s", i, tmp -> value);
        tmp = tmp -> next;
        i++;
    }
    printf("\nLength = %d\n", MyList -> size);
    return 0;
}
#endif /* List_h */
