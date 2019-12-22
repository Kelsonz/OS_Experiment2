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
#define FINISH 14
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
    struct RCBList *resUsing;
    struct RCBList *resRequest;
    pPCBStatus status;
    struct PCBTree *pPTree;
    property priority;
} PCB, *pPCB;
// 子进程链表
typedef struct PLNode {
    pPCB pcb;
    struct PLNode *next;
} PCBNode, *pPCBNode;
typedef struct PCBList {
    int count;
    PCBNode *head;
} PCBList, *pPCBList;
typedef pPCBList pReadyList;
typedef pPCBList pBlockedList;
// 进程树
typedef struct PCBTree {
    pPCB father;
    pPCBList son;
} PCBTree, *pPCBTree;

typedef struct RCB {
    property ID;
    property isUse;
    pPCBList waitPList;
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
Status createPCB(pPCB *pcb, property ID, property priority, pPCBList pcbList, pPCBList pReadyList);

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
Status destroyPCBList(pPCBList *pcbList);

//获得PCB队列中优先级最大的进程的指针
pPCB getMaxPriorityPCB(pPCBList pcbList);

//将进程移除进程队列
Status findAndDelPCBNode(pPCB pcb, pPCBList list);

//设置进程状态
Status setStatus(pPCB pcb, property status);

//获得进程状态
property getStatus(pPCB pcb);

//进程申请资源
Status getResource(pPCB pcb, pRCB rcb, pRCBList list, pPCBList pReadyList, pPCBList pBlockedList);

//获得当前进程的优先级
Status setPriority(pPCB pcb);

//释放进程所有资源
Status releaseResource(pPCB pcb);

//加入就绪队列
Status addToReadyList(pPCB pcb, pPCBList pReadyList);

//退出就绪队列
Status removeFromReadyList(pPCB pcb, pPCBList pReadyList);

//加入阻塞队列
Status addToBlockedList(pPCB pcb, pPCBList pBlockedList);

//退出阻塞队列
Status removeFromBlockedList(pPCB pcb, pPCBList pBlockedList);

//调度
Status scheduler(pPCBList pReadyList, pPCBList pBlockedList);

//将创建的PCB加入到PCB表中
Status insertPCB(pPCB p, pPCBList list);

//打印所有进程
Status showAllPCB(pPCBList list);

//运行就绪列表第一个进程
Status runPCB(pPCBList pReadyList);



/*
 * RCB部分
 */

//初始化资源列表
Status createRCBList(pRCBList *list);

//销毁资源列表
Status destroyRCBList(pRCBList *list);

//将创建的RCB加入到资源列表中
Status insertRCB(pRCB p, pRCBList list);

//新建资源
Status createRCB(pRCB *p, property ID, pRCBList list);

Status destroyRCB(pRCB *p);

//使用资源
Status useRCB(pPCB pcb, pRCB rcb);

//重载资源，当当前资源被释放后，将其使用权交给等待队列中的进程
Status reloadRCB(pRCB rcb);

//将得到并且正在占用的资源放到该PCB的resUsing列表中
Status addToResUsingList(pPCB pcb, pRCB rcb);

//资源退出队列
Status findAndDelRCBNode(pRCB rcb, pRCBList rcbList);

//将得不到的资源放到该PCB的resRequest列表中
Status addToResRequest(pPCB pcb, pRCB rcb);

//打印资源队列
Status printRCBList(pRCBList list);


#endif //OS_EXPERIMENT2_CB_H
