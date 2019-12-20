//
// Created by 傅康 on 2019/12/13.
//

#include "LinkedList.h"

Status createNode(pNode *p, Element id) {
    (*p) = (pNode) malloc(sizeof(Node));
    (*p)->id = id;
    (*p)->next = NULL;
}

Status createList(pList *L) {
    (*L) = (pList) malloc(sizeof(List));
    pNode head;
    createNode(&head, 0);
    (*L)->head = head;
};

int lenList(pList L) {
//    int sum = 0;
//    pNode p = L->head->next;
//    while (p) {
//        sum++;
//        p = p->next;
//    }
//
//    return sum;
    return L->head->id;
}

Status insertList(pList *L, Element id) {
    pNode p;
    createNode(&p, id);
    pNode temp = (*L)->head->next;
    (*L)->head->next = p;
    p->next = temp;
    (*L)->head->id++;
    return OK;
}

Status delNode(pList *L) {
    pNode p = (*L)->head->next;
    if (lenList(*L) == 1) {
        free(p);
        (*L)->head->next = NULL;
        return OK;
    } else {
        pNode q = p->next;
        free(p);
        (*L)->head->next = q;
        return OK;
    }
}
Status destroyList(pList *L) {
    int len = lenList(*L);
    while (len > 0) {
        delNode(L);
        len--;
        if (len == 0) {
            free((*L)->head);
        }
    }
}

Status findAndDelNode(pList *L, property ID) {
    pNode p = (*L)->head;
    if (p->next == NULL) {
        return ERROR;
    }
    while (TRUE) {
        if (p->next->id == ID) {
            pNode q = p->next->next;
            p->next = q;
            free(p->next);
            break;
        }
        p = p->next;
    }
}

Status printList(pList L) {
    int len = lenList(L);
    pNode p = L->head;
    for (int i = 0; i < len; i++) {
        p = p->next;
        if (i == len - 1) {
            printf("%d\n", p->id);
        } else {
            printf("%d -> ", p->id);
        }
    }
    return OK;
}
