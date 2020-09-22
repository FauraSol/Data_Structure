#include"LinearList.h"
//�����㷨��������
Status InitList(PtrSqList L) {
	//����һ���յ����Ա�
	L->elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L->elem) return ERROR;
	L->listsize = LIST_INIT_SIZE;
	L->length = 0;
	return OK;
}
Status DestroyList(PtrSqList L) {
	//�������Ա���ڣ�����������������Ա�
	if (!L->elem)return ERROR;
	free(L->elem);
	L->elem = NULL;
	L->length = 0;
	L->listsize = 0;
	return OK;
}
Status ClearList(PtrSqList L) {
	//�������Ա���ڣ����������L����Ϊ�ձ�
	if (!L->elem) return ERROR;
	L->length = 0;
	return OK;
}
Status ListEmpty(SqList L) {
	//�������Ա���ڣ���������ж��Ƿ�Ϊ�գ��շ���TRUE�����򷵻�FALSE
	if (!L.elem) return ERROR;
	if (!L.length) return TRUE;
	else return FALSE;
}
int ListLength(SqList L) {
	//�������Ա���ڣ�������ڷ������Ա���
	if (!L.elem) return ERROR;
	return L.length;
}
Status GetElem(SqList L, int i, ElemType* e) {
	//�������Ա��Ƿ�����Լ�i��ֵ�Ƿ���������e�������Ա�L�ĵ�i��Ԫ��
	if (!L.elem) return ERROR;
	if (i<1 || i>L.length) {
		printf("The value %d is unreasonable, please input a number between 1 and %d.\n", i, L.length);
		return OVERFLOW;
	}
	*e = L.elem[i - 1];
	return OK;
}
Status LocateElem(SqList L, ElemType e, Status(*compare)(ElemType, ElemType)) {
	//�������Ա��Ƿ����,����L�е�һ����e����compare()������Ԫ�ص�λ������������򷵻�FALSE.
	if (!L.elem) return ERROR;
	int i = 0;
	while (i < L.length) {
		if (compare(e, L.elem[i++])) return i;
	}
	if (i >= L.length) return ERROR;
}
Status PriorElem(SqList L, ElemType cur_e, ElemType* pre_e) {
	//�������Ա��Ƿ����
	//��cur_e��L������Ԫ���Ҳ��ǵ�һ��������pre_e��������ǰ�����������ʧ�ܣ�pre_e������
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
	//��Ҫ���
	//�������Ա��Ƿ����
	//��cur_e��L������Ԫ���Ҳ������һ��������next_e��������ǰ�����������ʧ�ܣ�next_e������
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
	//��Ҫ���
	//�������Ա��Ƿ���ڣ�����i�Ƿ�����1<=i<=ListLenngth(L)+1
	//��L�е�i��λ�ò����µ�Ԫ��e��L���ȼ�1
	if (!L->elem) return ERROR;
	if (i<1 || i>L->length + 1) return ERROR;
	//�ж�֮ǰ����Ŀռ��Ƿ�����������������·���
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
	//��Ҫ���
	//�������Ա��Ƿ���ڣ�����i�Ƿ�����1<=i<=ListLenngth(L)+1
	//ɾ����i��λ�õ�Ԫ�ز���e���أ�L���ȼ�1
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
	//��Ҫ���
	//�������Ա��Ƿ����,���ζ�L��ÿ��Ԫ�ص���visit()��һ��ʧ�ܣ������ʧ��
	if (!L.elem) return ERROR;
	int i;
	for (i = 0; i < L.length; i++) {
		if (!visit(&L.elem[i]))  return FALSE;
	}
	return TRUE;
}
Status SaveList(SqList L, char* pFN) {
	//��Ҫ���
	//���ļ��������Ƿ�ɹ������Ա��Ƿ����
	//�����Ա�����ݴ洢���ļ���
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
	//��Ҫ���
	//���ļ��������Ƿ�ɹ�
	//��ȡ�ļ��е����ݲ��������Ա�
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



//��չ�㷨�ĺ�������
Status Union(PtrSqList La, SqList Lb) {
	//�������Ա�La����Lb�в�����La��Ԫ�ؼ���
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
	//��֪���Ա�La��Lb�е�����Ԫ�ذ�ֵ�ǵݼ�����
	//�鲢La��Lb�õ������Ա�Lc��Lc��Ԫ��
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
	//��֪˳�����Ա�La��Lb��Ԫ�ذ�ֵ�ǵݼ�����
	//�鲢La��Lb�õ��µ�˳�����Ա�Lc��Lc��Ԫ�ذ�ֵ�ǵݼ�����
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



//���ߺ����Ķ���
Status Equal(ElemType a, ElemType b) {
	//�ж�����Ԫ���Ƿ���ͬ����������ElemTypeȡint������ֱ��ʹ��"=="�����
	if (a == b) return TRUE;
	else return FALSE;
}
Status Display(SqList L) {
	//���һ���������Ա������Ԫ��
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
	//��ʾ�˵�

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
	printf("��ѡ����Ĳ���[0~14]��");
	scanf("%d", choice);
}