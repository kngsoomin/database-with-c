#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "list.h"
#include "ui.h"
#include "test.h"



int main(void)
{
	InitList();

	LoadListFromFile();

	EventLoopRun();

	ReleaseList();

	return 0;
}