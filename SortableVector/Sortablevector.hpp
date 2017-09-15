#pragma once

//*******************************************************
//*******************************************************
// class template named SortableVector. This class is 	*
// derived from the SimpleVector. It has a member	    *
// that sorts the array elements in ascending order		*
//*******************************************************
//*******************************************************
#ifndef SORTABLEVECTOR_H
#define SORTABLEVECTOR_H
#include "SimpleVector.hpp"

template <class T>
class SortableVector : public SimpleVector<T>
{
public:

	// Default constructor
	SortableVector();

	// Constructor with array size
	SortableVector(const int size);

	// Copy constructor
	SortableVector(const SortableVector &obj);

	// Default Destructor
	~SortableVector() {};

	// functions to sort item
	void SortItems(SortableVector &obj);
	void SortItems();
};

//*******************************************************
// Default constructor for the Sortable Vector derived	*
//*******************************************************
template <class T>
SortableVector<T>::SortableVector() : SimpleVector<T>() {}


//*******************************************************
// Constructor for SortableVector class. Sets the size  *
// of the array and allocates memory for it.            *
//*******************************************************
template <class T>
SortableVector<T>::SortableVector(const int size) : SimpleVector<T>(size) {}

//*******************************************************
// Copy constructor for the Sortable Vector derived		*
// from SimpleVector class							    *
//*******************************************************

template <class T>
SortableVector<T>::SortableVector(const SortableVector & obj) : SimpleVector<T>(obj)
{
}

//*******************************************************
// function to sort a Sortable Vector in an ascending	*
// order. Takes no argument						        *
//*******************************************************

template <class T>
void SortableVector<T>::SortItems()
{
	T temp;
	bool swap;

	do
	{
		swap = false;
		for (int i = 0; i < this->size() - 1; i++)
		{
			for (int j = 0; j < this->size() - 1; j++)
			{
				if (this->operator[](j) > this->operator[](j + 1))
				{
					temp = this->operator[](j);
					this->operator[](j) = this->operator[](j + 1);
					this->operator[](j + 1) = temp;
				}
			}
		}
	} while (swap);
}

//*******************************************************
// function to sort a Sortable Vector in an ascending	*
// order. Takes an argument	of type	SortableVector      *
//*******************************************************

template <class T>
void SortableVector<T>::SortItems(SortableVector &obj)
{
	T temp;
	bool swap;

	do
	{
		swap = false;
		for (auto index = 0; index < obj.size() - 1; index++)
		{
			if (obj[index] > obj[index + 1])
			{
				temp = obj[index];
				obj[index] = obj[index + 1];
				obj[index + 1] = temp;
				swap = true;
			}
		}
	} while (swap);
}
#endif //end SORTABLEVECTOR_H
