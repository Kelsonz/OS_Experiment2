//
// Created by 傅康 on 2019/12/13.
//

#ifndef OS_EXPERIMENT2_EXPERIMENT_H
#define OS_EXPERIMENT2_EXPERIMENT_H
#include <stdlib.h>
#include <stdio.h>

#define OK 1
typedef int Element;
typedef int Status;

typedef struct list {
    struct node *head;
} List, *pList;
typedef struct node {
    Element id;
    struct node *next;
} Node, *pNode;

// 创建节点
Status Node_Create(pNode *p, Element id);

// 初始化表
Status List_Init(pList *L);

// 获得表的长度
int List_len(pList L);

// 使用尾插法插入数据
Status List_Insert(pList *L, Element id);

// 删除数据
Status List_Del(pList *L);

// 打印表
Status List_Print(pList L);
#endif //OS_EXPERIMENT2_EXPERIMENT_H
