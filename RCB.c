//
// Created by 傅康 on 2019/12/13.
//
#include "RCB.h"

static pRCBList list;
static Status initRCBList(pRCBList* list){
    createList(list);
}
Status createRCB(pRCB *p, property ID) {
    (*p) = (pRCB) malloc(sizeof(RCB));
    (*p)->ID = ID;
    (*p)->isUse = NOTUSING;
    createList(&((*p)->waitPList));

    insertList(&list,(*p)->ID);
}

Status useRCB(pPCB pcb, property RCBID) {
    if (rcb->isUse == USING) {
        insertList(&(rcb->waitPList), pcb->ID);
        return BUSY;
    } else if (rcb->isUse == NOTUSING) {
        rcb->isUse = USING;
        return SUCCESS;
    }
}
//todo:完成这个函数的书写
pRCB getRCBPointer(property RCBID){

}