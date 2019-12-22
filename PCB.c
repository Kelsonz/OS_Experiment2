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

Status createPCB(pPCB *pcb, property ID, property priority, pPCBList pReadyList) {
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
            list->count--;
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
Status useRCB(pPCB pcb, pRCB rcb) {
    if (rcb->isUse == USING) {
        insertPCB(pcb, rcb->waitPList);
        addToResRequest(pcb, rcb);
    } else if (rcb->isUse == NOTUSING) {
        rcb->isUse = USING;
        addToResUsingList(pcb, rcb);
    }
}

Status releaseResource(pPCB pcb) {
    for (pRCBNode p = pcb->resUsing->head->next; p != NULL;) {
        pRCB rcb = p->rcb;
        p = p->next;
        findAndDelRCBNode(rcb, pcb->resUsing);
        rcb->isUse = NOTUSING;
        reloadRCB(rcb);
    }
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

Status addToRunList(pPCB pcb, pPCBList pRunList) {
    pcb->status->stausID = RUN;
    insertPCB(pcb, pRunList);
}

Status removeFromRunList(pPCB pcb, pPCBList pRunList) {
    findAndDelPCBNode(pcb, pRunList);
}

Status addToFinishList(pPCB pcb, pPCBList pFinishList) {
    pcb->status->stausID = FINISH;
    insertPCB(pcb, pFinishList);
}

Status printPCBList(pPCBList list) {
    for (pPCBNode p = list->head->next; p != NULL; p = p->next) {
        printPCB(p->pcb);
    }
}

Status showAllPCB(pPCBList pReadyList, pPCBList pBlockedList, pPCBList pRunList, pPCBList pFinishList) {
    printf("ID\t\tPriority\tstatus");
    printf("\n");
    printPCBList(pReadyList);
    printPCBList(pRunList);
    printPCBList(pBlockedList);
    printPCBList(pFinishList);
    printf("\n");
}

Status scheduler(pPCBList pReadyList, pPCBList pBlockedList, pPCBList pRunList, pPCBList pFinishList) {
    while (pReadyList->count != 0) {
        runPCB(pReadyList, pBlockedList, pRunList);
        showAllPCB(pReadyList, pBlockedList, pRunList, pFinishList);
        finishPCB(pReadyList, pBlockedList, pRunList, pFinishList);
    }
    showAllPCB(pReadyList, pBlockedList, pRunList, pFinishList);
}

Status runPCB(pPCBList pReadyList, pPCBList pBlockedList, pPCBList pRunList) {
    int len = pReadyList->count;
    for (int i = 0; i < len; ++i) {
        pPCB run = getMaxPriorityPCB(pReadyList);
        removeFromReadyList(run, pReadyList);
        if (run->resRequest->count != 0) {
            addToBlockedList(run, pBlockedList);
        } else {
            addToRunList(run, pRunList);
        }
    }
}

Status finishPCB(pPCBList pReadyList, pPCBList pBlockedList, pPCBList pRunList, pPCBList pFinishList) {
    for (pPCBNode p = pRunList->head->next; p != NULL; p = p->next) {
        releaseResource(p->pcb);
        addToFinishList(p->pcb, pFinishList);
        removeFromRunList(p->pcb, pRunList);
    }
    for (pPCBNode p = pBlockedList->head->next; p != NULL; p = p->next) {
        if (p->pcb->resRequest != 0) {
            removeFromBlockedList(p->pcb, pBlockedList);
            addToReadyList(p->pcb, pReadyList);
        }
    }
}

Status printPCB(pPCB pcb) {
    printf("%-5d\t", pcb->ID);
    printf("%-5d\t\t", pcb->priority);
    switch (pcb->status->stausID) {
        case READY:
            printf("READY");
            break;
        case RUN:
            printf("RUN");
            break;
        case BLOCKED:
            printf("BLOCKED");
            break;
        case FINISH:
            printf("FINISH");
            break;
    }
    printf("\n");
}