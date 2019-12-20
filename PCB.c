//
// Created by 傅康 on 2019/12/13.
//
#include "LinkedList.h"

#include "PCB.h"
#include "RCB.h"

Status createPCB(pPCB *pcb, property ID, property priority) {
    (*pcb) = (pPCB) malloc(sizeof(PCB));
    (*pcb)->priority = priority;
    (*pcb)->ID = ID;
    if (!(*pcb)) {
        return ERROR;
    }
    createPCBTree(&((*pcb)->pPTree));
    createPCBStatus(&((*pcb)->status));
    createList(&((*pcb)->resource));
};

Status createPCBStatus(pPCBStatus *pcbStatus) {
    (*pcbStatus) = (pPCBStatus) malloc(sizeof(PCBStatus));
    (*pcbStatus)->stausID = READY;
};

Status createPCBTree(pPCBTree *pcbTree) {
    (*pcbTree) = (pPCBTree) malloc(sizeof(PCBTree));
    createPCBList(&((*pcbTree)->son));
};

Status createPCBList(pPCBList *pcbList) {
    (*pcbList) = (pPCBList) malloc(sizeof(PCBLNode));
    (*pcbList)->next = NULL;
}

Status destroyPCB(pPCB *pcb) {
    destroyPCBStatus(&((*pcb)->status));
    destroyPCBTree(&((*pcb)->pPTree));
    destroyList(&((*pcb)->resource));
    free(*pcb);
}

Status destroyPCBStatus(pPCBStatus *pcbStatus) {
    free(*pcbStatus);
}

Status destroyPCBTree(pPCBTree *pcbTree) {
    destoryPCBList(&((*pcbTree)->son));
    free(*pcbTree);
}

Status destoryPCBList(pPCBList *pcbList) {
    pPCBNode p = (*pcbList);
    while (p->next) {
        pPCBNode q = p->next;
        free(p);
        p = q;
    }
    free(p);
}

int lengthPCBList(pPCBList list) {
    int sum = 0;
    pPCBNode p = list->next;
    while (p) {
        sum++;
        p = p->next;
    }
    return sum;
}

Status setStatus(pPCB pcb, property status) {
    pcb->status->stausID = status;
    return OK;
}
property getStatus(pPCB pcb){
    return pcb->status->stausID;
}

Status getResource(pPCB pcb, property RCBID){
    pcb->status->stausID = BLOCKED;
    if (useRCB(pcb,RCBID))
    insertList(&((*pcb).resource),RCBID);
    return OK;
}
Status setPriority(pPCB pcb){
    return pcb->priority;
}