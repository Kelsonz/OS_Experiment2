//
// Created by 傅康 on 2019/12/20.
//

#ifndef OS_EXPERIMENT2_RCB_H
#define OS_EXPERIMENT2_RCB_H

#include <stdlib.h>
#include <stdio.h>
#include "PCB.h"
#include "LinkedList.h"

#define USING 21
#define NOTUSING 22
#define BUSY 23
#define SUCCESS 24
typedef struct RCB {
    property ID;
    property isUse;
    pList waitPList;
} RCB, *pRCB;
typedef struct RCBNode{
    pRCB rcb;
    struct RCBNode *next;
}RCBNode, *pRCBNode;
typedef struct RCBList{
    property head;
    pRCBNode next;
}RCBList, *pRCBList;
//初始化资源列表
static Status initRCBList(void);
static Status insertRCB(pRCB p);
//新建资源
Status createRCB(pRCB *p, property ID);

//使用资源
Status useRCB(pPCB pcb, property RCBID);
//通过资源ID获得资源指针
pRCB getRCBPointer(property RCBID);
//资源列表长度
static int lengthRCBList(void);
#endif //OS_EXPERIMENT2_RCB_H
