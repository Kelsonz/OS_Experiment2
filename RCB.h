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
typedef List RCBList;
typedef pList pRCBList;
//初始化资源列表
static Status initRCBList(pRCBList* list);
//新建资源
Status createRCB(pRCB *p, property ID);

//使用资源
Status useRCB(pPCB pcb, property RCBID);

pRCB getRCBPointer(property RCBID);

#endif //OS_EXPERIMENT2_RCB_H
