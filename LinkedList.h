//
// Created by 傅康 on 2019/12/13.
//

#ifndef OS_EXPERIMENT2_LINKEDLIST_H
#define OS_EXPERIMENT2_LINKEDLIST_H
#include <stdlib.h>
#include <stdio.h>

#define OK 1
#define ERROR -2
#define OVERFLOW -1
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
Status createNode(pNode *p, Element id);

// 初始化表
Status createList(pList *L);

// 获得表的长度
int lenList(pList L);

// 使用尾插法插入数据
Status insertList(pList *L, Element id);

// 删除数据
Status destroyList(pList *L);
Status delNode(pList *L);

// 打印表
Status printList(pList L);
#endif //OS_EXPERIMENT2_LINKEDLIST_H
