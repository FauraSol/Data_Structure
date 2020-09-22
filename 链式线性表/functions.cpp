#include"LinkList.h"

//剩余删除未调试成功

//工具函数的定义
Status Equal(ElemType a, ElemType b) {
	//由于这里ElemType为int，所以直接使用内置运算符==
	if (a == b) return TRUE;
	else return FALSE;
}
Status visit(ElemType a) {
	printf("The element visited is %d.\n", a);
	return OK;
}
void Show_Menu_Choice(int* choice) {
	//显示菜单并读取选项
	printf("\tMenu for Linear Table On Sequence Structure\n");
	printf("-----------------------------------------------------------\n");
	printf("\t1.InitList\t\t8.PriorElem\n");
	printf("\t2.DestroyList\t\t9.NextElem\n");
	printf("\t3.ClearList\t\t10.ListInsert\n");
	printf("\t4.ListEmpty\t\t11.ListDelete\n");
	printf("\t5.ListLength\t\t12.ListTrabverse\n");
	printf("\t6.GetElem\t\t13.SaveData\n");
	printf("\t7.LocateElem\t\t14.DataLoading\n");
	printf("\t0.Exit\n");
	printf("-----------------------------------------------------------\n");
	printf("请选择你的操作[0~14]：");
	scanf("%d", choice);
}


Status InitList(PtrLinkList PL) {
	//创建空的带头指针的链式线性表，并检测是否成功分配空间
	//*PL即为头结点
	*PL = (LinkList)malloc(sizeof(Lnode));
	if (!*PL) return ERROR;
	(*PL)->elem = 0;
	(*PL)->next = NULL;
	return OK;
}
Status DestroyList(PtrLinkList PL) {
	//检测链表存在，如果存在销毁包括头结点在内的每一个元素
	if (!*PL) return ERROR;
	LinkList p = (*PL), q = p;
	while (p) {
		p = p->next;
		free(q);
		q = p;
	}
	(*PL) = NULL;
	return OK;
}
Status ClearList(PtrLinkList PL) {
	//检测链表存在，如果存在清空链表(销毁除了头结点之外的其他元素)
	if (!*PL) return ERROR;
	//已经为空
	if (!(*PL)->next) return OK;
	/*令p，q均指向第一个元素，随后循环释放每一个元素的空间，将首结点的elem设为0*/
	LinkList p = (*PL)->next, q = p;
	while (p->next) {
		q = p->next;
		free(p);
		p = q;
	}
	free(p);
	(*PL)->elem = 0;
	(*PL)->next = NULL;
	return OK;
}
Status ListEmpty(LinkList L) {
	//检测链表是否存在，并通过检测首结点元素的方式判断是否非空
	if (!L) return ERROR;
	LinkList p = L->next;
	if (p) return FALSE;
	else return TRUE;
}
int ListLength(LinkList L) {
	//检测链表是否存在，并遍历链表并且返回链表长度
	if (!L) return ERROR;
	LinkList p = L->next;
	int cnt = 0;
	while (p) {
		p = p->next;
		++cnt;
	}
	return cnt;
}
Status GetElem(LinkList L, int i, ElemType* e) {
	//检测链表是否存在以及i是否超出链表长度
	//用e取出链表的第i个元素
	if (!L) return FALSE;
	if (i > ListLength(L)) return OVERFLOW;
	LinkList p = L->next;
	int j = 1;
	while (p && j < i) {
		p = p->next;
		++j;
	}
	if (!p || j > i) return ERROR;
	*e = p->elem;
	return OK;
}
int LocateElem(LinkList L, ElemType e, Status(*compare)(ElemType, ElemType)) {
	if (!L) return FALSE;
	LinkList p = L->next;
	int i = 1;
	while (p) {
		if (compare(p->elem, e)) {
			return i;
		}
		++i;
		p = p->next;
	}
	if (!p) return ERROR;
}
Status PriorElem(LinkList L, ElemType cur_e, ElemType* pre_e) {
	//检查链表存在，得到前趋结点
	if (!L) return FALSE;
	LinkList p = L;
	while (p->next) {
		if (Equal(cur_e, p->next->elem)) {
			*pre_e = p->elem;
			return OK;
		}
		p = p->next;
	}
	return FALSE;
}
Status NextElem(LinkList L, ElemType cur_e, ElemType* next_e) {
	//检查链表存在，得到后继节点
	if (!L) return FALSE;
	LinkList p = L->next;
	while (p) {
		if (Equal(cur_e, p->elem)) {
			//排除找到的是最后一个元素的情况
			if (!p->next) return ERROR;
			else {
				*next_e = p->next->elem;
				return OK;
			}
		}
		p = p->next;
	}
	return FALSE;
}
Status ListInsert(PtrLinkList PL, int i, ElemType e) {
	//检验链表存在以及序数的合法性，将e插入到序数i处
	if (!(*PL)) return ERROR;
	if (i > ListLength(*PL)+1) return OVERFLOW;
	//在链表内部进行插入
	LinkList p = (*PL);
	int j = 0;
	//寻找第i-1个结点
	while (p && j < i - 1) {
		p = p->next;
		++j;
	}
	if (!p || j > i) return ERROR;
	//创建新节点
	LinkList s = (LinkList)malloc(sizeof(Lnode));
	//完成插入操作
	if (!s) return OVERFLOW;
	s->next = p->next;
	s->elem = e;
	p->next = s;
	return OK;
}
Status ListDelete(PtrLinkList PL, int i, ElemType* e) {
	//检验链表存在以及序数i的合法性，删除序数i处的元素
	if (!(*PL)->next) return FALSE;
	if (i > ListLength(*PL)) return OVERFLOW;
	LinkList p = (*PL),pp=NULL;
	int j = 0;
	//寻找第i个结点，并令p指向其前趋结点
	while (p->next && j < i) {
		pp = p;
		p = p->next;
		j++;
	}
	//检查删除位置是否合理
	//不存在这样的位置
	if (!p || j > i) return ERROR;
	//处理尾元素
	if (!p->next&&pp->next && j == i) {
		*e = p->elem;
		pp->next = NULL;
		free(p);
		return OK;
	}
	
	
	LinkList q = p->next;
	p->next = q->next;
	*e = q->elem;
	free(q);
	return OK;
}
Status ListTraverse(LinkList L, Status(*visit)(ElemType)) {
	if (!L->next)return ERROR;
	LinkList p = L->next;
	while (p) {
		if (!visit(p->elem))return ERROR;
		p = p->next;
	}
}
Status SaveList(LinkList L, char* pFN) {
	//打开文件，检查打开是否成功和线性表是否存在
	//将线性表的内容存储入文件中
	FILE* fin = fopen(pFN, "wb");
	if (!fin || !L->next) return ERROR;
	LinkList p = L->next;
	while (p->next) {
		fprintf(fin, "%d ", p->elem);
		p = p->next;
	}
	fprintf(fin, "%d ", p->elem);
	fclose(fin);
	return TRUE;
}
Status LoadList(PtrLinkList PL, char* pFN) {
	InitList(PL);
	FILE* fout = fopen(pFN, "rb");
	if (!fout) return ERROR;
	if (!(*PL) && !ListEmpty(*PL)) return ERROR;
	(*PL)->next = (LinkList)malloc(sizeof(Lnode));
	LinkList p = (*PL)->next,q=(*PL);
	while (fscanf(fout, "%d", &(p->elem)) != EOF) {
		p->next = (LinkList)malloc(sizeof(Lnode));
		p = p->next;
		q = q->next;
	}
	q->next = NULL;
	fclose(fout);
	return OK;
}