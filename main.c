//
// Created by 傅康 on 2019/12/13.
//
#include "LinkedList.h"
#include "CB.h"

int main() {
    pPCB A;
    pRCB R1;
    pRCBList list;
    initRCBList(&list);
    createPCB(&A, 121, 1);
    createRCB(&R1, 1, &list);
}
