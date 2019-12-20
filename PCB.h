//
// Created by 傅康 on 2019/12/20.
//

#ifndef OS_EXPERIMENT2_PCB_H
#define OS_EXPERIMENT2_PCB_H

#include "LinkedList.h"
#include <stdio.h>
#include <stdlib.h>

#define READY 10
#define READYSUSPEND 11
#define RUN 12
#define BLOCKED 13
#define BLOCKEDSUSPEND 14

typedef int property;
typedef struct status {
    property stausID;
} PCBStatus, *pPCBStatus;
typedef struct PCB {
    property ID;
    pList resource;
    pPCBStatus status;
    struct PCBTree *pPTree;
    property priority;
} PCB, *pPCB;
// 子进程链表
typedef struct PLNode {
    pPCB PPointer;
    struct PLNode *next;
} PCBLNode, *pPCBNode, *pPCBList;
// 进程树
typedef struct PCBTree {
    pPCB father;
    pPCBList son;
} PCBTree, *pPCBTree;

//创建进程
Status createPCB(pPCB *pcb, property ID, property priority);

//创建进程状态
Status createPCBStatus(pPCBStatus *pcbStatus);

//创建进程树
Status createPCBTree(pPCBTree *pcbTree);

Status createPCBList(pPCBList *pcbList);

//销毁进程
Status destroyPCB(pPCB *pcb);

//销毁进程状态
Status destroyPCBStatus(pPCBStatus *pcbStatus);

//销毁进程树
Status destroyPCBTree(pPCBTree *pcbTree);

//销毁子进程链表
Status destoryPCBList(pPCBList *pcbList);

//获得子进程链表长度
int lengthPCBList(pPCBList list);

//设置进程状态
Status setStatus(pPCB pcb, property status);

//获得进程状态
property getStatus(pPCB pcb);
//进程申请资源
Status getResource(pPCB pcb, property RCBID);
//获得当前进程的优先级
Status setPriority(pPCB pcb);
#endif //OS_EXPERIMENT2_PCB_H
