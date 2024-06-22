#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "list.h"
#include "ui.h"

void TestStackAndQueue(void)
{
	//InitDummyData();
	ResetList();

	//TestStep01();
	//TestStep02();
	//TestStep03();
	USERDATA user = { 10, "TEST01", };
	Push(&user);

	user.age = 11;
	strcpy_s(user.name, sizeof(user.name), "TEST02");
	Push(&user);

	user.age = 12;
	strcpy_s(user.name, sizeof(user.name), "TEST03");
	Push(&user);

	PrintList();

	for (int i = 0; i < 3; i++)
	{
		USERDATA* pUser = Pop();
		printf("Pop: %d, %s\n", pUser->age, pUser->name);
		free(pUser);
	}

	ReleaseList();
}


void TestStep01(void)
{
	puts("TestStep01() -------------------------");
//	PrintList();

//	USERDATA* pRemove = SearchByName("Han");
//	if (&pRemove != NULL)
//		RemoveNode(pRemove);

//	ReleaseList();

//	putchar('\n');
}


void TestStep02(void)
{
	puts("TestStep02() -------------------------");
//	AddNewNodeAtTail(11, "Han", "010-1111-1111");
//	AddNewNodeAtTail(12, "Choi", "010-1111-1111");
//	AddNewNodeAtTail(13, "Kang", "010-1111-1111");
//	PrintList();

//	USERDATA* pRemove = SearchByName("Choi");
//	if (pRemove != NULL)
//		RemoveNode(pRemove);

//	ReleaseList();

//	putchar('\n');
}


void TestStep03(void)
{
	puts("TestStep03() -------------------------");
//	AddNewNodeAtTail(11, "Han", "010-1111-1111");
//	AddNewNodeAtTail(12, "Choi", "010-1111-1111");
//	AddNewNodeAtTail(13, "Kang", "010-1111-1111");
//	PrintList();

//	USERDATA* pRemove = SearchByName("Kang");
	//if (pRemove != NULL)
	//	RemoveNode(pRemove);

//	ReleaseList();

	//putchar('\n');
}


void InitDummyData(void)
{
	//AddNewNodeAtHead(1, "Kim", "010-1111-1111");
	//AddNewNodeAtHead(2, "Ahn", "010-2222-2222");	
	//AddNewNodeAtHead(3, "Koo", "010-3333-3333");

	AddNewNodeAtTail(10, "Han", "010-2222-2222");
	AddNewNodeAtTail(11, "Hwang", "010-1111-1111");
	AddNewNodeAtTail(9, "Moh", "010-3333-3333");
	AddNewNodeAtTail(7, "Park", "010-1234-3333");
	AddNewNodeAtTail(5, "Kim", "010-1234-1111");
	AddNewNodeAtTail(8, "Chang", "010-1234-7777");
	AddNewNodeAtTail(6, "Hoon", "010-1234-2222");
	AddNewNodeAtTail(8, "Jang", "010-1234-6666");
	AddNewNodeAtTail(8, "Jung", "010-1234-8888");
	AddNewNodeAtTail(7, "Choi", "010-1234-4444");
	AddNewNodeAtTail(7, "Chae", "010-1234-5555");
}