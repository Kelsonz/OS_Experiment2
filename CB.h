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
} PCBLNode, *pPCBNode;
typedef struct PCBList {
    int count;
    PCBLNode *head;
} PCBList, *pPCBList;
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
    int count;
    pRCBNode head;
} RCBList, *pRCBList;
/*
 * PCB部分
 */
//创建进程
Status createPCB(pPCB *pcb, property ID, property priority, pList pReadyList);

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

//释放资源
Status releaseResource(pPCB pcb, property RCBID, pRCBList *list, pList pReadyList, pList pBlockedList);

//加入就绪队列
Status addToReadyList(pPCB pcb, pList *pReadyList);

//撤出就绪队列
Status quitFromReadyList(pPCB pcb, pList *pReadyList, property status);

//加入阻塞队列
Status addToBlockedList(pPCB pcb, pList *pBlockedList);

//撤出阻塞队列
Status quitFromBlockedList(pPCB pcb, pList *pBlockedList, property status);

//调度
Status scheduler(pList pReadyList, pList pBlockedList);


/*
 * RCB部分
 */
//初始化资源列表
Status initRCBList(pRCBList *list);

Status insertRCB(pRCB p, pRCBList list);

//新建资源
Status createRCB(pRCB *p, property ID, pRCBList list);

Status destroyRCB(pRCB *p);

//使用资源
Status useRCB(pPCB pcb, property RCBID, pRCBList list);

//释放资源
Status releaseRCB(pPCB pcb, property RCBID, pRCBList *list);

//通过资源ID获得资源指针
pRCB getRCBPointer(property RCBID, pRCBList list);


#endif //OS_EXPERIMENT2_CB_H
