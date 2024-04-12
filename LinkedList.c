#include <stdlib.h>

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

bool add(LinkedList *list, void *value) {
    if (!list) return false;

    LinkedListNode *new = malloc(sizeof(LinkedListNode));

    new->value = value;

    if (list->tail) {
        list->tail->next = new;
        new->prev = list->tail;
    } else {
        list->head = new;
        list->tail = new;
    }

    return true;
}

bool addFirst(LinkedList *list, void *value) {
    if (!list) return false;

    LinkedListNode *new = malloc(sizeof(LinkedListNode));

    new->value = value;

    if (list->head) {
        new->next = list->head;
        list->head->prev = new;
        list->head = new;
    } else {
        list->head = new;
        list->tail = new;
    }

    return true;
}

bool drop(LinkedList *list) {
    if (!list) return false;
    if (!list->head) return false;

    if (list->tail == list->head) {
        free(list->head);

        list->head = NULL;
        list->tail = NULL;
    } else {
        LinkedListNode *toBeRemoved = list->head;

        if (list->head->next) {
            list->head->next->prev = NULL;
            list->head = list->head->next;
        }

        free(toBeRemoved);
    }

    return true;
}

bool dropLast(LinkedList *list) {
    if (!list) return false;
    if (!list->tail) return false;

    if (list->tail == list->head) {
        free(list->head);

        list->head = NULL;
        list->tail = NULL;
    } else {
        LinkedListNode *toBeRemoved = list->tail;

        if (list->tail->prev) {
            list->tail->prev->next = NULL;
            list->tail = list->tail->prev;
        }

        free(toBeRemoved);
    }

    return true;
}

int dropLast(LinkedList *list, const int amount) {
    if (!list) return -1;
    if (!list->head) return -1;

    int successCount = 0;

    for (int i = 0; i < amount; ++i) {
        if (dropLast(list)) {
            successCount++;
        } else {
            break;
        }
    }

    return successCount;
}

int drop(LinkedList *list, const int amount) {
    if (!list) return -1;
    if (!list->head) return -1;

    int successCount = 0;

    for (int i = 0; i < amount; ++i) {
        if (drop(list)) {
            successCount++;
        } else {
            break;
        }
    }

    return successCount;
}
