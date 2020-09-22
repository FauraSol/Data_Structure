#pragma once
#include"head.h"
//工具函数
Status Equal(ElemType a, ElemType b);
Status visit(ElemType*);
Status Display(SqList L);
void Show_Menu_Choice(int*);


//基本算法
Status InitList(PtrSqList L);
Status DestroyList(PtrSqList L);
Status ClearList(PtrSqList L);
Status ListEmpty(SqList L);
int ListLength(SqList L);
Status GetElem(SqList L, int i, ElemType* e);
Status LocateElem(SqList L, ElemType e, Status(*compare)(ElemType, ElemType));
Status PriorElem(SqList L, ElemType cur_e, ElemType* pre_e);
Status NextElem(SqList L, ElemType cur_e, ElemType* next_e);
Status ListInsert(PtrSqList L, int i, ElemType e);
Status ListDelete(PtrSqList L, int i, ElemType* e);
Status ListTraverse(SqList L, Status (*visit)(ElemType*));
Status SaveList(SqList L, char* pFN);
Status LoadList(PtrSqList L, char* pFN);


//拓展算法
Status Union(PtrSqList La, SqList Lb);
Status MergeList_1(SqList La, SqList Lb, PtrSqList Lc);
Status MergeList_2(SqList La, SqList Lb, PtrSqList Lc);


