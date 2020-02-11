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

	LinkedDeque<std::string> deque;
	LinkedQueue<std::string> queue;
	
	std::ifstream iFile;

	cout << endl << " --- Using Deque implementation ---" << endl << endl;


	cout << "deque currently empty - empty() method called in printAll() to show" << endl;
	PrintWithLabel("Printing deque:", deque, cout);

	//-------------------------------------------------

	cout << "Reading into deque from file using insertBack() method" << endl;

	std::string temp;
	iFile.open("Input.txt");

	while ( getline(iFile, temp) )
	{
		deque.insertBack(temp);
	}
	iFile.close();

	PrintWithLabel("Printing deque:", deque, cout);

	//-------------------------------------------------

	cout << "deque - calling size method" << endl;
	cout << "Size is currently: " << deque.size() << endl << endl;

	//-------------------------------------------------

	cout << "deque - Calling front() method" << endl;
	cout << "front value is currently: " << deque.front() << endl << endl;

	//-------------------------------------------------

	cout << "deque - Calling eraseFront() method" << endl;
	deque.eraseFront();
	cout << "front value is now currently: " << deque.front() << endl << endl;

	cout << "deque - Calling eraseFront() method" << endl;
	deque.eraseFront();
	PrintWithLabel("Printing deque:", deque, cout);

	//-------------------------------------------------
	//-------------------------------------------------

	cout << endl << " --- Using Queue wrapper of deque implementation ---" << endl << endl;


	cout << "Queue currently empty - empty() method called in printAll() to show" << endl;
	PrintWithLabel("Printing Queue:", queue, cout);

	//-------------------------------------------------

	cout << "Reading into queue from file using enqueue() method" << endl;

	temp.clear();
	iFile.open("Input.txt");

	while (getline(iFile, temp))
	{
		queue.enqueue(temp);
	}
	iFile.close();

	PrintWithLabel("Printing Queue:", queue, cout);

	//-------------------------------------------------

	cout << "queue - calling size method" << endl;
	cout << "Size is currently: " << queue.size() << endl << endl;

	//-------------------------------------------------

	cout << "queue - Calling front() method" << endl;
	cout << "front value is currently: " << queue.front() << endl << endl;

	//-------------------------------------------------

	cout << "queue - Calling dequeue() method" << endl;
	queue.dequeue();
	cout << "front value is now currently: " << queue.front() << endl << endl;

	cout << "queue - Calling dequeue() method" << endl;
	queue.dequeue();
	PrintWithLabel("Printing Queue:", queue, cout);


	system("pause");
	return 0;
}

