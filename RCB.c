//
// Created by 傅康 on 2019/12/13.
//
#include "exp2.h"

Status createRCBList(pRCBList *list) {
    (*list) = (pRCBList) malloc(sizeof(RCBList));
    if (!*list) {
        return ERROR;
    }
    (*list)->head = (pRCBNode) malloc(sizeof(RCBNode));
    if (!(*list)->head) {
        return ERROR;
    }
    (*list)->head->next = NULL;
    (*list)->count = 0;
    return OK;
}

Status destroyRCBList(pRCBList *list) {
    pRCBNode p = (*list)->head;
    while (p->next) {
        pRCBNode q = p->next;
        free(p);
        p = q;
    }
    free(p);
    return OK;
}

Status insertRCB(pRCB p, pRCBList list) {
    RCBNode *pNode = (RCBNode *) malloc(sizeof(RCBNode));
    if (!pNode) {
        return ERROR;
    }
    pNode->rcb = p;
    list->count++;
    if (list->count == 0) {
        list->head->next = pNode;
    } else {
        pRCBNode q = list->head->next;
        list->head->next = pNode;
        pNode->next = q;
    }
    return OK;
}

Status createRCB(pRCB *p, property ID, pRCBList list) {
    (*p) = (pRCB) malloc(sizeof(RCB));
    if (!(*p)) {
        return ERROR;
    }
    (*p)->ID = ID;
    (*p)->isUse = NOTUSING;
    createPCBList(&((*p)->waitPList));
    //加入资源列表
    insertRCB(*p, list);
    return OK;
}

Status destroyRCB(pRCB *p) {
    destroyPCBList(&((*p)->waitPList));
    free(*p);
    return OK;
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
    return OK;
}

Status reloadRCB(bool flag, pRCB rcb) {
    if (rcb->waitPList->count == 0) {
        return OK;
    } else {
        pPCB pcb = NULL;
        switch (flag) {
            case PRIORITY:
                pcb = getMaxPriorityPCB(rcb->waitPList);
                break;
            case FIFO:
                pcb = getFirstPriorityPCB(rcb->waitPList);
                break;
        }
        findAndDelPCBNode(pcb, rcb->waitPList);
        findAndDelRCBNode(rcb, pcb->resRequest);
        useRCB(pcb, rcb);
        return OK;
    }
}

Status showAllRCB(pRCBList list) {
    for (pRCBNode p = list->head->next; p != NULL; p = p->next) {
        printf("%d ", p->rcb->ID);
    }
    return OK;
}