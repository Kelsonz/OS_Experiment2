//
// Created by 傅康 on 2019/12/20.
//

#ifndef OS_EXPERIMENT2_EXP2_H
#define OS_EXPERIMENT2_EXP2_H

#include <stdio.h>
#include <stdlib.h>

//进程状态
#define READY 10
#define RUN 12
#define BLOCKED 13
#define FINISH 14
//资源使用状态
#define USING 21
#define NOTUSING 22
#define FIFO 23
#define PRIORITY 24
#define OK 1
#define ERROR -1
typedef int property;
typedef int Status;
typedef int bool;
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
typedef pPCBList pRunList;
typedef pPCBList pReadyList;
typedef pPCBList pBlockedList;
typedef pPCBList pFinishList;
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
Status createPCB(pPCB *pcb, property ID, property priority, pPCBList pReadyList);

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

pPCB getFirstPriorityPCB(pPCBList pcbList);

//将进程移除进程队列
Status findAndDelPCBNode(pPCB pcb, pPCBList list);

//进程申请资源
Status useRCB(pPCB pcb, pRCB rcb);


//释放进程所有资源
Status releaseResource(bool flag, pPCB pcb);

//加入就绪队列
Status addToReadyList(pPCB pcb, pPCBList pReadyList);

//退出就绪队列
Status removeFromReadyList(pPCB pcb, pPCBList pReadyList);

//加入阻塞队列
Status addToBlockedList(pPCB pcb, pPCBList pBlockedList);

//退出阻塞队列
Status removeFromBlockedList(pPCB pcb, pPCBList pBlockedList);

//加入运行队列
Status addToRunList(pPCB pcb, pPCBList pRunList);

//退出运行队列
Status removeFromRunList(pPCB pcb, pPCBList pRunList);

//加入完成队列
Status addToFinishList(pPCB pcb, pPCBList pFinishList);

//调度
Status scheduler(bool flag, pPCBList pReadyList, pPCBList pBlockedList, pPCBList pRunList, pPCBList pFinishList);

//将创建的PCB加入到PCB表中
Status insertPCB(pPCB p, pPCBList list);

//打印所有进程
Status showAllPCB(pPCBList pReadyList, pPCBList pBlockedList, pPCBList pRunList, pPCBList pFinishList);

//打印进程队列
Status printPCBList(pPCBList list);

//运行就绪列表第一个进程
Status runPCB(bool flag, pPCBList pReadyList, pPCBList pBlockedList, pPCBList pRunList);

//进程结束
Status finishPCB(bool flag, pPCBList pReadyList, pPCBList pBlockedList, pPCBList pRunList, pPCBList pFinishList);

//打印进程信息
Status printPCB(pPCB pcb);

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

//重载资源，当当前资源被释放后，将其使用权交给等待队列中的进程
Status reloadRCB(bool flag, pRCB rcb);

//将得到并且正在占用的资源放到该PCB的resUsing列表中
Status addToResUsingList(pPCB pcb, pRCB rcb);

//资源退出队列
Status findAndDelRCBNode(pRCB rcb, pRCBList rcbList);

//将得不到的资源放到该PCB的resRequest列表中
Status addToResRequest(pPCB pcb, pRCB rcb);

//打印资源队列
Status showAllRCB(pRCBList list);


#endif //OS_EXPERIMENT2_EXP2_H
