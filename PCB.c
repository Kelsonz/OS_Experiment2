//
// Created by 傅康 on 2019/12/13.
//
#include "LinkedList.h"

#include "CB.h"

Status createPCB(pPCB *pcb, property ID, property priority, pList pReadyList) {
    (*pcb) = (pPCB) malloc(sizeof(PCB));
    (*pcb)->priority = priority;
    (*pcb)->ID = ID;
    if (!(*pcb)) {
        return ERROR;
    }
    createPCBTree(&((*pcb)->pPTree));
    createPCBStatus(&((*pcb)->status));
    createList(&((*pcb)->resUsing));
    createList(&((*pcb)->resRequest));
    addToReadyList(*pcb, &pReadyList);
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
    (*pcbList) = (pPCBList) malloc(sizeof(PCBList));
    (*pcbList)->head = (pPCBNode) malloc(sizeof(PCBLNode));
    (*pcbList)->head->next = NULL;
}

Status destroyPCB(pPCB *pcb) {
    destroyPCBStatus(&((*pcb)->status));
    destroyPCBTree(&((*pcb)->pPTree));
    destroyList(&((*pcb)->resUsing));
    destroyList(&((*pcb)->resRequest));
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
    return list->count;
}

Status setStatus(pPCB pcb, property status) {
    pcb->status->stausID = status;
    return OK;
}

property getStatus(pPCB pcb) {
    return pcb->status->stausID;
}

//PCB申请资源
Status getResource(pPCB pcb, property RCBID, pRCBList *list, pList pReadyList, pList pBlockedList) {
    property result = useRCB(pcb, RCBID, list);
    if (result == SUCCESS) {
        insertList(&((*pcb).resUsing), RCBID);
    } else if (result == BUSY) {
        pcb->status->stausID = BLOCKED;
        insertList(&((*pcb).resRequest), RCBID);
//        todo:进程在对队列中的移动
//        insertList(&pReadyList, pcb->ID);
    }
    return OK;
}

Status releaseResource(pPCB pcb, property RCBID, pRCBList *list, pList pReadyList, pList pBlockedList) {
    releaseRCB(pcb, RCBID, list);
    findAndDelNode(&((*pcb).resUsing), RCBID);
}

Status setPriority(pPCB pcb) {
    return pcb->priority;
}

Status addToReadyList(pPCB pcb, pList *pReadyList) {
    pcb->status->stausID = READY;
    insertList(pReadyList, pcb->ID);
}

Status quitFromReadyList(pPCB pcb, pList *pReadyList, property status) {
    findAndDelNode(pReadyList, pcb->ID);
    pcb->status->stausID = status;
}

Status addToBlockedList(pPCB pcb, pList *pBlockedList) {
    pcb->status->stausID = BLOCKED;
    insertList(pBlockedList, pcb->ID);
}

Status quitFromBlockedList(pPCB pcb, pList *pBlockedList, property status) {
    findAndDelNode(pBlockedList, pcb->ID);
    pcb->status->stausID = status;
}

Status scheduler(pList pReadyList, pList pBlockedList) {

}
