#pragma once

typedef enum MY_MENU
{
	EXIT, NEW, SEARCH, SORTLIST, PRINT, REMOVE
} MY_MENU;

MY_MENU PrintMenu(void);
void PrintGreetings(void);

void PrintRow(USERDATA* pUser, int title, int author, int page);
void PrintSelectedCols(int title, int author, int page);
void PrintAllData(int wait);

void ToLowerCase(char* str);
char* TrimSpecialChars(char* str);

void ParseSelectedCols(const char* query, int* pPage, int* pTitle, int* pAuthor);
void InsertNewRow(int page, char* pszTitle, char* pszAuthor);
void DeleteRows(char* pszKeyword, char* pszKey);
void SearchByKeyword(char* pszKeyword, char* pszKey, int title, int author, int page);
void SearcyByPageRange(int min, int max, int title, int author, int page);

void Insert(char* query);
void Delete(char* query);
void Search(char* query);
void Order(char* query);

void EventLoopRun(void);




//typedef enum MY_MENU { EXIT, NEW, SEARCH, PRINT, REMOVE } MY_MENU;
//
//MY_MENU PrintMenu(void);
//void PrintList(void);
//void PrintListReverse(void);
//void EventLoopRun(void);
//
//void SearchByName(void);
//void SearchByAge(void);
//
//void RemoveByName(void);