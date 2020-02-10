/*****************************************************************************
 * AUTHOR 	  		: Nick Reardon
 * Assignment #4	: Deque To Queue
 * CLASS			: CS1D
 * SECTION			: MW - 2:30p
 * DUE DATE			: 02 / 10 / 20
 *****************************************************************************/
#ifndef _LINKEDDEQUE_H_
#define _LINKEDDEQUE_H_
#include <exception>
#include <sstream>



class Except : virtual public std::runtime_error {

protected:

	int error_number;               ///< Error number
	int error_offset;               ///< Error offset

public:

	/** Constructor (C++ STL string, int, int).
	 *  @param msg The error message
	 *  @param err_num Error number
	 *  @param err_off Error offset
	 */
	explicit
		Except(const std::string& msg, int err_num, int err_off) :
		std::runtime_error(msg)
	{
		error_number = err_num;
		error_offset = err_off;

	}

	/** Destructor.
	 *  Virtual to allow for subclassing.
	 */
	virtual ~Except() throw () {}

	/** Returns error number.
	 *  @return #error_number
	 */
	virtual int getErrorNumber() const throw() {
		return error_number;
	}

	/**Returns error offset.
	 * @return #error_offset
	 */
	virtual int getErrorOffset() const throw() {
		return error_offset;
	}

};

enum ERROR_TYPE
{
	DEFUALT,
	FULL,
	EMPTY,
	OUT_OF_RANGE
};

template <class Type>
struct Node
{
	Type value;

	Node<Type>* prev;
	Node<Type>* next;

	Node<Type>(const Type& newValue, Node<Type>* prevNode, Node<Type>* nextNode)
	{
		value = newValue;

		prev = prevNode;
		next = nextNode;
	}

};

template <class Type>
class LinkedDeque
{
private:
	Node<Type>* head;
	Node<Type>* tail;

	int capacity;
	int currentSize;


protected:
	void destroy();

public:

	LinkedDeque<Type>(const int newCapacity = 32);

	LinkedDeque<Type>(LinkedDeque<Type>& otherDeque);

	~LinkedDeque();

	bool isEmpty();
	bool isFull();
	int size();

	void insertBefore(const Type& newItem, const int index);
	void insertAfter(const Type& newItem, const int index);

	void insertFront(const Type& newItem);
	void insertBack(const Type& newItem);

	void removeFront();
	void removeBack();


	Type front();
	Type back();

	void printAll(std::ostream& output);

};


template<class Type>
inline LinkedDeque<Type>::LinkedDeque(const int newCapacity)
{
	head = nullptr;
	tail = nullptr;

	capacity = newCapacity;
	currentSize = 0;
}

template<class Type>
inline LinkedDeque<Type>::LinkedDeque(LinkedDeque<Type>& otherDeque)
{
	capacity = otherDeque.capacity;
	currentSize = 0;

	for (Node<Type>* temp = otherDeque.head; temp != nullptr; temp = temp->next)
	{
		enqueue(temp->value);
	}
}

template<class Type>
inline LinkedDeque<Type>::~LinkedDeque()
{
	destroy();
}

template<class Type>
inline bool LinkedDeque<Type>::isEmpty()
{
	bool value = (currentSize == 0 && head == nullptr && tail == nullptr);

	return value;
}

template<class Type>
inline bool LinkedDeque<Type>::isFull()
{
	bool value = (currentSize == capacity);

	return value;
}

template<class Type>
inline void LinkedDeque<Type>::destroy()
{
	for (Node<Type>* temp = head; temp != nullptr; )
	{
		Node<Type>* hold = temp;
		temp = temp->next;
		delete hold;
	}

	head = nullptr;
	tail = nullptr;

}

template<class Type>
inline void LinkedDeque<Type>::insertBefore(const Type& newItem, const int index)
{
	if (isEmpty())
	{
		throw Except("container is empty", EMPTY, 5);
	}
	else if (isFull())
	{
		throw Except("container is full", FULL, 5);
	}
	else
	{
		if (index <= (size() - 1 / 2))
		{
			Node<Type>* ptr = head;
			for (int i = 0; i < index; i++)
			{
				ptr = ptr->next;
			}
			Node<Type>* temp = new Node<Type>(newItem, nullptr, nullptr);

			temp->prev = ptr->prev;
			temp->next = ptr;

			ptr->prev = temp;
			temp->prev->next = temp;

			temp = nullptr;
			ptr = nullptr;

			currentSize++;
		}
		else
		{
			Node<Type>* ptr = head;
			for (int i = size() - 1; i >= size() - 1 - index; i--)
			{
				ptr = ptr->next;
			}
			Node<Type>* temp = new Node<Type>(newItem, nullptr, nullptr);

			temp->prev = ptr->prev;
			temp->next = ptr;

			ptr->prev = temp;
			temp->prev->next = temp;

			temp = nullptr;
			ptr = nullptr;

			currentSize++;
		}
	}

}

template<class Type>
inline void LinkedDeque<Type>::insertAfter(const Type& newItem, const int index)
{
	if (isEmpty())
	{
		throw Except("container is empty", EMPTY, 5);
	}
	else if (isFull())
	{
		throw Except("container is full", FULL, 5);
	}
	else
	{
		if (index <= (size() - 1 / 2))
		{
			Node<Type>* ptr = head;
			for (int i = 1; i <= index; i++)
			{
				ptr = ptr->next;
			}
			Node<Type>* temp = new Node<Type>(newItem, nullptr, nullptr);

			temp->next = ptr->next;
			ptr->next = temp;

			temp->prev = ptr;
			temp->next->prev = temp;

			temp = nullptr;
			ptr = nullptr;

			currentSize++;
		}
		else
		{
			Node<Type>* ptr = head;
			for (int i = size() - 1; i >= size() - 1 - index; i--)
			{
				ptr = ptr->next;
			}
			Node<Type>* temp = new Node<Type>(newItem, nullptr, nullptr);

			temp->next = ptr->next;
			ptr->next = temp;

			temp->prev = ptr;
			temp->next->prev = temp;

			temp = nullptr;
			ptr = nullptr;

			currentSize++;
		}
	}

}

template<class Type>
inline void LinkedDeque<Type>::insertFront(const Type& newItem)
{

	if (!isFull())
	{
		if (head == 0)
		{
			head = new Node<Type>(newItem, nullptr, nullptr);
			tail = head;
		}
		else
		{
			Node<Type>* temp = new Node<Type>(newItem, nullptr, nullptr);

			head->prev = temp;

			temp->next = head;
			temp->prev = nullptr;

			head = temp;

			temp = nullptr;
		}
		currentSize++;

	}
	else
	{
		throw Except("container is full", FULL, 5);
	}
}

template<class Type>
inline void LinkedDeque<Type>::insertBack(const Type& newItem)
{

	if (!isFull())
	{
		if (head == 0)
		{
			head = new Node<Type>(newItem, nullptr, nullptr);
			tail = head;
		}
		else
		{
			Node<Type>* temp = new Node<Type>(newItem, nullptr, nullptr);

			tail->next = temp;

			temp->prev = tail;
			temp->next = nullptr;

			tail = temp;

			temp = nullptr;
		}
		currentSize++;

	}
	else
	{
		throw Except("container is full", FULL, 5);
	}

}

template<class Type>
inline void LinkedDeque<Type>::removeFront()
{

	if (!isEmpty())
	{
		if (head == tail)
		{
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else
		{
			Node<Type>* temp = head;
			head = head->next;
			head->prev = nullptr;
			delete temp;
		}
		currentSize--;

	}
	else
	{
		throw Except("container is empty", EMPTY, 5);
	}

}

template<class Type>
inline void LinkedDeque<Type>::removeBack()
{
	if (!isEmpty())
	{
		if (head == tail)
		{
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		else
		{
			Node<Type>* temp = tail;
			tail = tail->prev;
			tail->next = nullptr;
			delete temp;
		}
		currentSize--;

	}
	else
	{
		throw Except("container is empty", EMPTY, 5);
	}

}

template<class Type>
inline int LinkedDeque<Type>::size()
{
	return currentSize;
}


template<class Type>
inline Type LinkedDeque<Type>::front()
{
	return head->value;
}

template<class Type>
inline Type LinkedDeque<Type>::back()
{
	return tail->value;
}

template<class Type>
inline void LinkedDeque<Type>::printAll(std::ostream& output)
{
	for (Node<Type>* temp = head; temp != nullptr; temp = temp->next)
	{
		output << temp->value << '\n';
	}
}



template<class Type>
class LinkedQueue : protected LinkedDeque<Type>
{
private:
	LinkedDeque<Type> deque;

protected:
	void destroy();

public:

	LinkedQueue<Type>(const int newCapacity = 32);

	LinkedQueue<Type>(LinkedQueue<Type>& otherDeque);

	~LinkedQueue();

	bool isEmpty();
	bool isFull();
	int size();

	void enqueue(const Type& newItem);
	void dequeue();

	Type front();
	Type back();

	void printAll(std::ostream& output);

};



#endif // !_LINKEDDEQUE_H_

template<class Type>
inline LinkedQueue<Type>::LinkedQueue(const int newCapacity) :
	LinkedDeque<Type>(newCapacity)
{

}

template<class Type>
inline LinkedQueue<Type>::LinkedQueue(LinkedQueue<Type>& otherDeque) :
	LinkedDeque<Type>(otherDeque)
{
}

template<class Type>
inline void LinkedQueue<Type>::destroy()
{
	deque.destroy();
}

template<class Type>
inline LinkedQueue<Type>::~LinkedQueue()
{
	deque.destroy();
}

template<class Type>
inline bool LinkedQueue<Type>::isEmpty()
{
	return deque.isEmpty();
}

template<class Type>
inline bool LinkedQueue<Type>::isFull()
{
	return deque.isFull();
}

template<class Type>
inline int LinkedQueue<Type>::size()
{
	return deque.size();
}

template<class Type>
inline void LinkedQueue<Type>::enqueue(const Type& newItem)
{
	deque.insertBack(newItem);
}

template<class Type>
inline void LinkedQueue<Type>::dequeue()
{
	deque.removeFront();
}

template<class Type>
inline Type LinkedQueue<Type>::front()
{
	return deque.front();
}

template<class Type>
inline Type LinkedQueue<Type>::back()
{
	return deque.back();
}

template<class Type>
inline void LinkedQueue<Type>::printAll(std::ostream& output)
{
	deque.printAll(output);
}
