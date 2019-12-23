//
// Created by 傅康 on 2019/12/13.
//
#include "exp2.h"

//创建进程
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
//    完成初始化后将资源加入就绪队列
    addToReadyList(*pcb, pReadyList);
    return OK;
}

//创建进程队列
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
//    进程队列头部计数变量count初始化为0
    (*list)->count = 0;
    return OK;
}

//创建进程状态结构体
Status createPCBStatus(pPCBStatus *pcbStatus) {
    (*pcbStatus) = (pPCBStatus) malloc(sizeof(PCBStatus));
    if (!*pcbStatus) {
        return ERROR;
    }
    (*pcbStatus)->stausID = READY;
    return OK;
}

//创建进程树结构体
Status createPCBTree(pPCBTree *pcbTree) {
    (*pcbTree) = (pPCBTree) malloc(sizeof(PCBTree));
    if (!*pcbTree) {
        return ERROR;
    }
    createPCBList(&((*pcbTree)->son));
    return OK;
}

//销毁进程
Status destroyPCB(pPCB *pcb) {
    destroyPCBStatus(&((*pcb)->status));
    destroyPCBTree(&((*pcb)->pPTree));
    destroyRCBList(&((*pcb)->resUsing));
    destroyRCBList(&((*pcb)->resRequest));
    free(*pcb);
    return OK;
}

//销毁进程状态
Status destroyPCBStatus(pPCBStatus *pcbStatus) {
    free(*pcbStatus);
    return OK;
}

//销毁进程树
Status destroyPCBTree(pPCBTree *pcbTree) {
    destroyPCBList(&((*pcbTree)->son));
    free(*pcbTree);
    return OK;
}

//销毁进程列表
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

//进程队列中插入进程
//采用头插法
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

//进程队列中删除进程
//寻找该节点并删除
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

//获得进程队列中优先级最大的PCB的指针
pPCB getMaxPriorityPCB(pPCBList list) {
    pPCBNode max = list->head->next;
    for (pPCBNode p = list->head->next; p != NULL; p = p->next) {
        if (p->pcb->priority > max->pcb->priority) {
            max = p;
        }
    }
    return max->pcb;
}

//获得进程队列最先加入的PCB的指针
//也就是链表的尾节点
pPCB getFirstPriorityPCB(pPCBList list) {
    pPCBNode p = list->head;
    for (; p->next != NULL; p = p->next);
    return p->pcb;
}

//进程加入就绪队列
Status addToReadyList(pPCB pcb, pPCBList pReadyList) {
    pcb->status->stausID = READY;
    insertPCB(pcb, pReadyList);
    return OK;
}

//进程退出就绪队列
Status removeFromReadyList(pPCB pcb, pPCBList pReadyList) {
    findAndDelPCBNode(pcb, pReadyList);
    return OK;
}

//进程加入阻塞队列
Status addToBlockedList(pPCB pcb, pPCBList pBlockedList) {
    pcb->status->stausID = BLOCKED;
    insertPCB(pcb, pBlockedList);
    return OK;
}

//进程退出阻塞队列
Status removeFromBlockedList(pPCB pcb, pPCBList pBlockedList) {
    findAndDelPCBNode(pcb, pBlockedList);
    return OK;
}

//进程加入运行队列
Status addToRunList(pPCB pcb, pPCBList pRunList) {
    pcb->status->stausID = RUN;
    insertPCB(pcb, pRunList);
    return OK;
}

//进程退出运行队列
Status removeFromRunList(pPCB pcb, pPCBList pRunList) {
    findAndDelPCBNode(pcb, pRunList);
    return OK;
}

//进程加入完成队列
Status addToFinishList(pPCB pcb, pPCBList pFinishList) {
    pcb->status->stausID = FINISH;
    insertPCB(pcb, pFinishList);
    return OK;
}

//释放PCB占用的所有资源
//删除PCB资源使用队列中的所有RCB，恢复RCB的未使用的状态，并且重载该RCB
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

//PCB申请资源
//如果资源被占用，将该PCB加入当前RCB的等待队列，同时将该RCB加入PCB的资源请求队列
//如果资源未被占用，占用该资源并将其加入PCB的资源使用队列
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

//调度
//FIFO方式：按照先来后到的顺序进行调度
//PRIORITY方式：按照优先级高低进程调度
Status scheduler(bool flag, pPCBList pReadyList, pPCBList pBlockedList, pPCBList pRunList, pPCBList pFinishList) {
    while (pReadyList->count != 0) {
        runPCB(flag, pReadyList, pBlockedList, pRunList);
        showAllPCB(pReadyList, pBlockedList, pRunList, pFinishList);
        finishPCB(flag, pReadyList, pBlockedList, pRunList, pFinishList);
    }
    showAllPCB(pReadyList, pBlockedList, pRunList, pFinishList);
    return OK;
}

//PCB运行判断
//依次判断就绪队列中进程的资源请求队列的长度是否为空
//如果为空说明资源已经申请到位，从就绪队列中删除并加入运行队列
//否则从就绪队列中删除并加入阻塞队列
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

//PCB完成判断
//依次释放运行队列中所有PCB占用的所有资源，将进程从运行队列中删除，加入完成队列
//将阻塞队列中资源请求列表长度为空的进程从阻塞队列中删除，加入就绪队列
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

//打印进程信息
//包括ID、优先级、状态、资源使用列表、资源请求列表
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

//打印进程列表
Status printPCBList(pPCBList list) {
    for (pPCBNode p = list->head->next; p != NULL; p = p->next) {
        printPCB(p->pcb);
    }
    return OK;
}

//打印所有进程列表
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
