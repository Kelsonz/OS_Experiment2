//
// Created by 傅康 on 2019/12/13.
//

#include "LinkedList.h"

Status createNode(pNode *p, Element id, Element priority) {
    (*p) = (pNode) malloc(sizeof(Node));
    (*p)->id = id;
    (*p)->priority = priority;
    (*p)->next = NULL;
}

Status createList(pList *L) {
    (*L) = (pList) malloc(sizeof(List));
    (*L)->head = (pNode) malloc(sizeof(Node));
    (*L)->head->id = 0;
    (*L)->head->priority = 0;
    (*L)->head->next = (pNode) malloc(sizeof(Node));
};

int lenList(pList L) {
    return L->head->id;
}

Status insertList(pList L, Element id, Element priority) {
    pNode p;
    createNode(&p, id, priority);
    pNode temp = (L)->head->next;
    (L)->head->next = p;
    p->next = temp;
    (L)->head->id++;
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
            return OK;
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

Status change(pList L, pNode p) {
    pNode x = p->next;
    pNode y = x->next;
    pNode z = y->next;
    p->next = y;
    y->next = x;
    x->next = z;
}

Status sort(pList L) {
    int len = (L)->head->id;
    if (len == 0 | len == 1) {
        return OK;
    }
    int flag = FALSE;
    pNode p = (L)->head;
    for (int i = 0; i < len - 1; ++i) {
        for (int j = 0; j < len - i - 1; ++j) {
            if (p->next->priority < p->next->next->priority) {
                change(L, p);
                flag = TRUE;
            }
            p = p->next;
        }
        if (flag) {
            p = (L)->head;
            flag = FALSE;
            continue;
        } else {
            break;
        }
    }
}