#pragma once


typedef struct USERDATA
{
	int page;
	char title[64];
	char author[32];
} USERDATA;

typedef struct NODE
{
	void* pData;
	struct NODE* pNext;
	struct NODE* pPrev;
	char* (*GetKey)(void* thisPointer);
} NODE;


extern NODE g_HeadNode;
extern NODE g_TailNode;

void ReleaseIndex(void);
NODE** UpdateIndex(void);
NODE** MakeIndexPage(unsigned int* pCnt);

void InitList(void);
void ReleaseList(void);
unsigned int GetListCount(void);
int IsEmpty(void);

void* GetKey(void* thisPointer, const char* key);
void SwapNode(NODE* pLeft, NODE* pRight);

void AddNewNode(int page, char* pszTitle, char* pszAuthor);
void RemoveNodeByKeyword(char* pszUserInput, char* key, int* pCount);
void** SearchListByKeyword(char* pszUserInput, char* key, int* pCount);
void** SearchListByPageRange(int min, int max, int* pCount);
void SortList(char* key);

int LoadListFromFile(void);
int SaveListToFile(void);
