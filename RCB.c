//
// Created by 傅康 on 2019/12/13.
//
#include "CB.h"

Status createRCBList(pRCBList *list) {
    (*list) = (pRCBList) malloc(sizeof(RCBList));
    (*list)->head = (pRCBNode) malloc(sizeof(RCBNode));
    (*list)->head->next = NULL;
    (*list)->count = 0;
}

Status destroyRCBList(pRCBList *list) {
    pRCBNode p = (*list)->head;
    while (p->next) {
        pRCBNode q = p->next;
        free(p);
        p = q;
    }
    free(p);
}

Status insertRCB(pRCB p, pRCBList list) {
    RCBNode *pNode = (RCBNode *) malloc(sizeof(RCBNode));
    pNode->rcb = p;
    list->count++;
    if (list->count == 0) {
        list->head->next = pNode;
    } else {
        pRCBNode q = list->head->next;
        list->head->next = pNode;
        pNode->next = q;
    }
}

Status createRCB(pRCB *p, property ID, pRCBList list) {
    (*p) = (pRCB) malloc(sizeof(RCB));
    (*p)->ID = ID;
    (*p)->isUse = NOTUSING;
    createPCBList(&((*p)->waitPList));
    //加入资源列表
    insertRCB(*p, list);
}

Status destroyRCB(pRCB *p) {
    destroyPCBList(&((*p)->waitPList));
    free(*p);
}

Status findAndDelRCBNode(pRCB rcb, pRCBList rcbList) {
    rcb->isUse = NOTUSING;
    rcbList->count--;
    pRCBNode p = rcbList->head;
    if (rcbList->count == 1) {
        free(p->next);
        p->next = NULL;
        return OK;
    }
    while (p->next) {
        if (p->next->rcb->ID == rcb->ID) {
            pRCBNode q = p->next;
            p->next = q->next;
            free(q);
            return OK;
        } else {
            p = p->next;
        }
    }
}

Status reloadRCB(pRCB rcb) {
    if (rcb->waitPList->count == 0) {
        return OK;
    } else {
        pPCB pcb = getMaxPriorityPCB(rcb->waitPList);
        findAndDelRCBNode(rcb, pcb->resRequest);
        addToResUsingList(pcb, rcb);
        rcb->isUse = USING;
        findAndDelPCBNode(pcb, rcb->waitPList);
    }
}

Status showAllRCB(pRCBList list) {
    for (pRCBNode p = list->head->next; p != NULL; p = p->next) {
        printf("%d ", p->rcb->ID);
    }
    return OK;
}