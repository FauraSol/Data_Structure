#include"LinearList.h"
int main() {
	int choice;
	SqList temp;
	int i;
	ElemType e=0,cur_e=0,pre_e=0,next_e=0;
	char filename[50];
	Show_Menu_Choice(&choice);
	while (choice != 0) {
		switch (choice) {
		case 1:
			if (InitList(temp)) {
				printf("Generated successfully.\n");
			}
			else {
				printf("Generated failed.\n");
			}
			Show_Menu_Choice(&choice);
			break;
		case 2:
			if (DestroyList(temp)) {
				printf("Destroyed successfully.\n");
			}
			else {
				printf("WRONG\n");
			}
			Show_Menu_Choice(&choice);
			break;
		case 3:
			if (ClearList(temp)) {
				printf("Cleared successfully.\n");
			}
			else {
				printf("WRONG\n");
			}
			Show_Menu_Choice(&choice);
			break;
		case 4:
			if (ListEmpty(temp) ==1) {
				printf("It's empty.\n");
			}
			else  {
				printf("Not empty\n");
			}
			Show_Menu_Choice(&choice);
			break;
		case 5:
			printf("%d\n", ListLength(temp));
			Show_Menu_Choice(&choice);
			break;
		case 6:
			printf("Please Input i:");
			scanf("%d", &i);
			if (GetElem(temp, i, e)) {
				printf("ok\n");
			}
			else {
				printf("wrong\n");
			}
			Show_Menu_Choice(&choice);
			break;
		case 7:
			scanf("%d", &e);
			if (LocateElem(temp, e)) {
				printf("ok\n");
			}
			else {
				printf("wrong\n");
			}
			Show_Menu_Choice(&choice);
			break;
		case 8:
			scanf("%d", &cur_e);
			if (PriorElem(temp, cur_e, pre_e)) {
				printf("ok\n");
			}
			else {
				printf("wrong\n");
			}
			Show_Menu_Choice(&choice);
			break;
		case 9:
			scanf("%d", &cur_e);
			if (NextElem(temp, cur_e, next_e)) {
				printf("ok\n");
			}
			else {
				printf("wrong\n");
			}
			Show_Menu_Choice(&choice);
			break;
		case 10:
			printf("Please input the position to insert.\n");
			scanf("%d", &i);
			printf("Please input the value to insert.\n");
			scanf("%d", &e);
			if (ListInsert(temp, i, e)) {
				printf("ok\n");
			}
			else {
				printf("wrong\n");
			}
			Show_Menu_Choice(&choice);
			break;
		case 11:
			printf("Please input the position to insert.\n");
			scanf("%d", &i);
			if (ListDelete(temp, i, e)) {
				printf("ok\n");
			}
			else {
				printf("wrong\n");
			}
			Show_Menu_Choice(&choice);
			break;
		case 12:
			if (ListTraverse(temp)) {
				printf("ok\n");
			}
			else {
				printf("wrong\n");
			}
			Show_Menu_Choice(&choice);
			break;
		case 13:
			printf("Please input the filename.");
			scanf("%s", filename);
			if (SaveList(temp, filename)) {
				printf("ok\n");
			}
			else {
				printf("wrong\n");
			}
			Show_Menu_Choice(&choice);
			break;
		case 14:
			printf("Please input the filename.");
			scanf("%s", filename);
			if (LoadList(temp, filename)) {
				printf("ok\n");
			}
			else {
				printf("wrong\n");
			}
			Show_Menu_Choice(&choice);
			break;
		default:
			printf("Please input a number between 0 and 14.\n");
			Show_Menu_Choice(&choice);
			break;
		}
	}
	printf("Thanks for using.\n");
	return 0;
}