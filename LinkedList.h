//
// Created by Kennarddh on 3/22/2024.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

struct LinkedListNode {
    struct LinkedListNode *next;
    struct LinkedListNode *prev;
    void *value;
};

struct LinkedList {
    struct LinkedListNode *head;
    struct LinkedListNode *tail;
};

typedef struct LinkedListNode LinkedListNode;
typedef struct LinkedList LinkedList;

bool add(LinkedList *list, void *value);

bool addFirst(LinkedList *list, void *value);

bool drop(LinkedList *list);

bool dropLast(LinkedList *list);

int dropLast(LinkedList *list, int amount);

int drop(LinkedList *list, int amount);

#endif //LINKEDLIST_H
