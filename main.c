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
    pPCB B;
    pPCB C;
    createPCB(&A, 1, 1, readyList);
    createPCB(&B, 2, 5, readyList);
    createPCB(&C, 3, 4, readyList);

    pRCB R0;
    pRCB R1;
    pRCB R2;
    pRCB R3;
    createRCB(&R0, 4, rcbList);
    createRCB(&R1, 1, rcbList);
    createRCB(&R2, 2, rcbList);
    createRCB(&R3, 3, rcbList);

    useRCB(C, R2);
    useRCB(A, R1);
    useRCB(A, R2);
    useRCB(A, R3);
    useRCB(B, R2);

    scheduler(PRIORITY, readyList, blockedList, runList, finishList);

    destroyPCB(&A);
    destroyPCB(&B);
    destroyRCB(&R1);
}
