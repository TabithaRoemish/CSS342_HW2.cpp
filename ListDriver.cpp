//ListDriver.cpp
// Programmer: Tabitha Roemish
// Date: 10/10/2017
// File contains:
//		main()
//		readInt()
//		readChar()

#include <iostream>
#include "List.h"
#include "Food.h"

// function declarations
void readInt(int& input);
void readChar(char &input);

//array of foods to put in linked list. 
Food FoodBank[] = { Food("Apple", 95), Food("Dinner Roll", 105), Food("Cheese, 1oz", 113), 
	Food("Wine, 5oz", 125), Food("Olives, 3.5oz", 115), Food("Salami, 1oz", 119) };

using namespace std;

int main()
{
	List lst1;
	for (int i = 0; i < sizeof(FoodBank) / sizeof(FoodBank[0]); i++)
		lst1.addFood(FoodBank[i]); // add food array to linked list

	cout << "This is our current list of foods" << endl;
	lst1.printList(cout);

	try
	{
		cout << "\nWould you like to add a food? (Y/N): ";
		char response;
		readChar(response);
		while (toupper(response) == 'Y')
		{
			cout << "\nPlease enter the food name: ";
			string tempName;
			getline(cin, tempName);
			cout << "\nPlease enter the calories for this food: ";
			int tempCal;
			readInt(tempCal);
			Food newFood(tempName, tempCal);
			lst1.addFood(newFood);
			cout << "\nWould you like to enter another food? (Y/N): ";
			readChar(response);
		}

		cout << "\nThank you for your input. Here is the list sorted in ascending order based on calories: " << endl;
		lst1.sortAscending();
		lst1.printList(cout);

		cout << "\nHere is the list sorted in descending order based on calories" << endl;
		lst1.sortDescending();
		lst1.printList(cout);

		cout << "\nWould you like to delete a food? (Y/N): "; // test search
		readChar(response);
		while (toupper(response) == 'Y')
		{
			cout << "\nPlease enter the food to delete (enter exact wording, including oz if applicable): ";
			string tempName;
			getline(cin, tempName);
			lst1.deleteFood(tempName);
			cout << "\nWould you like to delete another food? (Y/N): ";
			readChar(response);
		}

		cout << "\nHere is the final list: " << endl;
		lst1.printList(cout);

		cin.get(); // hold window open
	}
	catch (bad_alloc & ex)
	{
		cerr << "Memory error: " << ex.what() << endl;
		return 1; // EXIT_FAILURE - changed for g++
	}

	return 0;
}

void readInt(int& input)
{
	while (!(cin >> input))
	{
		cin.clear();
		cin.ignore(50, '\n');
		cout << "Invalid Input.";
	}
	cin.clear();
	cin.ignore(50, '\n');
}

void readChar(char &input)
{
	cin >> input;
	while (toupper(input) != 'Y' && toupper(input) != 'N')
	{
		cin.clear();
		cin.ignore(50, '\n');
		cout << "Please enter Y or N: ";
		cin >> input;
	}
	cin.clear();
	cin.ignore(50, '\n');
}
