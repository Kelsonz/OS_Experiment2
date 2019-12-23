//
// Created by 傅康 on 2019/12/13.
//
#include "exp2.h"

void exp();

int main() {
    exp();

}

void exp() {
    //    初始化资源列表
    pRCBList rcbList;
    createRCBList(&rcbList);

    pReadyList readyList;
    createPCBList(&readyList);
    pBlockedList blockedList;
    createPCBList(&blockedList);
    pRunList runList;
    createPCBList(&runList);
    pFinishList finishList;
    createPCBList(&finishList);

    pPCB A;
    createPCB(&A, 1, 1, readyList);
    pPCB B;
    createPCB(&B, 2, 5, readyList);
    pPCB C;
    createPCB(&C, 3, 4, readyList);
    pRCB R1;
    createRCB(&R1, 1, rcbList);
    pRCB R2;
    createRCB(&R2, 2, rcbList);
    pRCB R3;
    createRCB(&R3, 3, rcbList);
    pRCB R0;
    createRCB(&R0, 4, rcbList);

    useRCB(C, R2);
    useRCB(A, R1);
    useRCB(A, R2);
    useRCB(A, R3);
    useRCB(B, R2);

    scheduler(PRIORITY, readyList, blockedList, runList, finishList);

    destroyPCB(&A);
    destroyRCB(&R1);
}
