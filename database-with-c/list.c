#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


NODE g_HeadNode = { 0 };
NODE g_TailNode = { 0 };

static unsigned int g_listCount = 0;

NODE** g_idxListPage = NULL;


void ReleaseIndex(void)
{
	if (g_idxListPage != NULL)
	{
		free(g_idxListPage);
		g_idxListPage = NULL;
	}

	return;
}

NODE** UpdateIndex(void)
{
	ReleaseIndex();

	int cnt = 0;
	g_idxListPage = MakeIndexPage(&cnt);

	return g_idxListPage;
}

NODE** MakeIndexPage(unsigned int* pCnt)
{
	if (IsEmpty())
		return NULL;

	*pCnt = GetListCount();

	NODE** idxList;
	idxList = malloc(sizeof(NODE*) * (*pCnt));
	memset(idxList, 0, sizeof(NODE*) * (*pCnt));

	NODE* pTmp = g_HeadNode.pNext;

	for (unsigned int i = 0; pTmp != &g_TailNode; ++i)
	{
		idxList[i] = pTmp;
		pTmp = pTmp->pNext;
	}

	USERDATA* pSelected;
	USERDATA* pCmp;
	for (unsigned int i = 0; i < *pCnt - 1; ++i)
	{
		for (unsigned int j = i + 1; j < *pCnt; ++j)
		{
			pSelected = (USERDATA*)idxList[i]->pData;
			pCmp = (USERDATA*)idxList[j]->pData;

			if (pSelected->page > pCmp->page)
			{
				NODE* pTmp = idxList[i];
				idxList[i] = idxList[j];
				idxList[j] = pTmp;
			}
		}
	}

	return idxList;
}

void InitList(void)
{
	ReleaseList();
	g_HeadNode.pNext = &g_TailNode;
	g_TailNode.pPrev = &g_HeadNode;
	g_listCount = 0;
}

void ReleaseList(void)
{
	if (IsEmpty())
		return NULL;

	NODE* pTmp = g_HeadNode.pNext;
	NODE* pDelete;

	while (pTmp != &g_TailNode)
	{
		pDelete = pTmp;
		pTmp = pTmp->pNext;
		free(pDelete->pData);
		free(pDelete);
	}

	g_HeadNode.pNext = &g_TailNode;
	g_TailNode.pPrev = &g_HeadNode;
	g_listCount = 0;

	ReleaseIndex();
}

unsigned int GetListCount(void)
{
	return g_listCount;
}

int IsEmpty(void)
{
	return (g_HeadNode.pNext == &g_TailNode || g_HeadNode.pNext == NULL);
}

void* GetKey(void* thisPointer, const char* key)
{
	USERDATA* pData = (USERDATA*)thisPointer;

	if (strcmp(key, "page") == 0) {
		int* pPage = (int*)malloc(sizeof(int));
		if (pPage == NULL) {
			return NULL;
		}
		*pPage = pData->page;
		return pPage;
	}
	else if (strcmp(key, "title") == 0) {
		return pData->title;
	}
	else if (strcmp(key, "author") == 0) {
		return pData->author;
	}
	else
		return NULL;
}

void SwapNode(NODE* pLeft, NODE* pRight)
{
	void* pTmp = pLeft->pData;
	pLeft->pData = pRight->pData;
	pRight->pData = pTmp;
}

void AddNewNode(int page, char* pszTitle, char* pszAuthor)
{
	USERDATA* pNewData = calloc(1, sizeof(USERDATA));
	pNewData->page = page;
	strcpy_s(pNewData->title, sizeof(pNewData->title), pszTitle);
	strcpy_s(pNewData->author, sizeof(pNewData->author), pszAuthor);

	NODE* pNewNode = calloc(1, sizeof(NODE));
	pNewNode->pData = pNewData;
	pNewNode->GetKey = GetKey;

	NODE* pLastNode = g_TailNode.pPrev;
	pLastNode->pNext = pNewNode;
	pNewNode->pPrev = pLastNode;
	pNewNode->pNext = &g_TailNode;
	g_TailNode.pPrev = pNewNode;

	++g_listCount;

	UpdateIndex();
}

void RemoveNodeByKeyword(char* pszUserInput, char* key, int* pCount)
{
	NODE* pCur = g_HeadNode.pNext;
	NODE* pToRemove;
	NODE* pPrevNode;
	NODE* pNextNode;
	USERDATA* pData;

	int cnt = 0;

	while (pCur != NULL && pCur != &g_TailNode)
	{
		char* pSelected = (char*)pCur->GetKey(pCur->pData, key);
		if (strstr(pSelected, pszUserInput) != NULL)
		{
			pPrevNode = pCur->pPrev;
			pNextNode = pCur->pNext;
			pPrevNode->pNext = pCur->pNext;
			pNextNode->pPrev = pCur->pPrev;

			pToRemove = pCur;
			pCur = pCur->pNext;

			free(pToRemove->pData);
			free(pToRemove);

			--g_listCount;
			++cnt;
		}

		else
			pCur = pCur->pNext;
	}

	if (cnt)
	{
		*pCount = cnt;
		UpdateIndex();
	}

	return;
}

void** SearchListByKeyword(char* pszUserInput, char* key, int* pCount)
{
	if (IsEmpty())
		return NULL;

	*pCount = 0;
	NODE* pTmp = g_HeadNode.pNext;
	int cnt = 0;
	char* pTmpData = NULL;

	while (pTmp != &g_TailNode) {

		pTmpData = (char*)pTmp->GetKey(pTmp->pData, key);
		USERDATA* pData = (USERDATA*)pTmp->pData;
		if (strstr(pTmpData, pszUserInput) != NULL)
			++cnt;

		pTmp = pTmp->pNext;
	}

	if (cnt == 0)
		return NULL;

	void** pResultList = malloc(sizeof(void*) * cnt);
	if (pResultList == NULL)
		return NULL;

	*pCount = cnt;

	cnt = 0;
	pTmp = g_HeadNode.pNext;

	while (pTmp != &g_TailNode) {
		USERDATA* pData = (USERDATA*)pTmp->pData;
		pTmpData = (char*)pTmp->GetKey(pTmp->pData, key);
		if (strstr(pTmpData, pszUserInput) != NULL) {
			pResultList[cnt] = pTmp->pData;
			++cnt;
		}
		pTmp = pTmp->pNext;
	}

	return pResultList;
}

void** SearchListByPageRange(int min, int max, int* pCount)
{
	*pCount = 0;
	unsigned int listLen = 0;
	NODE** idxList = (NODE**)MakeIndexPage(&listLen);
	USERDATA* pData;

	int idxMin = -1, idxMax = 0;

	unsigned int i = 0;
	for (i = 0; i < listLen; ++i)
	{
		pData = idxList[i]->pData;
		if (pData->page >= min && pData->page <= max)
		{
			idxMin = i;
			idxMax = i;
			break;
		}
	}

	if (idxMin >= 0)
	{
		for (; i < listLen; ++i)
		{
			pData = idxList[i]->pData;
			if (pData->page > max)
				break;
			else if (pData->page <= max)
				idxMax = i;
		}

		int resultLen = idxMax - idxMin + 1;
		NODE** resultList = malloc(sizeof(void*) * resultLen);
		memcpy(resultList, idxList + idxMin, sizeof(void*) * resultLen);

		free(idxList);

		*pCount = resultLen;
		return resultList;
	}
	return NULL;
}

void SortList(char* key)
{
	if (IsEmpty())
		return;

	NODE* pTmp = g_HeadNode.pNext;
	NODE* pSelected = NULL;
	NODE* pCmp = NULL;
	char* dataSelected = NULL;
	char* dataToComp = NULL;

	while (pTmp != NULL && pTmp != g_TailNode.pPrev)
	{
		pSelected = pTmp;
		pCmp = pTmp->pNext;
		while (pCmp != NULL && pCmp != &g_TailNode)
		{
			char* dataSelected = (char*)pSelected->GetKey(pSelected->pData, key);
			char* dataToComp = (char*)pCmp->GetKey(pCmp->pData, key);

			if (strcmp(key, "page") == 0)
			{
				if (*(int*)dataSelected > *(int*)dataToComp)
					pSelected = pCmp;
			}
			else
			{
				if (strcmp(dataSelected, dataToComp) > 0)
					pSelected = pCmp;
			}
			pCmp = pCmp->pNext;
		}

		if (pTmp != pSelected)
			SwapNode(pTmp, pSelected);

		pSelected = NULL;
		pTmp = pTmp->pNext;
	}

	if (strcmp(key, "page") == 0) {

		if (dataSelected != NULL ||
			dataToComp != NULL)
		{
			free(dataSelected);
			free(dataToComp);
		}
	}
}

// Functions for File I/O
int LoadListFromFile(void)
{
	ReleaseList();
	FILE* fp = NULL;
	fopen_s(&fp, "data.dat", "rb");
	if (fp == NULL)
		return 0;

	USERDATA user = { 0 };
	while (fread(&user, sizeof(USERDATA), 1, fp) > 0)
	{
		AddNewNode(user.page, user.title, user.author);
		memset(&user, 0, sizeof(USERDATA));
	}

	UpdateIndex();

	fclose(fp);
	return 1;
}

int SaveListToFile(void)
{
	FILE* fp = NULL;
	fopen_s(&fp, "data.dat", "wb");
	if (fp == NULL)
		return 0;

	NODE* pTmp = g_HeadNode.pNext;
	while (pTmp != NULL && pTmp != &g_TailNode)
	{
		fwrite(pTmp->pData, sizeof(USERDATA), 1, fp);
		pTmp = pTmp->pNext;
	}

	fclose(fp);
	return 1;
}