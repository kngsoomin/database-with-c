#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "list.h"
#include "ui.h"



MY_MENU PrintMenu(void)
{
	MY_MENU input = 0;

	system("cls");
	printf("[1]New\t[2]Search\t[3]Print\t[4]Remove\t[0]Exit\n");
	scanf_s("%d%*c", &input);
	return input;
}


void PrintList(void)
{
	USERDATA* pTmp = &g_HeadNode;

	while (pTmp != NULL) {
		printf("[%p] %d, %s, %s [%p]\n",
			pTmp, pTmp->age, pTmp->name, pTmp->phone, pTmp->pNext);
		pTmp = pTmp->pNext;
	}

	puts("End of list");
	_getch();
}


void PrintListReverse(void)
{
	USERDATA* pTmp = &g_TailNode.pPrev;

	while (pTmp != NULL) {
		printf("[%p] %d, %s, %s [%p]\n",
			pTmp, pTmp->age, pTmp->name, pTmp->phone, pTmp->pNext);
		pTmp = pTmp->pPrev;
	}
}


void EventLoopRun(void)
{
	MY_MENU menu = 0;

	while ((menu = PrintMenu()) != 0)
	{
		switch (menu)
		{
		case NEW:
			break;

		case SEARCH:
			RecalcListLen();
			SearchByAge();
			break;

		case PRINT:
			PrintList();
			break;

		case REMOVE:
			RemoveByName();
			break;

		default:
			break;
		}
	}

	printf("Bye~\n");
}


void SearchByName(void)
{
	char name[32] = { 0 };

	printf("name: ");
	gets_s(name, sizeof(name));

	USERDATA user = { 0 };
	if (SearchListByName(&user, name) > 0)
		printf("Found: %d, %s, %s\n",
			user.age, user.name, user.phone);
	else
		puts("Not found");

	_getch();
}


void SearchByAge(void)
{
	int min = 0, max = 0, cnt = 0;
	printf("Min Max Age: ");
	scanf_s("%d%d%*c", &min, &max);

	void** pResultList = (USERDATA**)SearchByAgeRange(min, max, &cnt);

	if (cnt)
	{
		USERDATA* pTmp = NULL;
		for (int i = 0; i < cnt; ++i) 
		{
			pTmp = (USERDATA*)pResultList[i];
			printf("[%p] %d, %s, %s [%p]\n",
				pTmp, pTmp->age, pTmp->name, pTmp->phone, pTmp->pNext);
		}
	}
	else
		printf("Query returns empty list.\n");

	free(pResultList);
	_getch();

}



void RemoveByName(void)
{
	char name[32] = { 0 };

	printf("name: ");
	gets_s(name, sizeof(name));
	if (RemoveNodeByName(name))
		puts("Removed");
	else
		puts("Not found");

	_getch();

}