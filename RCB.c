//
// Created by 傅康 on 2019/12/13.
//
#include "CB.h"

Status initRCBList(pRCBList *list) {
    (*list) = (pRCBList) malloc(sizeof(RCBList));
    (*list)->head = (pRCBNode) malloc(sizeof(RCBNode));
    (*list)->head->next = NULL;
    (*list)->count = 0;
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
    createList(&((*p)->waitPList));
    //加入资源列表
    insertRCB(*p, list);
}

Status destroyRCB(pRCB *p) {
    destroyList(&((*p)->waitPList));
    free(*p);
}

Status useRCB(pPCB pcb, property RCBID, pRCBList list) {
    pRCB rcb = getRCBPointer(RCBID, list);
    if (rcb->isUse == USING) {
        insertList((rcb->waitPList), pcb->ID, pcb->priority);
        return BUSY;
    } else if (rcb->isUse == NOTUSING) {
        rcb->isUse = USING;
        return SUCCESS;
    }
}

Status releaseRCB(pPCB pcb, property RCBID, pRCBList *list) {
    pRCB rcb = getRCBPointer(RCBID, list);
    rcb->isUse = NOTUSING;
    return OK;
}

pRCB getRCBPointer(property RCBID, pRCBList list) {
    pRCBNode p = (list)->head->next;
    while (p) {
        if (p->rcb->ID == RCBID) {
            return p->rcb;
        } else {
            p = p->next;
        }
    }
}
