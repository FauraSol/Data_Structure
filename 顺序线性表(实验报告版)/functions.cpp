#include"LinearList.h"
//�����㷨��������

void Show_Menu_Choice(int* choice) {
	//��ʾ�˵�

	printf("\tMenu for Linear Table On Sequence Structure\n");
	printf("-----------------------------------------------------------\n");
	printf("\t1.InitList\t\t10.ListInsert\n");
	printf("\t2.DestroyList\t\t11.ListDelete\n");
	printf("\t3.ClearList\t\t12.ListTrabverse\n");
	printf("\t4.ListEmpty\t\t13.SaveData\n");
	printf("\t5.ListLength\t\t14.LoadData\n");
	printf("\t6.GetElem\t\t15.AddList\n");
	printf("\t7.LocateElem\t\t16.RemoveList\n");
	printf("\t8.PriorElem\t\t17.LocateList\n");
	printf("\t9.NextElem\t\t0.exit\n");
	printf("\t0.Exit\n");
	printf("-----------------------------------------------------------\n");
	printf("��ѡ����Ĳ���[0~14]��");
	scanf("%d", choice);
}

status InitList(SqList& L) {
	/*���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE������ڴ����ʧ�ܷ���ERROR��*/

	//��������Ƿ��Ѿ����ڣ����ܶ��Ѵ��������ʼ��
	if (L.elem) return INFEASIBLE;
	L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem) return ERROR;
	L.listsize = LIST_INIT_SIZE;
	L.length = 0;
	return OK;
}
status DestroyList(SqList& L) {
	/*������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��*/

	//����������
	if (!L.elem)return INFEASIBLE;
	free(L.elem);
	L.elem = NULL;
	L.length = 0;
	L.listsize = 0;
	return OK;
}
status ClearList(SqList& L) {
	/*������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE*/

	//����������
	if (!L.elem) return INFEASIBLE;
	for (int i = 0; i < L.length; i++) {
		L.elem[i] = NULL;
	}
	L.length = 0;
	return OK;
}
status ListEmpty(SqList L) {
	/*������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��
	������Ա����ڣ�����INFEASIBLE*/

	//����������
	if (!L.elem) return INFEASIBLE;
	if (!L.length) return TRUE;
	else return FALSE;
}
int ListLength(SqList L) {
	/*������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��*/

	//����������
	if (!L.elem) return INFEASIBLE;
	return L.length;
}
status GetElem(SqList L, int i, ElemType& e) {
	/*������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��*/

	//����������
	if (!L.elem) return INFEASIBLE;
	//����λ���Ƿ�Ϸ�
	if (i<1 || i>L.length) {
		//�Դ�������ĺ������
		printf("The value %d is unreasonable, please input a number between 1 and %d.\n", i, L.length);
		return ERROR;
	}
	e = L.elem[i - 1];
	return OK;
}
status LocateElem(SqList L, ElemType e) {
	/*������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����Ų�����OK�����e�����ڣ�����ERROR�������Ա�L������ʱ������INFEASIBLE��*/

	//����������
	if (!L.elem) return INFEASIBLE;
	int i = 0;
	while (i < L.length) {
		//�����ҵ�ʱ�����
		if (e == L.elem[i++]) return i;
	}
	//�����Ҳ��������
	if (i >= L.length) return ERROR;
}
status PriorElem(SqList L, ElemType e, ElemType& pre) {
	/*������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��*/

	//�ֱ�������ںͱ���Ԫ�صĴ���,�������������
	if (!L.elem) {
		printf("The sequence list doesn't exit.");
		return INFEASIBLE;
	}
	else if(L.length==0){
		printf("There are no element so that we can't find the prior element.");
		return ERROR;
	}
	int loc;
	//while (loc < L.length) {
	//	//�����ҵ�ʱ�����
	//	if (e == L.elem[loc++]) break;
	//}
	//if (loc >= L.length) return ERROR;
	if (!(loc=LocateElem(L, e))) {
		//�Ҳ�������������λ��
		return ERROR;
	}
	else {
		if (loc > 1) {
			//����λ��
			pre = L.elem[loc - 2];
			return OK;
		}
		else {
			//������Ҫ��õ�һ��Ԫ�ص�ǰ��Ԫ�ص����
			printf("The element cur_e is the first element.");
			pre = 0;
			return ERROR;
		}
	}

}
status NextElem(SqList L, ElemType e, ElemType& next) {
	/*������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��*/

	//�жϿձ�
	if (!L.elem) return INFEASIBLE;
	int loc;
	if (!(loc = LocateElem(L, e))) {
		//û�з���������Ԫ��
		return ERROR;
	}else {
		if (loc < L.length) {
			//�����λ��
			next = L.elem[loc];
			return OK;
		}
		else {
			printf("The element cur_e is the last element.");
			return ERROR;
		}
	}
}
status ListInsert(SqList& L, int i, ElemType e)
/* ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��*/
{
	
	//�жϿձ�
	if (!L.elem) return INFEASIBLE;
	//������Ĳ���λ��
	if (i<1 || i>L.length + 1) return ERROR;
	//�ж�֮ǰ����Ŀռ��Ƿ�����������������·���
	if (L.length >= L.listsize) {
		ElemType* newbase;
		newbase = (ElemType*)realloc(L.elem, (LISTINCREMENT + L.listsize) * sizeof(ElemType));
		if (!newbase) return OVERFLOW;
		L.listsize += LISTINCREMENT;
		L.elem = newbase;
	}
	//����λ�ú����Ԫ�����κ���
	ElemType* q = &(L.elem[i - 1]);
	for (ElemType* p = &(L.elem[L.length - 1]); p >= q; --p) *(p + 1) = *p;
	//����Ԫ�ز��޸ı�
	*q = e;
	++L.length;
	return OK;
}
status ListDelete(SqList& L, int i, ElemType& e)
/* ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��*/
{
	//�жϿձ�
	if (!L.elem) return INFEASIBLE;
	//������Ĳ���λ��
	if (i<1 || i>L.length + 1) return ERROR;
	//ȡ��Ԫ��
	ElemType* p = &(L.elem[i - 1]), * q = &(L.elem[L.length - 1]);
	e = *p;
	//ɾ��λ�ú����Ԫ������ǰ��
	for (++p; p <= q; ++p) {
		*(p - 1) = *p;
	}
	//�޸ı�
	--L.length;
	return OK;

}
status ListTraverse(SqList L)
/* ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��*/
{
	//�жϿձ�
	if (!L.elem) return INFEASIBLE;
	int i;
	for (i = 0; i < L.length - 1; i++) {
		printf("%d ", L.elem[i]);
	}
	//Ϊ�˱�֤�淶�ļ����ʽ�����һ��Ԫ�ص������
	if (L.length)printf("%d", L.elem[i]);
	return OK;
}
status SaveList(SqList L, char FileName[]) {
/* ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��*/

	//�жϿձ�
	if (!L.elem) return INFEASIBLE;
	//������д�뷽ʽ�򿪣����Ҽ���ļ��Ƿ�������
	FILE* fin = fopen(FileName, "wb");
	if (!fin ) return INFEASIBLE;
	int i;
	for (i = 0; i < L.length; i++) {
		fprintf(fin, "%d ", L.elem[i]);
	}
	fclose(fin);
	return TRUE;
}
status LoadList(SqList& L, char FileName[]) {
/* ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��*/

	
	//�жϱ�Ϊ�գ��������ڴ��ڵ�������д������
	if (L.elem) return INFEASIBLE;
	/*
	L.elem = (ElemType*)malloc(sizeof(ElemType) * LIST_INIT_SIZE);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	*/

	//��ʼ������
	InitList(L);
	//�����ƶ�ȡ�ļ����������Ƿ�����
	FILE* fout = fopen(FileName, "rb");
	if (!fout) return INFEASIBLE;
	int i = 0;
	ElemType* newbase;
	while (fscanf(fout, "%d", &(L.elem[i])) != EOF) {
		//����ȡʱ���ֳ��ȳ����ѷ����ڴ��������ڴ�
		if (L.length >= L.listsize) {
			newbase = (ElemType*)realloc(L.elem, (LIST_INIT_SIZE + LISTINCREMENT) * sizeof(ElemType));
			if (!newbase) return OVERFLOW;
			L.elem = newbase;
			L.listsize += LISTINCREMENT;
		}
		i++;
		L.length++;
	}
	fclose(fout);
	return OK;
}
status AddList(LISTS& Lists, char ListName[])
/* ��Lists������һ������ΪListName�Ŀ����Ա�*/
{

	int i = 0;
	//һ��ʼ����elem���������ַ�����ܼ򵥵ؿ�ָ���ж�
	//
	//if (Lists.length == 0) {
		Lists.listsize = 10;
		//for (i = 0; i < Lists.listsize; i++)
		//	Lists.elem[i].L.elem = NULL;
	//}
	InitList(Lists.elem[Lists.length].L);
	for (i = 0; ListName[i] && i < 30; i++) {
		Lists.elem[Lists.length].name[i] = ListName[i];
	}
	Lists.elem[Lists.length].name[i] = '\0';
	Lists.length++;
	/*
	��Ҫ��д���ڴ�Ĳ���
	if (Lists.length >= Lists.listsize) {

		Lists.elem = realloc(Lists.elem, sizeof(Lists.elem[0]));
		realloc
	}*/
	return OK;
}

status RemoveList(LISTS& Lists, char ListName[])
// Lists��ɾ��һ������ΪListName�����Ա�
{
	// �������ﲹ����룬��ɱ�������
	/********** Begin *********/
	int i = 0, j = 0;
	int flag = 0;
	if (Lists.length == 0) return INFEASIBLE;
	for (i = 0; i < Lists.length; i++) {
		if (!strcmp(ListName, Lists.elem[i].name))
		{
			flag = 1;
			DestroyList(Lists.elem[i].L);
			for (j = i; j < Lists.length - 1; j++) {
				Lists.elem[j] = Lists.elem[j + 1];
			}
			Lists.length--;
		}
	}
	if (flag)return OK;
	else return ERROR;

	/********** End **********/
}

int LocateList(LISTS Lists, char ListName[])
// ��Lists�в���һ������ΪListName�����Ա��ɹ������߼���ţ����򷵻�0
{
	// �������ﲹ����룬��ɱ�������
	/********** Begin *********/
	int i = 0;
	if (Lists.length == 0) return INFEASIBLE;
	for (i = 0; i < Lists.length; i++) {
		if (!strcmp(ListName, Lists.elem[i].name)) {
			return i + 1;
		}
	}
	return ERROR;

	/********** End **********/
}
