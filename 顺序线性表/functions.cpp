#include"LinearList.h"
//基本算法函数定义
Status InitList(PtrSqList L) {
	//创建一个空的线性表
	L->elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L->elem) return ERROR;
	L->listsize = LIST_INIT_SIZE;
	L->length = 0;
	return OK;
}
Status DestroyList(PtrSqList L) {
	//检验线性表存在，如果存在则销毁线性表
	if (!L->elem)return ERROR;
	free(L->elem);
	L->elem = NULL;
	L->length = 0;
	L->listsize = 0;
	return OK;
}
Status ClearList(PtrSqList L) {
	//检验线性表存在，如果存在则将L重置为空表
	if (!L->elem) return ERROR;
	L->length = 0;
	return OK;
}
Status ListEmpty(SqList L) {
	//检验线性表存在，如果存在判断是否为空，空返回TRUE，否则返回FALSE
	if (!L.elem) return ERROR;
	if (!L.length) return TRUE;
	else return FALSE;
}
int ListLength(SqList L) {
	//检验线性表存在，如果存在返回线性表长度
	if (!L.elem) return ERROR;
	return L.length;
}
Status GetElem(SqList L, int i, ElemType* e) {
	//检验线性表是否存在以及i的值是否合理，随后用e返回线性表L的第i个元素
	if (!L.elem) return ERROR;
	if (i<1 || i>L.length) {
		printf("The value %d is unreasonable, please input a number between 1 and %d.\n", i, L.length);
		return OVERFLOW;
	}
	*e = L.elem[i - 1];
	return OK;
}
Status LocateElem(SqList L, ElemType e, Status(*compare)(ElemType, ElemType)) {
	//检验线性表是否存在,返回L中第一个与e满足compare()的数据元素的位序，如果不存在则返回FALSE.
	if (!L.elem) return ERROR;
	int i = 0;
	while (i < L.length) {
		if (compare(e, L.elem[i++])) return i;
	}
	if (i >= L.length) return ERROR;
}
Status PriorElem(SqList L, ElemType cur_e, ElemType* pre_e) {
	//检验线性表是否存在
	//若cur_e是L的数据元素且不是第一个，则用pre_e返回它的前驱，否则操作失败，pre_e无意义
	if (!L.elem) return ERROR;
	int loc;
	if (loc = LocateElem(L, cur_e, Equal)) {
		if (loc > 1) {
			*pre_e = L.elem[loc - 2];
			return OK;
		}
		else {
			printf("The element cur_e is the first element.");
			pre_e = NULL;
			return ERROR;
		}
	}
	else {
		printf("There is no such an element in L");
		pre_e = NULL;
		return ERROR;
	}
}
Status NextElem(SqList L, ElemType cur_e, ElemType* next_e) {
	//需要检查
	//检验线性表是否存在
	//若cur_e是L的数据元素且不是最后一个，则用next_e返回它的前驱，否则操作失败，next_e无意义
	if (!L.elem) return ERROR;
	int loc;
	if (loc = LocateElem(L, cur_e, Equal)) {
		if (loc < L.length) {
			*next_e = L.elem[loc];
			return OK;
		}
		else {
			printf("The element cur_e is the last element.");
			return ERROR;
		}
	}
	else {
		printf("There is no such an element in L");
		return ERROR;
	}
}
Status ListInsert(PtrSqList L, int i, ElemType e) {
	//需要检查
	//检验线性表是否存在，检验i是否满足1<=i<=ListLenngth(L)+1
	//在L中第i个位置插入新的元素e，L长度加1
	if (!L->elem) return ERROR;
	if (i<1 || i>L->length + 1) return ERROR;
	//判断之前分配的空间是否已满，如果满了重新分配
	if (L->length >= L->listsize) {
		ElemType* newbase;
		newbase = (ElemType*)realloc(L->elem, (LISTINCREMENT + L->listsize) * sizeof(ElemType));
		if (!newbase) return OVERFLOW;
		L->listsize += LISTINCREMENT;
		L->elem = newbase;
	}
	ElemType* q = &(L->elem[i - 1]);
	for (ElemType* p = &(L->elem[L->length - 1]); p >= q; --p) *(p + 1) = *p;
	*q = e;
	++L->length;
	return OK;
}
Status ListDelete(PtrSqList L, int i, ElemType* e) {
	//需要检查
	//检验线性表是否存在，检验i是否满足1<=i<=ListLenngth(L)+1
	//删除第i个位置的元素并用e返回，L长度减1
	if (!L->elem) return ERROR;
	if (i<1 || i>L->length + 1) return ERROR;
	ElemType* p = &(L->elem[i - 1]), * q = &(L->elem[L->length - 1]);
	*e = *p;

	for (++p; p <= q; ++p) {
		*(p - 1) = *p;
	}
	--L->length;
	return OK;
}
Status ListTraverse(SqList L, Status(*visit)(ElemType*)) {
	//需要检查
	//检验线性表是否存在,依次对L的每个元素调用visit()，一旦失败，则操作失败
	if (!L.elem) return ERROR;
	int i;
	for (i = 0; i < L.length; i++) {
		if (!visit(&L.elem[i]))  return FALSE;
	}
	return TRUE;
}
Status SaveList(SqList L, char* pFN) {
	//需要检查
	//打开文件，检查打开是否成功和线性表是否存在
	//将线性表的内容存储入文件中
	FILE* fin = fopen(pFN, "wb");
	if (!fin || !L.elem) return ERROR;
	int i;
	for (i = 0; i < L.length; i++) {
		fprintf(fin, "%d ", L.elem[i]);
	}
	fclose(fin);
	return TRUE;
}
Status LoadList(PtrSqList L, char* pFN) {
	//需要检查
	//打开文件，检查打开是否成功
	//读取文件中的内容并创建线性表
	FILE* fout = fopen(pFN, "rb");
	if (!fout) return ERROR;
	int i = 0;
	ElemType* newbase;
	while (fscanf(fout, "%d", &(L->elem[i])) != EOF) {
		if (L->length >= L->listsize) {
			newbase = (ElemType*)realloc(L->elem, (LIST_INIT_SIZE + LISTINCREMENT) * sizeof(ElemType));
			if (!newbase) return OVERFLOW;
			L->elem = newbase;
			L->listsize += LISTINCREMENT;
		}
		i++;
		L->length++;
	}
	fclose(fout);
	return OK;
}



//拓展算法的函数定义
Status Union(PtrSqList La, SqList Lb) {
	//扩大线性表La并将Lb中不属于La的元素加入
	if (!La->elem || !Lb.elem) return ERROR;
	int NewLen = La->length + Lb.length;
	if (NewLen > La->listsize) {
		La->elem = (ElemType*)realloc(La->elem, 2 * La->listsize * sizeof(ElemType));
		La->listsize *= 2;
	}
	if (La->elem) return ERROR;
	int i = 0;
	ElemType e;
	for (i = 0; i < Lb.length; i++) {
		GetElem(Lb, i, &e);
		if (!LocateElem(*La, e, Equal)) ListInsert(La, ++La->length, e);
	}
	return OK;
}
Status MergeList_1(SqList La, SqList Lb, PtrSqList pLc) {
	//已知线性表La和Lb中的数据元素按值非递减排列
	//归并La和Lb得到新线性表Lc，Lc的元素
	int i, j, k;
	i = j = 1; k = 0;
	ElemType* ai=NULL, * bj=NULL, * ck=NULL;
	while ((i <= La.length) && (i <= Lb.length)) {
		GetElem(La, i, ai);
		GetElem(Lb, j, bj);
		if (*ai <= *bj) {
			ListInsert(pLc, ++k, *ai);
			++i;
		}
		else {
			ListInsert(pLc, ++k, *bj);
			++j;
		}
	}
	while (i <= La.length) {
		GetElem(La, i, ai);
		ListInsert(pLc, ++k, *ai);
		++i;
	}
	while (i <= Lb.length) {
		GetElem(Lb, j, bj);
		ListInsert(pLc, ++k, *bj);
		++j;
	}
	return OK;
}
Status MergeList_2(SqList La, SqList Lb, PtrSqList pLc) {
	//已知顺序线性表La和Lb的元素按值非递减排列
	//归并La和Lb得到新的顺序线性表Lc，Lc的元素按值非递减排列
	ElemType* pa = La.elem, * pa_last = pa + La.length - 1;
	ElemType* pb = Lb.elem, * pb_last = pb + Lb.length - 1;
	pLc->listsize = pLc->length = La.length + Lb.length;
	pLc->elem = (ElemType*)malloc(pLc->listsize * sizeof(ElemType));
	ElemType* pc = pLc->elem;
	if (!pLc->elem)return ERROR;
	while (pa <= pa_last && pb <= pb_last) {
		if (*pa <= *pb) *pc++ = *pa++;
		else *pc++ = *pb++;
	}
	while (pa <= pa_last)*pc++ = *pa++;
	while (pb <= pb_last)*pc++ = *pb++;
	return OK;
}



//工具函数的定义
Status Equal(ElemType a, ElemType b) {
	//判断两个元素是否相同，这里由于ElemType取int，所以直接使用"=="运算符
	if (a == b) return TRUE;
	else return FALSE;
}
Status Display(SqList L) {
	//输出一个连续线性表的所有元素
	int i, cnt = 0;
	for (int i = 0; i < L.length; i++, cnt++) {
		printf("#%d:\t%d", i + 1, L.elem[i]);
		if (cnt % 2) printf("\n");
	}
	return OK;
}
Status visit(ElemType* a) {
	printf("The element's value is %d at %#x.\n", *a, a);
	return TRUE;
}
void Show_Menu_Choice(int* choice) {
	//显示菜单

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