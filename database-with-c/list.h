#pragma once

typedef struct USERDATA
{
	int age;
	char name[32];
	char phone[32];
	struct USERDATA* pPrev;
	struct USERDATA* pNext;
} USERDATA;


USERDATA g_HeadNode;
USERDATA g_TailNode;
static unsigned int g_listLen;

unsigned int GetListLength();
unsigned int RecalcListLen(void);
void ResetList(void);
void ReleaseList(void);

void ReleaseIndex(void);
void** MakeIndexAge(unsigned int* pCnt);
void** MakeIndexName(int* pCnt);
void UpdateIndexAll(void);

void AddNewNodeAtTail(int age, const char* pszName, const char* pszPhone);


void Enqueue(USERDATA* pUser);
USERDATA* Dequeue(void);

void Push(USERDATA* pUser);
USERDATA* Pop(void);

int IsEmpty(void);

void RemoveNode(USERDATA* pRemove);
void CopyNodeData(USERDATA* pDest, USERDATA* pOri);
void SwapNode(USERDATA* pLeft, USERDATA* pRight);

void SortListByAge(void);
void SortListByName(void);

int SearchListByName(USERDATA* pUser, char* pszName);

void** SearchBySortedAgeRange(int min, int max, int* pCount);
void** SearchByAgeRange(int min, int max, int* pCount);

int RemoveNodeByName(char* pszName);
