#include"LinkList.h"

//ʣ��ɾ��δ���Գɹ�

//���ߺ����Ķ���
Status Equal(ElemType a, ElemType b) {
	//��������ElemTypeΪint������ֱ��ʹ�����������==
	if (a == b) return TRUE;
	else return FALSE;
}
Status visit(ElemType a) {
	printf("The element visited is %d.\n", a);
	return OK;
}
void Show_Menu_Choice(int* choice) {
	//��ʾ�˵�����ȡѡ��
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


Status InitList(PtrLinkList PL) {
	//�����յĴ�ͷָ�����ʽ���Ա�������Ƿ�ɹ�����ռ�
	//*PL��Ϊͷ���
	*PL = (LinkList)malloc(sizeof(Lnode));
	if (!*PL) return ERROR;
	(*PL)->elem = 0;
	(*PL)->next = NULL;
	return OK;
}
Status DestroyList(PtrLinkList PL) {
	//���������ڣ�����������ٰ���ͷ������ڵ�ÿһ��Ԫ��
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
	//���������ڣ���������������(���ٳ���ͷ���֮�������Ԫ��)
	if (!*PL) return ERROR;
	//�Ѿ�Ϊ��
	if (!(*PL)->next) return OK;
	/*��p��q��ָ���һ��Ԫ�أ����ѭ���ͷ�ÿһ��Ԫ�صĿռ䣬���׽���elem��Ϊ0*/
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
	//��������Ƿ���ڣ���ͨ������׽��Ԫ�صķ�ʽ�ж��Ƿ�ǿ�
	if (!L) return ERROR;
	LinkList p = L->next;
	if (p) return FALSE;
	else return TRUE;
}
int ListLength(LinkList L) {
	//��������Ƿ���ڣ������������ҷ���������
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
	//��������Ƿ�����Լ�i�Ƿ񳬳�������
	//��eȡ������ĵ�i��Ԫ��
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
	//���������ڣ��õ�ǰ�����
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
	//���������ڣ��õ���̽ڵ�
	if (!L) return FALSE;
	LinkList p = L->next;
	while (p) {
		if (Equal(cur_e, p->elem)) {
			//�ų��ҵ��������һ��Ԫ�ص����
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
	//������������Լ������ĺϷ��ԣ���e���뵽����i��
	if (!(*PL)) return ERROR;
	if (i > ListLength(*PL)+1) return OVERFLOW;
	//�������ڲ����в���
	LinkList p = (*PL);
	int j = 0;
	//Ѱ�ҵ�i-1�����
	while (p && j < i - 1) {
		p = p->next;
		++j;
	}
	if (!p || j > i) return ERROR;
	//�����½ڵ�
	LinkList s = (LinkList)malloc(sizeof(Lnode));
	//��ɲ������
	if (!s) return OVERFLOW;
	s->next = p->next;
	s->elem = e;
	p->next = s;
	return OK;
}
Status ListDelete(PtrLinkList PL, int i, ElemType* e) {
	//������������Լ�����i�ĺϷ��ԣ�ɾ������i����Ԫ��
	if (!(*PL)->next) return FALSE;
	if (i > ListLength(*PL)) return OVERFLOW;
	LinkList p = (*PL),pp=NULL;
	int j = 0;
	//Ѱ�ҵ�i����㣬����pָ����ǰ�����
	while (p->next && j < i) {
		pp = p;
		p = p->next;
		j++;
	}
	//���ɾ��λ���Ƿ����
	//������������λ��
	if (!p || j > i) return ERROR;
	//����βԪ��
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
	//���ļ��������Ƿ�ɹ������Ա��Ƿ����
	//�����Ա�����ݴ洢���ļ���
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