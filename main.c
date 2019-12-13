//
// Created by 傅康 on 2019/12/13.
//
#include "Experiment.h"

int main() {
    pList L;
    List_Init(&L);
//  使用尾插法建立单链表
    List_Insert(&L, 1);
    List_Insert(&L, 2);
    List_Insert(&L, 3);
    List_Insert(&L, 4);
    List_Print(L);
}