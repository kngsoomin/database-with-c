#pragma once

typedef enum QUERY
{
	EXIT, SELECT, INSERT, DELETE, ORDER, UNRECOGNIZED
} QUERY;

QUERY GetQueryFromUser(char* pQuery);
void ClearInputBuffer();
QUERY ParseQuery(const char* query);
void PrintGreetings(void);
void EventLoopRun(void);

void PrintHeader(int title, int author, int page);
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
