//
// Created by 傅康 on 2019/12/13.
//
#include "CB.h"

Status initRCBList(pRCBList *list) {
    (*list) = (pRCBList) malloc(sizeof(RCBList));
    (*list)->head = (pRCBNode) malloc(sizeof(RCBNode));
    (*list)->head->next = NULL;
}

Status insertRCB(pRCB p, pRCBList *list) {
    RCBNode *pNode = (RCBNode *) malloc(sizeof(RCBNode));
    pNode->rcb = p;
    if (lengthRCBList(list) == 0) {
        (*list)->head->next = pNode;
    } else {
        pRCBNode q = (*list)->head->next;
        (*list)->head->next = pNode;
        pNode->next = q;
    }
}

Status createRCB(pRCB *p, property ID, pRCBList *list) {
    (*p) = (pRCB) malloc(sizeof(RCB));
    (*p)->ID = ID;
    (*p)->isUse = NOTUSING;
    createList(&((*p)->waitPList));
    //加入资源列表
    insertRCB(*p, list);
}

Status useRCB(pPCB pcb, property RCBID, pRCBList *list) {
    pRCB rcb = getRCBPointer(RCBID, list);
    if (rcb->isUse == USING) {
        insertList(&(rcb->waitPList), pcb->ID);
        return BUSY;
    } else if (rcb->isUse == NOTUSING) {
        rcb->isUse = USING;
        return SUCCESS;
    }
}

pRCB getRCBPointer(property RCBID, pRCBList *list) {
    pRCBNode p = (*list)->head->next;
    while (p) {
        if (p->rcb->ID == RCBID) {
            return p->rcb;
        } else {
            p = p->next;
        }
    }
}

int lengthRCBList(pRCBList *list) {
    int sum = 0;
    pRCBNode p = (*list)->head->next;
    while (p) {
        sum++;
        p = p->next;
    }
    return sum;
}