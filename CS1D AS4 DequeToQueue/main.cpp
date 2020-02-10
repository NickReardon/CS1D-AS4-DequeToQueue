/*****************************************************************************
 * AUTHOR 	  		: Nick Reardon
 * Assignment #4	: Deque To Queue
 * CLASS			: CS1D
 * SECTION			: MW - 2:30p
 * DUE DATE			: 02 / 10 / 20
 *****************************************************************************/
#include "main.h"

using std::cout; using std::endl;


int main()
{

	/*
	 * HEADER OUTPUT
	 */
	PrintHeader(cout, "Prompt.txt");

	/********************************************************************/

	LinkedDeque<int> deque;
	for (int i = 0; i < 25; i++)
	{
		deque.insertBack(i);
	}

	deque.removeBack();

	deque.insertAfter(100, 15);







	deque.printAll(cout);

	system("pause");
	return 0;
}