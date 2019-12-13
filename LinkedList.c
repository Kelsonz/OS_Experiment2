//
// Created by 傅康 on 2019/12/13.
//

#include "Experiment.h"

Status Node_Create(pNode *p, Element id) {

    (*p) = (pNode) malloc(sizeof(Node));
    (*p)->id = id;
    (*p)->next = NULL;

}

Status List_Init(pList *L) {
    (*L) = (pList) malloc(sizeof(List));
    pNode head;
    Node_Create(&head, 0);
    (*L)->head = head;
};

int List_len(pList L) {
    int sum = 0;
    pNode p = L->head->next;
    while (p) {
        sum++;
        p = p->next;
    }

    return sum;
}

Status List_Insert(pList *L, Element id) {
    pNode p;
    Node_Create(&p, id);
    pNode temp = (*L)->head->next;
    (*L)->head->next = p;
    p->next = temp;
    return OK;
}

Status List_Del(pList *L) {
    pNode p = (*L)->head->next;
    if (List_len(*L) == 1) {
        free(p);
        return OK;
    } else {
        pNode q = p->next;
        (*L)->head->next = q;
        free(p);
        return OK;
    }
}

Status List_Print(pList L) {
    int len = List_len(L);
    pNode p = L->head;
    for (int i = 0; i < len; i++) {
        p = p->next;
        if (i == len - 1) {
            printf("%d", p->id);
        } else {
            printf("%d -> ", p->id);
        }
    }
    return OK;
}
