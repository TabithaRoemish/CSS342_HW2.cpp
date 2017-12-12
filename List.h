// File Name: List.h
// Programmer: Tabitha Roemish
// Date: Oct. 15, 2017
// File contains: List class declaration and definition
//				  node Class declaration and definition
#ifndef LIST_H
#define LIST_H
#include "Food.h"
using namespace std;

class List
{
	class node
	{
	public:
		// note: nullptr was changed to NULL for g++
		node(Food &fd) : food(fd), next(NULL), prev(NULL) {};
		node * next;
		node * prev;
		Food food;
	};

public:
	List() : head(NULL), tail(NULL), size(0) {};
	~List() { clearList(); };
	void addFood(Food &fd);
	bool clearList();
	bool deleteFood(string name);
	void sortAscending();
	void sortDescending();
	void printList(ostream& out);
	node * searchListLocation(string name);
	node * next(node* nd);
	node * prev(node* nd);
private:
	node * head;
	node * tail;
	int size;
};


//List definitions-----------------------------

//addFood(Food& fd) uses new for memory allocation
// throws bad_alloc if memory cannot be obtained
void List::addFood(Food &fd)
{
	size++;
	try
	{
		node * newNode = new node(fd);
	
		if (head == NULL && tail == NULL)
		{
			head = newNode;
			tail = newNode;
		}
		else
		{
			head->prev = newNode;
			newNode->next = head;
			head = newNode;
		}
	}
	catch (bad_alloc & ba)
	{
		cerr << "Could not allocate memory";
	}
}
// method for destructor
bool List::clearList()
{
	node * temp = head;
	if (head = NULL)
		return false;
	else
	{
		for (int i = 1; i < size; i++)
		{
			temp = next(temp);
			delete temp->prev;
		} 
		delete temp;
		//reset list properties
		size = 0; 
		head = NULL;
		tail = NULL;
	}
	return true;
}
// deleteFood(string) uses searchLocation() to delete
// at specific place in list
bool List::deleteFood(string name)
{
	node* temp = searchListLocation(name);
	if (temp == NULL)
		cout << "\nFood not found.\n";
	else if(size != 0)
	{
		if (next(temp) != NULL && prev(temp) != NULL) // in middle
		{
			next(temp)->prev = prev(temp);
			prev(temp)->next = next(temp);
		}
		else if (next(temp) == NULL) // at tail
		{
			tail = prev(temp);
			tail->next = NULL;
		}
		else // at head
		{
			head = next(temp);
			head->prev = NULL;
		}
		
		delete temp; 
		size--;
		cout << "\n" << name << " deleted. Current list size is " << size << ".\n";
		return true;
	}
	else
		cout << "\nList is empty.\n";

	return false;
}

List::node* List::next(node* nd)
{
	node * temp = nd->next;
	return temp;
}

List::node* List::prev(node* nd)
{
	node * temp = nd->prev;
	return temp;
}
List::node* List::searchListLocation(string name) // Big O = O(n)
// iterates through n items in while loop so n is max iteration count
{
	node * temp = head;
	while (temp->next != NULL)
		if (name == temp->food.getName())
			return temp;
		else
			temp = next(temp);
	if (name == temp->food.getName()) // check last element
		return temp;
	else
		return NULL;
}

void List::printList(ostream& out)
{
	node* curr = head;
	for (int x = 1; x <= size; x++)
	{
		cout << x << ": " << curr->food;
		curr = next(curr);
	}
}

void List::sortAscending() // Big O = O(n^2)
// bubble sort, iterates through n items in while loop
//	n times in for loop so n*n
{
	if (size > 0) // don't sort empty list
	{
		node * temp = head;
		node * nextFood = next(temp);
		int swapCount = 0;

		for (int i = 1; i < size; i++)
		{
			if (swapCount == 0 && i != 1)
				break;
			swapCount = 0;
			while(nextFood != NULL)
			{
				if (temp->food < nextFood->food) // < ---- only difference between sortDescending()
				{
					swapCount++; // track swap

					//establish nodes
					node * swap = next(temp); 
					node * outsideLeft = prev(temp);
					node * outsideRight = next(swap);
					
					// swap pointers to each other
					temp->prev = swap;
					swap->next = temp;

					// swap pointers to outside nodes
					temp->next = outsideRight;
					swap->prev = outsideLeft;

					if (outsideLeft == NULL) //watch for head of list
					{head = swap;}
					else outsideLeft->next = swap;

					if (outsideRight == NULL) // watch for tail of list
					{tail = temp; break;}
					else outsideRight->prev = temp;

					//get new next food
					nextFood = next(temp);
				}
				else // advance nodes 
				{
					temp = next(temp);
					nextFood = next(temp);
				}
			}
			temp = head; // reset to beginning of list
			nextFood = next(temp);
		}
	}
}

void List::sortDescending() // Big O = O(n^2)
{
	if (size > 0) // don't sort empty list
	{
		node * temp = head;
		node * nextFood = next(temp);
		int swapCount = 0;

		for (int i = 1; i < size; i++)
		{
			if (swapCount == 0 && i != 1)
				break;
			swapCount = 0;
			while (nextFood != NULL)
			{
				if (temp->food > nextFood->food) //<----only difference between sortAscending()
				{
					swapCount++; // track swap

					//establish nodes
					node * swap = next(temp);
					node * outsideLeft = prev(temp);
					node * outsideRight = next(swap);

					// swap pointers to each other
					temp->prev = swap;
					swap->next = temp;

					// swap pointers to outside nodes
					temp->next = outsideRight;
					swap->prev = outsideLeft;

					if (outsideLeft == NULL) //watch for head of list
					{
						head = swap;
					}
					else outsideLeft->next = swap;

					if (outsideRight == NULL) // watch for tail of list
					{
						tail = temp; break;
					}
					else outsideRight->prev = temp;

					//get new next food
					nextFood = next(temp);
				}
				else // advance nodes 
				{
					temp = next(temp);
					nextFood = next(temp);
				}
			}
			temp = head; // reset to beginning of list
			nextFood = next(temp);
		}
	}
}

#endif
