//
// Created by 傅康 on 2019/12/13.
//
#include "LinkedList.h"
#include "CB.h"

void exp();

void list();

int main() {
    exp();
//    list();
}

void exp() {
    //    初始化资源列表
    pRCBList rcbList;
    initRCBList(&rcbList);
    pPCBList pcbList;
    initPCBList(&pcbList);
//    初始化就绪队列
    pReadyList readyList;
    createList(&readyList);
//    初始化阻塞队列
    pBlockedList blockedList;
    createList(&blockedList);

    pPCB A;
    createPCB(&A, 155, 1, pcbList, readyList);
    pPCB B;
    createPCB(&B, 14, 555, pcbList, readyList);
    pRCB R1;
    createRCB(&R1, 1, rcbList);
    pRCB R2;
    createRCB(&R2, 2, rcbList);
    pRCB R3;
    createRCB(&R3, 3, rcbList);

    useRCB(A, 1, rcbList);
    useRCB(A, 2, rcbList);
    useRCB(B, 1, rcbList);

    showAllPCB(pcbList);
    destroyPCB(&A);
    destroyRCB(&R1);
}

void list() {
    pList list;
    createList(&list);
    insertList(list, 1, 1);
    insertList(list, 2, 2);
    insertList(list, 5, 5);
    insertList(list, -2, -2);
    insertList(list, 9, 9);
    insertList(list, 14, 14);
    insertList(list, 0, 0);
    printList(list);
    sort(list);
    printList(list);
}