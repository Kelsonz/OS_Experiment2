//
// Created by 傅康 on 2019/12/13.
//
#include "LinkedList.h"
#include "CB.h"

int main() {
//    初始化资源列表
    pRCBList list;
    initRCBList(&list);
//    初始化就绪队列
    pReadyList readyList;
    createList(&readyList);
//    初始化阻塞队列
    pBlockedList blockedList;
    createList(&blockedList);

    pPCB A;
    createPCB(&A, 121, 1, readyList);
    pPCB B;
    createPCB(&A, 14, 5, readyList);
    pRCB R1;
    createRCB(&R1, 1, list);
    pRCB R2;
    createRCB(&R2, 2, list);
    pRCB R3;
    createRCB(&R3, 3, list);

    useRCB(A, 1, list);
    useRCB(A, 2, list);
    useRCB(B, 1, list);

    destroyPCB(&A);
    destroyRCB(&R1);
}
