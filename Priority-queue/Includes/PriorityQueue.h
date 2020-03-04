#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <memory>
#include <cstdlib>
#include <exception>
#include <stdexcept>
#include <utility>
#include <iterator>

template <typename T>
class PriorityQueue
{
private:
	unsigned long long elemCounter = 0;

	struct node
	{
		T nodeElement;
		struct node* next;
	};

	node* head = NULL;

public:

	PriorityQueue()
		:head(NULL){}

	void enqueue(T element)
	{
		node* ptr;
		node* temp = new node;
		temp->nodeElement = element;
		temp->next = NULL;

		//IF HEAD IS NOT SET
		if(head == NULL)
		{
			head = temp;
		}

		//IF ELEMENT IS SMALLER THAN HEADS ELEMENT
		if(element < head->nodeElement)
		{
			temp->next = head;
			head = temp;
		}

		//FOR ALL OTHER INSERTIONS
		if(head != NULL && element > head->nodeElement)
		{
			ptr = head;
			while(ptr->next != NULL && ptr->next->nodeElement <= element)
			{
				ptr = ptr->next;
			}
			temp->next = ptr->next;
			ptr->next = temp;
		}
		elemCounter++;
	}

	void dequeue()
	{
		if(head != NULL)
		{
			try
			{
				node* temp = head;
				head = head->next;
				delete(temp);
				elemCounter--;
			}
			catch(std::exception& e)
			{
				throw e;
			}
		}
		else
		{
			throw std::out_of_range("Dequeue Error");
		}
	}

	T peek()
	{
		try
		{
			if(head != NULL)
			{
				return head->nodeElement;
			}
			else
			{
				throw std::out_of_range("Error");
			}
		}
		catch(std::exception& e)
		{
			throw e;
		}
	}

	size_t size()
	{
		return elemCounter;
	}

	bool isEmpty()
	{
		if(elemCounter == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

#endif