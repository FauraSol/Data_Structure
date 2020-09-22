#pragma once
#include"head.h"

//���ߺ���
Status Equal(ElemType, ElemType);
Status visit(ElemType);
void Show_Menu_Choice(int* choice);


//������������
Status InitList(PtrLinkList LH);
Status DestroyList(PtrLinkList LH);
Status ClearList(PtrLinkList LH);
Status ListEmpty(LinkList L);
int ListLength(LinkList L);
Status GetElem(LinkList L, int i, ElemType* e);
int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType));
Status PriorElem(LinkList L, ElemType cur_e, ElemType* pre_e);
Status NextElem(LinkList L, ElemType cur_e, ElemType* next_e);
Status ListInsert(PtrLinkList L, int i, ElemType e);
Status ListDelete(PtrLinkList L, int i, ElemType* e);
Status ListTraverse(LinkList L, Status(*visit)(ElemType));
Status SaveList(LinkList L, char* pFN);
Status LoadList(PtrLinkList L, char* pFN);
//������������


//��չ����
Status CreateList(LinkList*, int);
Status MergeLinkList(LinkList*, LinkList*, LinkList*);