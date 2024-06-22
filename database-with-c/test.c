#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "list.h"
#include "ui.h"

void InitDummyData(void)
{
	AddNewNode(280, "Frankenstein", "Mary Shelly");
	AddNewNode(309, "Harry Potter and the Sorcerers Stone", "J.K.Rowling");
	AddNewNode(1216, "The Lord of the Rings", "J.R.R.Tolkien");
	AddNewNode(896, "Dune", "Frank Herbert");
	AddNewNode(369, "The Martian", "Andy Weir");
	AddNewNode(311, "Brave New World", "Aldous Huxley");
}