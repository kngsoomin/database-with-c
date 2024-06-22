#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "oldlist.h"

//USERDATA g_HeadNode = { 0, "__DummyHead__" };
//USERDATA g_TailNode = { 0, "__DummyTail__" };
//static unsigned int g_listLen = 0;
//
//USERDATA** g_idxListAge = NULL;
//USERDATA** g_idxListName = NULL;
//
//
//unsigned int GetListLength()
//{
//	return g_listLen;
//}
//
//unsigned int RecalcListLen(void)
//{
//	unsigned int cnt = 0;
//	USERDATA* pTmp = g_HeadNode.pNext;
//	while (pTmp != &g_TailNode)
//	{
//		++cnt;
//		pTmp = pTmp->pNext;
//	}
//	g_listLen = cnt;
//
//	return g_listLen;
//}
//
//void ResetList(void)
//{
//	g_HeadNode.pNext = &g_TailNode;
//	g_TailNode.pPrev = &g_HeadNode;
//	g_listLen = 0;
//
//	ReleaseIndex();
//}
//
//
//void** MakeIndexAge(unsigned int* pCnt)
//{
//	if (IsEmpty())
//		return NULL;
//
//	*pCnt = GetListLength();
//
//	USERDATA** idxList;
//	idxList = malloc(sizeof(USERDATA*) * *pCnt);
//	memset(idxList, 0, sizeof(USERDATA*) * *pCnt);
//
//	USERDATA* pTmp = g_HeadNode.pNext;
//
//	for (int i = 0; pTmp != &g_TailNode; ++i)
//	{
//		idxList[i] = pTmp;
//		pTmp = pTmp->pNext;
//	}
//
//	for (int i = 0; i < *pCnt - 1; ++i)
//	{
//		for (int j = i + 1; j < *pCnt; ++j)
//		{
//			if (idxList[i]->age > idxList[j]->age)
//			{
//				pTmp = idxList[i];
//				idxList[i] = idxList[j];
//				idxList[j] = pTmp;
//			}
//		}
//	}
//
//	return idxList;
//}
//
//
//void** MakeIndexName(int* pCnt)
//{
//	*pCnt = 0;
//	if (IsEmpty())
//		return NULL;
//
//	*pCnt = GetListLength();
//
//	USERDATA** idxList;
//	idxList = malloc(sizeof(USERDATA*) * *pCnt);
//	memset(idxList, 0, sizeof(USERDATA*) * *pCnt);
//
//	USERDATA* pTmp = g_HeadNode.pNext;
//	for (int i = 0; pTmp != &g_TailNode; ++i)
//	{
//		idxList[i] = pTmp;
//		pTmp = pTmp->pNext;
//	}
//
//	for (unsigned int i = 0; i < *pCnt - 1; ++i)
//	{
//		for (unsigned int j = i + 1; j < *pCnt; ++j)
//		{
//			if (strcmp(idxList[i]->name, idxList[j]->name) > 0)
//			{
//				USERDATA* pTmp = idxList[i];
//				idxList[i] = idxList[j];
//				idxList[j] = pTmp;
//			}
//		}
//	}
//
//	return idxList;
//}
//
//void ReleaseIndex(void)
//{
//	if (g_idxListAge != NULL)
//	{
//		free(g_idxListAge);
//		g_idxListAge = NULL;
//	}
//
//	if (g_idxListName != NULL)
//	{
//		free(g_idxListName);
//		g_idxListName = NULL;
//	}
//
//	return;
//}
//
//void UpdateIndex(void)
//{
//	ReleaseIndex();
//
//	int cnt = 0;
//	g_idxListAge = (USERDATA**)MakeIndexAge(&cnt);
//	g_idxListName = (USERDATA**)MakeIndexName(&cnt);
//}
//
//void ReleaseList(void)
//{
//	USERDATA* pTmp = g_HeadNode.pNext;
//	USERDATA* pDelete;
//
//	while (pTmp != NULL && pTmp != &g_TailNode)
//	{
//		pDelete = pTmp;
//		pTmp = pTmp->pNext;
//
//		free(pDelete);
//	}
//
//	ResetList();
//	ReleaseIndex();
//}
//
//int IsEmpty(void)
//{
//	if (g_HeadNode.pNext == &g_TailNode)
//		return 1;
//
//	return 0;
//}
//
//void AddNewNodeAtTail(int age, const char* pszName, const char* pszPhone) // Queue
//{
//	USERDATA* pNewNode = (USERDATA*)malloc(sizeof(USERDATA));
//
//	pNewNode->age = age;
//	strcpy_s(pNewNode->name, sizeof(pNewNode->name), pszName);
//	strcpy_s(pNewNode->phone, sizeof(pNewNode->phone), pszPhone);
//	pNewNode->pPrev = NULL;
//	pNewNode->pNext = NULL;
//
//	USERDATA* pPrevNode = g_TailNode.pPrev;
//	pNewNode->pPrev = pPrevNode;
//	pNewNode->pNext = &g_TailNode;
//
//	pPrevNode->pNext = pNewNode;
//	g_TailNode.pPrev = pNewNode;
//
//	++g_listLen;
//	UpdateIndex();
//}
//
//void Push(USERDATA* pUser)
//{
//	USERDATA* pNewNode = (USERDATA*)malloc(sizeof(USERDATA));
//
//	memcpy(pNewNode, pUser, sizeof(USERDATA));
//
//	pNewNode->pPrev = NULL;
//	pNewNode->pNext = NULL;
//
//	USERDATA* pNextNode = g_HeadNode.pNext;
//	pNewNode->pPrev = &g_HeadNode;
//	pNewNode->pNext = pNextNode;
//
//	pNextNode->pPrev = pNewNode;
//	g_HeadNode.pNext = pNewNode;
//}
//
//USERDATA* Pop(void)
//{
//	if (IsEmpty())
//		return NULL;
//
//	USERDATA* pPop = g_HeadNode.pNext;
//	g_HeadNode.pNext = pPop->pNext;
//	pPop->pNext->pPrev = pPop->pPrev;
//
//	return pPop;
//}
//
//USERDATA* Dequeue(void)
//{
//	return Pop();
//}
//
//void Enqueue(USERDATA* pUser)
//{
//	AddNewNodeAtTail(pUser->age, pUser->name, pUser->phone);
//}
//
//int SearchListByName(USERDATA* pUser, char* pszName)
//{
//	USERDATA* pTmp = g_HeadNode.pNext;
//
//	while (pTmp != &g_TailNode)
//	{
//		if (strcmp(pTmp->name, pszName) == 0)
//		{
//			memcpy(pUser, pTmp, sizeof(USERDATA));
//			return 1;
//		}
//
//		pTmp = pTmp->pNext;
//	}
//
//	return 0;
//}
//
//void** SearchBySortedAgeRange(int min, int max, int* pCount) // after sorting
//{
//	*pCount = 0;
//	USERDATA* pMin = NULL;
//	USERDATA* pMax = NULL;
//	USERDATA* pTmp = g_HeadNode.pNext;
//
//	while (pTmp != &g_TailNode)
//	{
//		if (pTmp->age >= min)
//		{
//			pMin = pTmp;
//			break;
//		}
//		pTmp = pTmp->pNext;
//	}
//
//	if (pMin != NULL)
//		pTmp = pMin->pNext;
//	else
//		pTmp = g_HeadNode.pNext;
//
//	while (pTmp != &g_TailNode)
//	{
//		if (pTmp->age > max)
//			break;
//
//		if (pTmp->age >= min && pTmp->age <= max)
//			pMax = pTmp;
//		
//		pTmp = pTmp->pNext;
//	}
//
//	if (pMin != NULL && pMax != NULL)
//	{
//		pTmp = pMin;
//		int cnt = 1;
//
//		while (pTmp != pMax)
//		{
//			++cnt;
//			pTmp = pTmp->pNext;
//		}
//
//		*pCount = cnt;
//		void** pResultList = malloc(sizeof(void*) * cnt);
//
//		pTmp = pMin;
//		for (int i = 0; i < cnt; ++i)
//		{
//			pResultList[i] = pTmp;
//			pTmp = pTmp->pNext;
//		}
//	
//		return pResultList;
//	}
//
//	return NULL;
//	
//}
//
//void** SearchByAgeRange(int min, int max, int* pCount)
//{
//	*pCount = 0;
//	unsigned int listLen = 0;
//	USERDATA** idxList = (USERDATA**)MakeIndexAge(&listLen);
//
//	int idxMin = -1, idxMax = 0;
//
//	unsigned int i = 0;
//	for (i = 0; i < listLen; ++i)
//	{
//		if (idxList[i]->age >= min && idxList[i]->age <= max)
//		{
//			idxMin = i;
//			idxMax = i;
//			break;
//		}
//	}
//
//	if (idxMin >= 0)
//	{
//		for (; i < listLen; ++i)
//		{
//			if (idxList[i]->age > max)
//				break;
//			else if (idxList[i]->age <= max)
//				idxMax = i;
//		}
//
//		int resultLen = idxMax - idxMin + 1;
//		USERDATA** resultList = malloc(sizeof(void*) * resultLen);
//		memcpy(resultList, idxList + idxMin, sizeof(void*) * resultLen);
//
//		free(idxList);
//
//		*pCount = resultLen;
//		return resultList;
//	}
//	return NULL;
//}
//
//void SortListByName(void)
//{
//	if (IsEmpty())
//		return;
//
//	USERDATA* pTmp = g_HeadNode.pNext;
//	USERDATA* pSelected = NULL;
//	USERDATA* pCmp = NULL;
//
//	while (pTmp != NULL && pTmp != g_TailNode.pPrev)
//	{
//		pSelected = pTmp;
//		pCmp = pTmp->pNext;
//
//		while (pCmp != NULL && pCmp != &g_TailNode)
//		{
//			if (strcmp(pSelected->name, pCmp->name) > 0)
//				pSelected = pCmp;
//
//			pCmp = pCmp->pNext;
//		}
//
//		if (pTmp != pSelected)
//			SwapNode(pTmp, pSelected);
//
//		pSelected = NULL;
//		pTmp = pTmp->pNext;
//	}
//
//}
//
//void SortListByAge(void)
//{
//	if (IsEmpty())
//		return;
//
//	USERDATA* pTmp = g_HeadNode.pNext;
//	USERDATA* pSelected = NULL;
//	USERDATA* pCmp = NULL;
//
//	while (pTmp != NULL && pTmp != g_TailNode.pPrev)
//	{
//		pSelected = pTmp;
//		pCmp = pTmp->pNext;
//
//		while (pCmp != &g_TailNode)
//		{
//			if (pSelected->age > pCmp->age)
//				pSelected = pCmp;
//
//			pCmp = pCmp->pNext;
//		}
//
//		if (pSelected != pTmp)
//			SwapNode(pTmp, pSelected);
//
//		pSelected = NULL;
//		pTmp = pTmp->pNext;
//	}
//}
//
//int RemoveNodeByName(char* pszName)
//{
//	USERDATA* pCur = g_HeadNode.pNext;
//	USERDATA* pPrevNode;
//	USERDATA* pNextNode;
//
//	while (pCur != NULL && pCur != &g_TailNode)
//	{
//		if (strcmp(pCur->name, pszName) == 0)
//		{
//			pPrevNode = pCur->pPrev;
//			pNextNode = pCur->pNext;
//			pPrevNode->pNext = pCur->pNext;
//			pNextNode->pPrev = pCur->pPrev;
//
//			free(pCur);
//			--g_listLen;
//			UpdateIndex();
//			return 1;
//		}
//
//		pCur = pCur->pNext;
//	}
//
//	return 0;
//}
//
//void RemoveNode(USERDATA* pRemove)
//{
//
//	USERDATA* pPrev = pRemove->pPrev;
//	USERDATA* pNext = pRemove->pNext;
//
//	pPrev->pNext = pRemove->pNext;
//	pNext->pPrev = pRemove->pPrev;
//
//	free(pRemove);
//}
//
//void CopyNodeData(USERDATA* pDest, USERDATA* pOri)
//{
//	pDest->age = pOri->age;
//	strcpy_s(pDest->name, sizeof(pDest->name), pOri->name);
//	strcpy_s(pDest->phone, sizeof(pDest->phone), pOri->phone);
//}
//
//void SwapNode(USERDATA* pLeft, USERDATA* pRight)
//{
//	USERDATA tmp = *pLeft;
//	CopyNodeData(pLeft, pRight);
//	CopyNodeData(pRight, &tmp);
//}