//
// Created by 傅康 on 2019/12/13.
//
#include "LinkedList.h"
#include <time.h>
#include "CB.h"

Status createPCBList(pPCBList *list) {
    (*list) = (pPCBList) malloc(sizeof(PCBList));
    (*list)->head = (pPCBNode) malloc(sizeof(PCBNode));
    (*list)->head->next = NULL;
    (*list)->count = 0;
}

Status createPCB(pPCB *pcb, property ID, property priority, pPCBList pcbList, pPCBList pReadyList) {
    (*pcb) = (pPCB) malloc(sizeof(PCB));
    (*pcb)->priority = priority;
    (*pcb)->ID = ID;
    if (!(*pcb)) {
        return ERROR;
    }
    createPCBTree(&((*pcb)->pPTree));
    createPCBStatus(&((*pcb)->status));
    createRCBList(&((*pcb)->resUsing));
    createRCBList(&((*pcb)->resRequest));
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

Status destroyPCB(pPCB *pcb) {
    destroyPCBStatus(&((*pcb)->status));
    destroyPCBTree(&((*pcb)->pPTree));
    destroyRCBList(&((*pcb)->resUsing));
    destroyRCBList(&((*pcb)->resRequest));
    free(*pcb);
}


Status destroyPCBStatus(pPCBStatus *pcbStatus) {
    free(*pcbStatus);
}

Status destroyPCBTree(pPCBTree *pcbTree) {
    destroyPCBList(&((*pcbTree)->son));
    free(*pcbTree);
}

Status destroyPCBList(pPCBList *pcbList) {
    pPCBNode p = (*pcbList)->head;
    while (p->next) {
        pPCBNode q = p->next;
        free(p);
        p = q;
    }
    free(p);
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


Status findAndDelPCBNode(pPCB pcb, pPCBList list) {
    for (pPCBNode p = list->head; p != NULL; p = p->next) {
        if (p->next->pcb->ID == pcb->ID) {
            pPCBNode q = p->next;
            p->next = q->next;
            free(q);
            return OK;
        }
    }
}

Status setPriority(pPCB pcb) {
    return pcb->priority;
}

Status setStatus(pPCB pcb, property status) {
    pcb->status->stausID = status;
    return OK;
}

property getStatus(pPCB pcb) {
    return pcb->status->stausID;
}

pPCB getMaxPriorityPCB(pPCBList list) {
    pPCBNode max = list->head->next;
    for (pPCBNode p = list->head->next; p != NULL; p = p->next) {
        if (p->pcb->priority > max->pcb->priority) {
            max = p;
        }
    }
    return max->pcb;
}

//PCB申请资源
Status getResource(pPCB pcb, pRCB rcb, pRCBList list, pPCBList pReadyList, pPCBList pBlockedList) {
    addToBlockedList(pcb, pBlockedList);
    removeFromReadyList(pcb, pReadyList);
    property result = useRCB(pcb, rcb);
    if (result == SUCCESS) {
        addToResUsingList(pcb, rcb);
        addToReadyList(pcb, pReadyList);
    } else if (result == BUSY) {
        removeFromReadyList(pcb, pReadyList);
        addToResRequest(pcb, rcb);
    }
    return OK;
}

Status releaseResource(pPCB pcb) {
    for (pRCBNode p = pcb->resUsing->head->next; p != NULL; p = p->next) {
        pRCB rcb = p->rcb;
        findAndDelRCBNode(rcb, pcb->resUsing);
        pcb->resUsing->count--;
        reloadRCB(rcb);
    }
    pcb->status->stausID = FINISH;
}

Status addToResUsingList(pPCB pcb, pRCB rcb) {
    insertRCB(rcb, pcb->resUsing);
}

Status removeFromReadyList(pPCB pcb, pPCBList pReadyList) {
    findAndDelPCBNode(pcb, pReadyList);
}

Status addToResRequest(pPCB pcb, pRCB rcb) {
    insertRCB(rcb, pcb->resRequest);
}

Status removeFromBlockedList(pPCB pcb, pPCBList pBlockedList) {
    findAndDelPCBNode(pcb, pBlockedList);
}

Status addToReadyList(pPCB pcb, pPCBList pReadyList) {
    pcb->status->stausID = READY;
    insertPCB(pcb, pReadyList);
}

Status addToBlockedList(pPCB pcb, pPCBList pBlockedList) {
    pcb->status->stausID = BLOCKED;
    insertPCB(pcb, pBlockedList);
}

Status showAllPCB(pPCBList list) {
    printf("ID\t\tPriority\tstatus");
    printf("\n");
    for (pPCBNode p = list->head->next; p != NULL; p = p->next) {
        printf("%-5d\t", p->pcb->ID);
        printf("%-5d\t\t", p->pcb->priority);
        printRCBList(p->pcb->resUsing);
        printRCBList(p->pcb->resRequest);
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

Status scheduler(pPCBList pReadyList, pPCBList pBlockedList) {
    while (TRUE) {
        runPCB(pReadyList);
    }
}

Status runPCB(pPCBList pReadyList) {
    pPCB pcb = getMaxPriorityPCB(pReadyList);
    pcb->status->stausID = RUN;
    removeFromReadyList(pcb, pReadyList);
}