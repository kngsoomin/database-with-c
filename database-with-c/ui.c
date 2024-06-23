#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include "list.h"
#include "ui.h"


// Console handling
QUERY GetQueryFromUser(char* pQuery)
{
	QUERY input = 0;

	system("cls");

	PrintGreetings();

	printf("Write your query to execute : ");

	if (scanf_s("%99[^\n]", pQuery, 100) == 1) {
		ClearInputBuffer();
		return ParseQuery(pQuery);
	}
	else {
		ClearInputBuffer();
		return UNRECOGNIZED;
	}
}

void ClearInputBuffer() 
{
	// To clear the input buffer after reading the query
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

QUERY ParseQuery(const char* query) 
{
	char lowered_query[100];

	strcpy_s(lowered_query, sizeof(lowered_query), query);
	ToLowerCase(lowered_query);

	if (strncmp(lowered_query, "delete", 6) == 0) 
		return DELETE;

	else if (strncmp(lowered_query, "insert", 6) == 0) 
		return INSERT;

	else if (strncmp(lowered_query, "select", 6) == 0) 
	{
		if (strstr(lowered_query, "order by") != NULL)
			return ORDER;

		else
			return SELECT;
	}
	else if (strncmp(lowered_query, "exit", 4) == 0)
		return EXIT;

	return UNRECOGNIZED;
}

void PrintGreetings(void)
{
	printf("database-with-c (version 1.0)\n\n");
	printf("Greetings! ");
	printf("Welcome to the C-based Database Program.\n");
	printf("You can query the database with SQL queries,\n");
	printf("such as SELECT, INSERT, DELETE, and ORDER BY.\n");
	printf("If you would like to see the examples or know more about project,\n");
	printf("please visit 'https://github.com/kngsoomin/database-with-c'.\n\n");
}

void EventLoopRun(void)
{
	QUERY input = 0;
	char query[100] = { 0 };

	while ((input = GetQueryFromUser(&query)) != 0)
	{
		switch (input)
		{
		case SELECT:
			Search(query);
			break;

		case DELETE:
			Delete(query);
			break;

		case INSERT:
			Insert(query);
			break;

		case ORDER:
			Order(query);
			break;

		case UNRECOGNIZED:
		default:
			break;
		}
	}

	printf("Do you want to save changes to file? (y/n)");
	char ch = _getch();
	if (ch == 'y' || ch == 'Y')
	{
		SaveListToFile();
		putchar('\n');
		puts("Saved!\n");
	}
	
	puts("Thank you for using the database program. Goodbye!");
}

// Print functions
void PrintHeader(int title, int author, int page)
{
	if (title + author + page != 0)
	{
		if (title)
			printf("%-40s\t", "Title");
		if (author)
			printf("%-15s\t", "Author");
		if (page)
			printf("%s", "Page");
		putchar('\n');
		if (title)
			printf("%-40s\t", "========================================");
		if (author)
			printf("%-15s\t", "==============");
		if (page)
			printf("%s", "====");
		putchar('\n');
	}
}

void PrintRow(USERDATA* pUser, int title, int author, int page)
{
	if (title)
		printf("%-40s\t", pUser->title);
	if (author)
		printf("%-15s\t", pUser->author);
	if (page)
		printf("%d", pUser->page);
	if (page + author + title > 0)
		putchar('\n');
}

void PrintSelectedCols(int title, int author, int page)
{
	NODE* pTmp = g_HeadNode.pNext;
	USERDATA* pUser = NULL;

	PrintHeader(title, author, page);

	while (pTmp != NULL && pTmp != &g_TailNode)
	{
		pUser = pTmp->pData;
		PrintRow(pUser, title, author, page);
		pTmp = pTmp->pNext;
	}
	
	putchar('\n');
	printf("[Alert] %d row(s) found for your query.\n", GetListCount());
}

void PrintAllData(int wait)
{
	PrintSelectedCols(1, 1, 1);

	putchar('\n');

	if (wait)
		_getch();
}

// Functions for string manipulation
void ToLowerCase(char* str) 
{
	while (*str) {
		*str = tolower(*str);
		str++;
	}
}

char* TrimSpecialChars(char* str) 
{
	char* end;

	while (*str == ' ' || *str == '\'' || *str == '%') {
		str++;
	}

	if (*str == 0) 
		return str;

	end = str + strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\'' || *end == '%')) {
		end--;
	}

	*(end + 1) = 0;

	return str;
}

// Insert, Delete, Select, Order by
void InsertNewRow(int page, char* pszTitle, char* pszAuthor)
{
	AddNewNode(page, pszTitle, pszAuthor);

	PrintAllData(0);
	putchar('\n');
	printf("[Alert] 1 row has been added.\n");
	
	_getch();
}

void DeleteRows(char* pszKeyword, char* pszKey)
{
	int cnt = 0;
	RemoveNodeByKeyword(pszKeyword, pszKey, &cnt);

	if (cnt != 0)
		printf("\n[Alert] %d row(s) have been deleted successfully.\n", cnt);
	else
		printf("\n[Alert] The query returned an empty result set.\n");

	_getch();
}

void SearchByKeyword(char* pszKeyword, char* pszKey, int title, int author, int page)
{
	int cnt = 0;

	void** pResult = SearchListByKeyword(pszKeyword, pszKey, &cnt);
	USERDATA* pTmp = NULL;


	if (cnt != 0)
	{
		PrintHeader(title, author, page);
		for (int i = 0; i < cnt; ++i)
		{
			pTmp = (USERDATA*)pResult[i];
			PrintRow(pTmp, title, author, page);
		}
		putchar('\n');
		printf("[Alert] %d row(s) found for your query.\n", cnt);

		free(pResult);
	}
	else
	{
		putchar('\n');
		printf("[Alert] The query returned an empty result set.\n");
	}

	_getch();
}

void SearcyByPageRange(int min, int max, int title, int author, int page)
{
	int cnt = 0;

	NODE** pResultList = (NODE**)SearchListByPageRange(min, max, &cnt);
	USERDATA* pTmp;

	if (cnt)
	{
		USERDATA* pTmp = NULL;

		PrintHeader(title, author, page);
		for (int i = 0; i < cnt; ++i)
		{
			pTmp = (USERDATA*)pResultList[i]->pData;
			PrintRow(pTmp, title, author, page);
		}
		putchar('\n');
		printf("[Alert] %d row(s) found for your query.\n", cnt);

		free(pResultList);
	}
	else
	{
		putchar('\n');
		printf("[Alert] The query returned an empty result set.\n");
	}

	_getch();

}

// Main functions for SQL query execution
void ParseSelectedCols(const char* query, int* pPage, int* pTitle, int* pAuthor)
{
	int page = 0, title = 0, author = 0;

	char* cols = NULL;
	char* token;
	char* context = NULL;

	const char* select_start = strstr(query, "select");
	const char* from_start = strstr(query, "from");

	if (select_start != NULL && from_start != NULL)
	{
		select_start += 6;

		int length = from_start - select_start;
		char select_items[50];

		strcpy_s(select_items, sizeof(select_items), select_start);
		select_items[length] = '\0';

		cols = TrimSpecialChars(select_items);
		if (strcmp(cols, "*") == 0)
		{
			page = 1;
			title = 1;
			author = 1;
		}

		else
		{
			token = strtok_s(cols, ",", &context);

			while (token != NULL)
			{
				while (*token == ' ')
					token++;
				if (strcmp(token, "page") == 0)
					page = 1;
				else if (strcmp(token, "title") == 0)
					title = 1;
				else if (strcmp(token, "author") == 0)
					author = 1;

				token = strtok_s(NULL, ",", &context);
			}
		}
		*pPage = page;
		*pTitle = title;
		*pAuthor = author;
	}
	else
	{
		printf("[Warning] Select query should be in the format ");
		printf("'SELECT col1, col2 FROM DATABASE' OR ");
		printf("'SELECT * FROM DATABASE WHERE col1 LIKE '%val1%'' OR ");
		printf("'SELECT * FROM DATABASE WHERE 0<col1<1000'.\n");
		return;
	}
}

void Insert(char* query)
{
	char* token;
	char* context = NULL;
	char values[100];
	char input_lower[100];

	int page;
	char title[64];
	char author[32];

	strcpy_s(input_lower, sizeof(input_lower), query);

	ToLowerCase(input_lower);

	char* start = strstr(input_lower, "values(");
	if (start == NULL) {
		printf("[Warning] Insert query should be in the format 'INSERT INTO DATABASE VALUES(a, b, c)'\n");
		return;
	}

	int offset = start - input_lower;
	strcpy_s(values, sizeof(values), query + offset + 7);

	char* end = strchr(values, ')');
	if (end != NULL)
		*end = '\0';  // Replace ')' with null terminator

	token = strtok_s(values, ",", &context);
	int token_index = 0;

	while (token != NULL) 
	{
		while (*token == ' ')
			token++;
		if (token_index == 0)
			page = atoi(token);
		else if (token_index == 1) 
			strcpy_s(title, sizeof(title), token);
		else if (token_index == 2) 
			strcpy_s(author, sizeof(author), token);

		token = strtok_s(NULL, ",", &context);
		++token_index;
	}

	InsertNewRow(page, title, author);

	return;
}

void Delete(char* query)
{
	char values[100];
	char input_lower[100];

	char* key = NULL;
	char* search_kw = NULL;

	strcpy_s(input_lower, sizeof(input_lower), query);

	ToLowerCase(input_lower);

	char* start = strstr(input_lower, "where");
	if (start == NULL) {
		printf("[Warning] Delete query should be in the format ");
		printf("'DELETE FROM DATABASE WHERE col1 LIKE '%val1%''.\n");
		return;
	}

	int offset = start - input_lower;
	strcpy_s(values, sizeof(values), input_lower + offset + 5);

	if (strstr(values, "like") != NULL)
	{
		char* like_position = strstr(values, "like");
		*like_position = '\0';
		like_position += 4;

		key = TrimSpecialChars(values);
		search_kw = TrimSpecialChars(like_position);
	}
	else
	{
		printf("[Warning] Delete query should be in the format ");
		printf("'DELETE FROM DATABASE WHERE col1 LIKE '%val1%''.\n");
		return;
	}

	DeleteRows(search_kw, key);

	return;
}

void Search(char* query)
{
	char* token;
	char* context = NULL;

	char values[100];
	char input_lower[100];

	int min, max;
	char* key = NULL;
	char* search_kw = NULL;

	int colPage = 0, colTitle = 0, colAuthor = 0;

	strcpy_s(input_lower, sizeof(input_lower), query);
	ToLowerCase(input_lower);

	ParseSelectedCols(input_lower, &colPage, &colTitle, &colAuthor);

	char* start = strstr(input_lower, "where");

	if (start == NULL) {
		PrintSelectedCols(colTitle, colAuthor, colPage);

		_getch();
		return;
	}

	int offset = start - input_lower;
	strcpy_s(values, sizeof(values), input_lower + offset + 5);

	if (strstr(values, "<") != NULL)
	{
		token = strtok_s(values, "<", &context);
		int token_index = 0;

		while (token != NULL)
		{
			while (*token == ' ')
				token++;

			if (token_index == 0)
				min = atoi(token);
			else if (token_index == 2)
				max = atoi(token);

			token = strtok_s(NULL, "<", &context);
			++token_index;
		}

		SearcyByPageRange(min, max, colTitle, colAuthor, colPage);
	}
	else if (strstr(values, "like") != NULL)
	{
		char* like_position = strstr(values, "like");
		*like_position = '\0';
		like_position += 4;

		key = TrimSpecialChars(values);
		search_kw = TrimSpecialChars(like_position);

		SearchByKeyword(search_kw, key, colTitle, colAuthor, colPage);
	}

	else
	{
		printf("[Warning] Select query should be in the format ");
		printf("'SELECT col1, col2 FROM DATABASE' OR ");
		printf("'SELECT * FROM DATABASE WHERE col1 LIKE '%val1%'' OR ");
		printf("'SELECT * FROM DATABASE WHERE 0<col1<1000'.\n");
		return;
	}

}

void Order(char* query)
{
	char input_lower[100];
	char* key = NULL;

	int colPage = 0, colTitle = 0, colAuthor = 0;

	strcpy_s(input_lower, sizeof(input_lower), query);
	ToLowerCase(input_lower);

	ParseSelectedCols(input_lower, &colPage, &colTitle, &colAuthor);

	char* order_by_position = strstr(input_lower, "order by");

	order_by_position += 8;

	key = TrimSpecialChars(order_by_position);

	SortList(key);

	PrintSelectedCols(colTitle, colAuthor, colPage);
	_getch();
}