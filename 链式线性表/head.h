#pragma once
#pragma once
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define LISTINCREMENT 10
#define LIST_INIT_SIZE 100
typedef int Status;
typedef int ElemType;
//结点的结构定义，头指针的elem值为此链表元素的数量。
//采用带头结点的链表
typedef struct Lnode{
	ElemType elem;
	struct Lnode* next;
}Lnode, *LinkList,**PtrLinkList;