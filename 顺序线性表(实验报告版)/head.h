#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int status;
typedef int ElemType; //����Ԫ�����Ͷ���
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef struct {  //˳���˳��ṹ���Ķ���
    ElemType* elem;
    int length;
    int listsize;
}SqList;
typedef struct {  //���Ա�Ĺ������
    struct {
        char name[30];
        SqList L;
    } elem[10];
    int length;
    int listsize;
}LISTS;
