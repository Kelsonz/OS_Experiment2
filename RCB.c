//
// Created by 傅康 on 2019/12/13.
//
#include "RCB.h"

static pRCBList *list;

static Status initRCBList(void) {
    (*list) = (pRCBList) malloc(sizeof(RCBNode));
    (*list)->head = 0;
    (*list)->next = NULL;
}

static Status insertRCB(pRCB p) {
    RCBNode *pNode = (RCBNode *) malloc(sizeof(RCBNode));
    pNode->rcb = p;
    if ((*list)->next == NULL) {
        (*list)->next = pNode;
    } else {
        pRCBNode q = (*list)->next;
        (*list)->next = pNode;
        pNode->next = q;
    }
}

Status createRCB(pRCB *p, property ID) {
    (*p) = (pRCB) malloc(sizeof(RCB));
    (*p)->ID = ID;
    (*p)->isUse = NOTUSING;
    createList(&((*p)->waitPList));
    //加入资源列表
    insertRCB(*p);
}

Status useRCB(pPCB pcb, property RCBID) {
    pRCB rcb = getRCBPointer(RCBID);
    if (rcb->isUse == USING) {
        insertList(&(rcb->waitPList), pcb->ID);
        return BUSY;
    } else if (rcb->isUse == NOTUSING) {
        rcb->isUse = USING;
        return SUCCESS;
    }
}

pRCB getRCBPointer(property RCBID) {
    pRCBNode p = (*list)->next;
    while (p) {
        if (p->rcb->ID == RCBID) {
            return p->rcb;
        } else {
            p = p->next;
        }
    }
}

int lengthRCBList(void) {
    int sum = 0;
    pRCBNode p = (*list)->next;
    while (p) {
        sum++;
        p = p->next;
    }
    return sum;
}