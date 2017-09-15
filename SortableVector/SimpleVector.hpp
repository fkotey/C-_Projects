// File: makeBinaryFile.cpp
// Programmer: Felix Neequaye Kotey
// Date submitted: 02/13/14
// -------------------------------------------------------------------------
// Description: 
// Input: 
// Output: 

#ifndef SIMPLEVECTOR_H
#define SIMPLEVECTOR_H

#include <algorithm>
#include <iostream>
#include <cstdlib>
using namespace std;

template <class T>
class SimpleVector
{
private:
	   T *aptr;
	   int arraySize;  
	   static int m_def_size; // Dynamic array static default size.
	   void subError();       // Handles subscripts out of range
public:
	   SimpleVector();					    // Default constructor
	   SimpleVector(const int);             // Constructor with array size
	   SimpleVector(const SimpleVector &);  // Copy constructor
	   virtual  ~SimpleVector(); 	        // Destructor
	   int size()
		 { return arraySize; }
	   T &operator[](int);    // Overloaded [] operator
	   void print();          // outputs the array elements.
};

// set array default size to 10
template <typename T>
int SimpleVector<T>::m_def_size = 10;


//*******************************************************
// Default Constructor for SimpleVector class. Sets     *
// the size of the array and allocates memory for it.   *
//*******************************************************

template <class T>
SimpleVector<T>::SimpleVector() : arraySize(m_def_size), m_data(new T[m_def_size]) {}


//*******************************************************
// Constructor for SimpleVector class. Sets the size    *
// of the array and allocates memory for it.            *
//*******************************************************
template <class T>
SimpleVector<T>::SimpleVector(const int s)
{
	arraySize = s;
	aptr = new T [s];
	for (int count = 0; count < arraySize; count++)
	   aptr[count] = T();
}

//******************************************************
// Copy Constructor for SimpleVector class.            *
//******************************************************
template <class T>
SimpleVector<T>::SimpleVector(const SimpleVector &obj)
{
   arraySize = obj.arraySize;
   aptr = new T [arraySize];
   for(int count = 0; count < arraySize; count++)
	  aptr[count] = obj[count];
}

//*****************************************************
// Destructor for SimpleVector class.                 *
//*****************************************************
template <class T>
SimpleVector<T>::~SimpleVector()
{
	if (arraySize > 0)
	   delete [] aptr;
}

//******************************************************
// subError function. Displays an error message and    *
// terminates the program when a subscript is out of   *
// range.                                              *
//******************************************************
template <class T>
void SimpleVector<T>::subError()
{
	cout << "ERROR: Subscript out of range.\n";
	exit(0);
}

//*******************************************************
// Overloaded [] operator. The argument is a subscript. *
// This function returns a reference to the element     *
// in the array indexed by the subscript.               *
//*******************************************************
template <class T>
T &SimpleVector<T>::operator[](int sub)
{
	if (sub < 0 || sub >= arraySize)
	  subError();
	return aptr[sub];
}

//********************************************************
// prints all the entries is the array.                  *
//********************************************************
template <class T>
void SimpleVector<T>::print( )
{
   for (int k = 0; k < arraySize; k++ )
	 cout << aptr[k] << "  ";
   cout << endl;  
}
#endif	//end SIMPLEVECTOR_H

