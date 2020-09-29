#include"LinearList.h"
//基本算法函数定义

void Show_Menu_Choice(int* choice) {
	//显示菜单

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
	printf("请选择你的操作[0~14]：");
	scanf("%d", choice);
}

status InitList(SqList& L) {
	/*线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE，如果内存分配失败返回ERROR。*/

	//检查链表是否已经存在，不能对已存在链表初始化
	if (L.elem) return INFEASIBLE;
	L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem) return ERROR;
	L.listsize = LIST_INIT_SIZE;
	L.length = 0;
	return OK;
}
status DestroyList(SqList& L) {
	/*如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。*/

	//检查链表存在
	if (!L.elem)return INFEASIBLE;
	free(L.elem);
	L.elem = NULL;
	L.length = 0;
	L.listsize = 0;
	return OK;
}
status ClearList(SqList& L) {
	/*如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE*/

	//检查链表存在
	if (!L.elem) return INFEASIBLE;
	for (int i = 0; i < L.length; i++) {
		L.elem[i] = NULL;
	}
	L.length = 0;
	return OK;
}
status ListEmpty(SqList L) {
	/*如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；
	如果线性表不存在，返回INFEASIBLE*/

	//检查链表存在
	if (!L.elem) return INFEASIBLE;
	if (!L.length) return TRUE;
	else return FALSE;
}
int ListLength(SqList L) {
	/*如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。*/

	//检查链表存在
	if (!L.elem) return INFEASIBLE;
	return L.length;
}
status GetElem(SqList L, int i, ElemType& e) {
	/*如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。*/

	//检查链表存在
	if (!L.elem) return INFEASIBLE;
	//检验位置是否合法
	if (i<1 || i>L.length) {
		//对错误情况的合理输出
		printf("The value %d is unreasonable, please input a number between 1 and %d.\n", i, L.length);
		return ERROR;
	}
	e = L.elem[i - 1];
	return OK;
}
status LocateElem(SqList L, ElemType e) {
	/*如果线性表L存在，查找元素e在线性表L中的位置序号并返回OK；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。*/

	//检查链表存在
	if (!L.elem) return INFEASIBLE;
	int i = 0;
	while (i < L.length) {
		//处理找到时的情况
		if (e == L.elem[i++]) return i;
	}
	//处理找不到的情况
	if (i >= L.length) return ERROR;
}
status PriorElem(SqList L, ElemType e, ElemType& pre) {
	/*如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。*/

	//分别处理表不存在和表无元素的错误,并输出错误描述
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
	//	//处理找到时的情况
	//	if (e == L.elem[loc++]) break;
	//}
	//if (loc >= L.length) return ERROR;
	if (!(loc=LocateElem(L, e))) {
		//找不到符合条件的位置
		return ERROR;
	}
	else {
		if (loc > 1) {
			//合理位置
			pre = L.elem[loc - 2];
			return OK;
		}
		else {
			//处理需要获得第一个元素的前驱元素的情况
			printf("The element cur_e is the first element.");
			pre = 0;
			return ERROR;
		}
	}

}
status NextElem(SqList L, ElemType e, ElemType& next) {
	/*如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。*/

	//判断空表
	if (!L.elem) return INFEASIBLE;
	int loc;
	if (!(loc = LocateElem(L, e))) {
		//没有符合条件的元素
		return ERROR;
	}else {
		if (loc < L.length) {
			//合理的位置
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
/* 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。*/
{
	
	//判断空表
	if (!L.elem) return INFEASIBLE;
	//不合理的插入位置
	if (i<1 || i>L.length + 1) return ERROR;
	//判断之前分配的空间是否已满，如果满了重新分配
	if (L.length >= L.listsize) {
		ElemType* newbase;
		newbase = (ElemType*)realloc(L.elem, (LISTINCREMENT + L.listsize) * sizeof(ElemType));
		if (!newbase) return OVERFLOW;
		L.listsize += LISTINCREMENT;
		L.elem = newbase;
	}
	//插入位置后面的元素依次后移
	ElemType* q = &(L.elem[i - 1]);
	for (ElemType* p = &(L.elem[L.length - 1]); p >= q; --p) *(p + 1) = *p;
	//插入元素并修改表长
	*q = e;
	++L.length;
	return OK;
}
status ListDelete(SqList& L, int i, ElemType& e)
/* 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。*/
{
	//判断空表
	if (!L.elem) return INFEASIBLE;
	//不合理的插入位置
	if (i<1 || i>L.length + 1) return ERROR;
	//取出元素
	ElemType* p = &(L.elem[i - 1]), * q = &(L.elem[L.length - 1]);
	e = *p;
	//删除位置后面的元素依次前移
	for (++p; p <= q; ++p) {
		*(p - 1) = *p;
	}
	//修改表长
	--L.length;
	return OK;

}
status ListTraverse(SqList L)
/* 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。*/
{
	//判断空表
	if (!L.elem) return INFEASIBLE;
	int i;
	for (i = 0; i < L.length - 1; i++) {
		printf("%d ", L.elem[i]);
	}
	//为了保证规范的间隔格式，最后一个元素单独输出
	if (L.length)printf("%d", L.elem[i]);
	return OK;
}
status SaveList(SqList L, char FileName[]) {
/* 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。*/

	//判断空表
	if (!L.elem) return INFEASIBLE;
	//二进制写入方式打开，并且检测文件是否正常打开
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
/* 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。*/

	
	//判断表为空，不允许在存在的链表中写入数据
	if (L.elem) return INFEASIBLE;
	/*
	L.elem = (ElemType*)malloc(sizeof(ElemType) * LIST_INIT_SIZE);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	*/

	//初始化链表
	InitList(L);
	//二进制读取文件，并检测打开是否正常
	FILE* fout = fopen(FileName, "rb");
	if (!fout) return INFEASIBLE;
	int i = 0;
	ElemType* newbase;
	while (fscanf(fout, "%d", &(L.elem[i])) != EOF) {
		//若读取时发现长度超出已分配内存则增加内存
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
/* 在Lists中增加一个名称为ListName的空线性表。*/
{

	int i = 0;
	//一开始所有elem都有随机地址，不能简单地空指针判断
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
	需要重写超内存的部分
	if (Lists.length >= Lists.listsize) {

		Lists.elem = realloc(Lists.elem, sizeof(Lists.elem[0]));
		realloc
	}*/
	return OK;
}

status RemoveList(LISTS& Lists, char ListName[])
// Lists中删除一个名称为ListName的线性表
{
	// 请在这里补充代码，完成本关任务
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
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
{
	// 请在这里补充代码，完成本关任务
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
