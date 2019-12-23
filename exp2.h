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
//调度方式
#define FIFO 23
#define PRIORITY 24
//函数返回状态
#define OK 1
#define ERROR -1
//结构体中某属性的变量类型
typedef int property;
//函数返回值类型
typedef int Status;
//标志位类型
typedef int bool;
//进程状态的结构体
typedef struct status {
    property stausID;
} PCBStatus, *pPCBStatus;
/*
 * PCB结构体
 * 进程ID
 * RCB使用列表
 * RCB请求列表
 * 进程状态{READY, BLOCKED, RUN, FINISH}
 * 进程树
 * 优先级
 */
typedef struct PCB {
    property ID;
    struct RCBList *resUsing;
    struct RCBList *resRequest;
    pPCBStatus status;
    struct PCBTree *pPTree;
    property priority;
} PCB, *pPCB;
//进程队列的节点结构体
typedef struct PLNode {
    pPCB pcb;
    struct PLNode *next;
} PCBNode, *pPCBNode;
//进程队列的头部，包含一个计数变量
typedef struct PCBList {
    int count;
    PCBNode *head;
} PCBList, *pPCBList;
//进程运行队列
typedef pPCBList pRunList;
//进程就绪队列
typedef pPCBList pReadyList;
//进程阻塞队列
typedef pPCBList pBlockedList;
//进程完成队列
typedef pPCBList pFinishList;
// 进程树结构体
typedef struct PCBTree {
    pPCB father;
    pPCBList son;
} PCBTree, *pPCBTree;
/*
 * RCB结构体
 * RCBID
 * RCB使用状态{USING, NOTSUING}
 * 等待使用该RCB的PCB队列
 */
typedef struct RCB {
    property ID;
    property isUse;
    pPCBList waitPList;
} RCB, *pRCB;
//RCB队列结构体
typedef struct RCBNode {
    pRCB rcb;
    struct RCBNode *next;
} RCBNode, *pRCBNode;
//RCB队列头部，包括一个计数变量
typedef struct RCBList {
    int count;
    pRCBNode head;
} RCBList, *pRCBList;

/*
 * PCB部分
 * 1 创建
 * 创建PCB结构体
 * 创建进程状态结构体
 * 创建进程树
 * 创建进程队列
 * 2 销毁
 * 销毁进程
 * 销毁进程状态
 * 销毁进程树
 * 销毁进程队列
 * 3 获得指针
 * 获得进程队列中优先级最大的PCB的指针
 * 获得进程队列最先加入的PCB的指针
 * 4 增删
 * 进程加入队列
 * 进程退出队列
 * 进程加入就绪队列
 * 进程退出就绪队列
 * 进程加入阻塞队列
 * 进程退出阻塞队列
 * 进程加入运行队列
 * 进程退出运行队列
 * 进程加入完成队列
 * 5 资源使用
 * 申请资源
 * 释放PCB占用的所有资源
 * 加入PCB资源使用队列
 * 加入PCB资源请求队列
 * 6 调度
 * 调度
 * PCB运行判断
 * PCB完成判断
 * 7 打印
 * 打印PCB
 * 打印进程队列
 * 打印所有队列
 */
//创建进程
Status createPCB(pPCB *pcb, property ID, property priority, pPCBList pReadyList);

//创建进程状态
Status createPCBStatus(pPCBStatus *pcbStatus);

//创建进程树
Status createPCBTree(pPCBTree *pcbTree);

//创建进程队列
Status createPCBList(pPCBList *pcbList);

//销毁进程
Status destroyPCB(pPCB *pcb);

//销毁进程状态
Status destroyPCBStatus(pPCBStatus *pcbStatus);

//销毁进程树
Status destroyPCBTree(pPCBTree *pcbTree);

//销毁进程队列
Status destroyPCBList(pPCBList *pcbList);

//获得PCB队列中优先级最大的进程的指针
pPCB getMaxPriorityPCB(pPCBList pcbList);

//获得进程队列最先加入的PCB的指针
pPCB getFirstPriorityPCB(pPCBList pcbList);

//将创建的PCB加入到PCB表中
Status insertPCB(pPCB p, pPCBList list);

//将进程移除进程队列
Status findAndDelPCBNode(pPCB pcb, pPCBList list);

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

//进程申请资源
Status useRCB(pPCB pcb, pRCB rcb);

//释放进程所有资源
Status releaseResource(bool flag, pPCB pcb);

//调度
Status scheduler(bool flag, pPCBList pReadyList, pPCBList pBlockedList, pPCBList pRunList, pPCBList pFinishList);

//运行就绪列表第一个进程
Status runPCB(bool flag, pPCBList pReadyList, pPCBList pBlockedList, pPCBList pRunList);

//进程结束
Status finishPCB(bool flag, pPCBList pReadyList, pPCBList pBlockedList, pPCBList pRunList, pPCBList pFinishList);

//打印进程信息
Status printPCB(pPCB pcb);

//打印所有进程
Status showAllPCB(pPCBList pReadyList, pPCBList pBlockedList, pPCBList pRunList, pPCBList pFinishList);

//打印进程队列
Status printPCBList(pPCBList list);

/*
 * RCB部分
 * 1 创建
 * 创建资源列表
 * 创建资源
 * 2 销毁
 * 销毁资源
 * 销毁资源列表
 * 3 增删
 * 将资源插入到资源队列中
 * 删除资源队列中资源
 * 将资源放入资源请求队列中
 * 将资源放入资源使用队列中
 * 4 重载
 * 重载资源
 * 5 打印
 * 打印资源列表
 */

//创建资源列表
Status createRCBList(pRCBList *list);

//新建资源
Status createRCB(pRCB *p, property ID, pRCBList list);

//销毁资源
Status destroyRCB(pRCB *p);

//销毁资源列表
Status destroyRCBList(pRCBList *list);

//将创建的RCB加入到资源列表中
Status insertRCB(pRCB p, pRCBList list);

//资源退出队列
Status findAndDelRCBNode(pRCB rcb, pRCBList rcbList);

//将得到并且正在占用的资源放到该PCB的resUsing列表中
Status addToResUsingList(pPCB pcb, pRCB rcb);

//将得不到的资源放到该PCB的resRequest列表中
Status addToResRequest(pPCB pcb, pRCB rcb);

//重载资源，当当前资源被释放后，将其使用权交给等待队列中的进程
Status reloadRCB(bool flag, pRCB rcb);

//打印资源队列
Status showAllRCB(pRCBList list);


#endif //OS_EXPERIMENT2_EXP2_H
