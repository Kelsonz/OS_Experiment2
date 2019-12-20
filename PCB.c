//
// Created by 傅康 on 2019/12/13.
//
#include "LinkedList.h"
#include <time.h>
#include "CB.h"

Status initPCBList(pPCBList *list) {
    (*list) = (pPCBList) malloc(sizeof(PCBList));
    (*list)->head = (pPCBNode) malloc(sizeof(PCBNode));
    (*list)->head->next = NULL;
    (*list)->count = 0;
}

Status insertPCB(pPCB p, pPCBList list) {
    PCBNode *pNode = (PCBNode *) malloc(sizeof(PCBNode));
    pNode->pcb = p;
    list->count++;
    if (list->count == 0) {
        list->head->next = pNode;
    } else {
        pPCBNode q = list->head->next;
        list->head->next = pNode;
        pNode->next = q;
    }
}

Status createPCB(pPCB *pcb, property ID, property priority, pPCBList pcbList, pList pReadyList) {
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
    addToReadyList(*pcb, pReadyList);
    insertPCB(*pcb, pcbList);
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
    (*pcbList)->head = (pPCBNode) malloc(sizeof(PCBNode));
    (*pcbList)->count = 0;
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
Status getResource(pPCB pcb, property RCBID, pRCBList list, pList pReadyList, pList pBlockedList) {
    property result = useRCB(pcb, RCBID, list);
    if (result == SUCCESS) {
        insertList(((*pcb).resUsing), RCBID, 0);
    } else if (result == BUSY) {
        pcb->status->stausID = BLOCKED;
        insertList(((*pcb).resRequest), RCBID, 0);
        findAndDelNode(&pReadyList, pcb->ID);
        addToBlockedList(pcb, pBlockedList);
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

Status addToReadyList(pPCB pcb, pList pReadyList) {
    pcb->status->stausID = READY;
    insertList(pReadyList, pcb->ID, pcb->priority);
}

Status addToBlockedList(pPCB pcb, pList pBlockedList) {
    pcb->status->stausID = BLOCKED;
    insertList(pBlockedList, pcb->ID, pcb->priority);
}

pPCB findPCBPointer(property PCBID, pPCBList list) {
    pPCBNode p = (list)->head->next;
    while (p) {
        if (p->pcb->ID == PCBID) {
            return p->pcb;
        } else {
            p = p->next;
        }
    }
}

Status showAllPCB(pPCBList list) {
    printf("ID\t\tPriority\tstatus");
    printf("\n");
    for (pPCBNode p = list->head->next; p != NULL; p = p->next) {
        printf("%-5d\t", p->pcb->ID);
        printf("%-5d\t\t", p->pcb->priority);
        printList(p->pcb->resUsing);
        printList(p->pcb->resRequest);
        switch (p->pcb->status->stausID) {
            case READY:
                printf("READY");
                break;
            case RUN:
                printf("RUN");
                break;
            case BLOCKED:
                printf("READY");
                break;
        }
        printf("\n");
    }
}

Status scheduler(pList pReadyList, pList pBlockedList, pPCBList pcbList, pRCBList rcblist) {
    while (TRUE) {
        sort(pReadyList);
        pPCB runPCB = findPCBPointer(pReadyList->head->next->id, pcbList);
        runPCB->status->stausID = RUN;
    }
}
