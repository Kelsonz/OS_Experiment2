//
// Created by 傅康 on 2019/12/13.
//
#include "exp2.h"

Status createPCBList(pPCBList *list) {
    (*list) = (pPCBList) malloc(sizeof(PCBList));
    if (!(*list)) {
        return ERROR;
    }
    (*list)->head = (pPCBNode) malloc(sizeof(PCBNode));
    if (!(*list)->head) {
        return ERROR;
    }
    (*list)->head->next = NULL;
    (*list)->count = 0;
    return OK;
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
    return OK;
}

Status createPCBStatus(pPCBStatus *pcbStatus) {
    (*pcbStatus) = (pPCBStatus) malloc(sizeof(PCBStatus));
    if (!*pcbStatus) {
        return ERROR;
    }
    (*pcbStatus)->stausID = READY;
    return OK;
}

Status createPCBTree(pPCBTree *pcbTree) {
    (*pcbTree) = (pPCBTree) malloc(sizeof(PCBTree));
    if (!*pcbTree) {
        return ERROR;
    }
    createPCBList(&((*pcbTree)->son));
    return OK;
}

Status destroyPCB(pPCB *pcb) {
    destroyPCBStatus(&((*pcb)->status));
    destroyPCBTree(&((*pcb)->pPTree));
    destroyRCBList(&((*pcb)->resUsing));
    destroyRCBList(&((*pcb)->resRequest));
    free(*pcb);
    return OK;
}


Status destroyPCBStatus(pPCBStatus *pcbStatus) {
    free(*pcbStatus);
    return OK;
}

Status destroyPCBTree(pPCBTree *pcbTree) {
    destroyPCBList(&((*pcbTree)->son));
    free(*pcbTree);
    return OK;
}

Status destroyPCBList(pPCBList *pcbList) {
    pPCBNode p = (*pcbList)->head;
    while (p->next) {
        pPCBNode q = p->next;
        free(p);
        p = q;
    }
    free(p);
    return OK;
}

Status insertPCB(pPCB p, pPCBList list) {
    PCBNode *pNode = (PCBNode *) malloc(sizeof(PCBNode));
    if (!pNode) {
        return ERROR;
    }
    pNode->pcb = p;
    pPCBNode q = list->head->next;
    list->head->next = pNode;
    pNode->next = q;
    list->count++;
    return OK;
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
    return OK;
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

pPCB getFirstPriorityPCB(pPCBList list) {
    pPCBNode p = list->head;
    for (; p->next != NULL; p = p->next);
    return p->pcb;
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
    return OK;
}

Status releaseResource(bool flag, pPCB pcb) {
    for (pRCBNode p = pcb->resUsing->head->next; p != NULL;) {
        pRCB rcb = p->rcb;
        p = p->next;
        findAndDelRCBNode(rcb, pcb->resUsing);
        rcb->isUse = NOTUSING;
        reloadRCB(flag, rcb);
    }
    return OK;
}

Status addToResUsingList(pPCB pcb, pRCB rcb) {
    insertRCB(rcb, pcb->resUsing);
    return OK;
}

Status removeFromReadyList(pPCB pcb, pPCBList pReadyList) {
    findAndDelPCBNode(pcb, pReadyList);
    return OK;
}

Status addToResRequest(pPCB pcb, pRCB rcb) {
    insertRCB(rcb, pcb->resRequest);
    return OK;
}

Status removeFromBlockedList(pPCB pcb, pPCBList pBlockedList) {
    findAndDelPCBNode(pcb, pBlockedList);
    return OK;
}

Status addToReadyList(pPCB pcb, pPCBList pReadyList) {
    pcb->status->stausID = READY;
    insertPCB(pcb, pReadyList);
    return OK;
}

Status addToBlockedList(pPCB pcb, pPCBList pBlockedList) {
    pcb->status->stausID = BLOCKED;
    insertPCB(pcb, pBlockedList);
    return OK;
}

Status addToRunList(pPCB pcb, pPCBList pRunList) {
    pcb->status->stausID = RUN;
    insertPCB(pcb, pRunList);
    return OK;
}

Status removeFromRunList(pPCB pcb, pPCBList pRunList) {
    findAndDelPCBNode(pcb, pRunList);
    return OK;
}

Status addToFinishList(pPCB pcb, pPCBList pFinishList) {
    pcb->status->stausID = FINISH;
    insertPCB(pcb, pFinishList);
    return OK;
}

Status printPCBList(pPCBList list) {
    for (pPCBNode p = list->head->next; p != NULL; p = p->next) {
        printPCB(p->pcb);
    }
    return OK;
}

Status scheduler(bool flag, pPCBList pReadyList, pPCBList pBlockedList, pPCBList pRunList, pPCBList pFinishList) {
    while (pReadyList->count != 0) {
        runPCB(flag, pReadyList, pBlockedList, pRunList);
        showAllPCB(pReadyList, pBlockedList, pRunList, pFinishList);
        finishPCB(flag, pReadyList, pBlockedList, pRunList, pFinishList);
    }
    showAllPCB(pReadyList, pBlockedList, pRunList, pFinishList);
    return OK;
}

Status runPCB(bool flag, pPCBList pReadyList, pPCBList pBlockedList, pPCBList pRunList) {
    int len = pReadyList->count;
    for (int i = 0; i < len; ++i) {
        pPCB run = NULL;
        switch (flag) {
            case PRIORITY:
                run = getMaxPriorityPCB(pReadyList);
                break;
            case FIFO:
                run = getFirstPriorityPCB(pReadyList);
                break;
        }
        removeFromReadyList(run, pReadyList);
        if (run->resRequest->count != 0) {
            addToBlockedList(run, pBlockedList);
        } else {
            addToRunList(run, pRunList);
        }
    }
    return OK;
}

Status finishPCB(bool flag, pPCBList pReadyList, pPCBList pBlockedList, pPCBList pRunList, pPCBList pFinishList) {
    for (pPCBNode p = pRunList->head->next; p != NULL; p = p->next) {
        releaseResource(flag, p->pcb);
        addToFinishList(p->pcb, pFinishList);
        removeFromRunList(p->pcb, pRunList);
    }
    for (pPCBNode p = pBlockedList->head->next; p != NULL; p = p->next) {
        if (p->pcb->resRequest->count == 0) {
            removeFromBlockedList(p->pcb, pBlockedList);
            addToReadyList(p->pcb, pReadyList);
        }
    }
    return OK;
}

Status showAllPCB(pPCBList pReadyList, pPCBList pBlockedList, pPCBList pRunList, pPCBList pFinishList) {
    printf("ID\t\tPriority\tstatus\t\tres_using\tres_req");
    printf("\n");
    printPCBList(pReadyList);
    printPCBList(pRunList);
    printPCBList(pBlockedList);
    printPCBList(pFinishList);
    printf("\n");
    return OK;
}

Status printPCB(pPCB pcb) {
    printf("%-5d\t", pcb->ID);
    printf("%-5d\t\t", pcb->priority);
    switch (pcb->status->stausID) {
        case READY:
            printf("READY");
            break;
        case RUN:
            printf("RUN\t");
            break;
        case BLOCKED:
            printf("BLOCKED");
            break;
        case FINISH:
            printf("FINISH");
            break;
    }
    printf("\t\t");
    if (pcb->resUsing->count == 0) {
        printf("NULL\t\t");
    } else {
        for (pRCBNode p = pcb->resUsing->head->next; p != NULL;) {
            pRCB rcb = p->rcb;
            printf("%d ", rcb->ID);
            p = p->next;
        }
        printf("\t\t");
    }
    if (pcb->resRequest->count == 0) {
        printf("NULL\t\t");
    } else {
        for (pRCBNode p = pcb->resRequest->head->next; p != NULL;) {
            pRCB rcb = p->rcb;
            printf("%d ", rcb->ID);
            p = p->next;
        }
        printf("\t\t");
    }
    printf("\n");
    return OK;
}
