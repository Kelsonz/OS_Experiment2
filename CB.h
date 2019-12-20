//
// Created by 傅康 on 2019/12/20.
//

#ifndef OS_EXPERIMENT2_CB_H
#define OS_EXPERIMENT2_CB_H

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
//进程状态
#define READY 10
#define RUN 12
#define BLOCKED 13
//资源使用状态
#define USING 21
#define NOTUSING 22
#define BUSY 23
#define SUCCESS 24
typedef int property;
typedef struct status {
    property stausID;
} PCBStatus, *pPCBStatus;
typedef struct PCB {
    property ID;
    pList resUsing;
    pList resRequest;
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

typedef struct RCB {
    property ID;
    property isUse;
    pList waitPList;
} RCB, *pRCB;
typedef struct RCBNode {
    pRCB rcb;
    struct RCBNode *next;
} RCBNode, *pRCBNode;
typedef struct RCBList {
    pRCBNode head;
} RCBList, *pRCBList;
/*
 * PCB部分
 */
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
Status getResource(pPCB pcb, property RCBID, pRCBList *list, pList pReadyList, pList pBlockedList);

//获得当前进程的优先级
Status setPriority(pPCB pcb);

/*
 * RCB部分
 */
//初始化资源列表
Status initRCBList(pRCBList *list);

Status insertRCB(pRCB p, pRCBList *list);

//新建资源
Status createRCB(pRCB *p, property ID, pRCBList *list);

//使用资源
Status useRCB(pPCB pcb, property RCBIDpRCB, pRCBList *list);

//通过资源ID获得资源指针
pRCB getRCBPointer(property RCBID, pRCBList *list);

//资源列表长度
int lengthRCBList(pRCBList *list);

#endif //OS_EXPERIMENT2_CB_H
