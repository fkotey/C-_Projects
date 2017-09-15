// File: makeBinaryFile.cpp
// Programmer: Felix Neequaye Kotey
// Date submitted: 02/13/14
// -------------------------------------------------------------------------
// Description: 
// Input: 
// Output: 

#include <iostream>
#include <iomanip>
#include <random>
#include <ctime>  
#include <boost/random.hpp>						// Convenience header file
#include "Sortablevector.hpp"

int main()
{
	const int SIZE = 20;
	SortableVector<int> intTable(SIZE);			// create a vector to hold integers
	SortableVector<double> doubleTable(SIZE);	// create a vector to hold doubles

	// Mersenne Twister.
	boost::random::mt19937 myRng;

	// Set the seed.
	srand((unsigned)time(0));
	myRng.seed(static_cast<boost::int32_t> (std::time(0)));

	// Uniform in range [1,20]
	boost::random::uniform_int_distribution<int> intrandom(1, 20);

	// generate uniform random double numbers
	double lower_bound = 10;		// set the lower bound
	double upper_bound = 200;		// set the upper bound
	std::uniform_real_distribution<double> unif(lower_bound, upper_bound);
	std::default_random_engine re;
	
	// generate different outcomes based on the number of trials
	for (int x = 0; x < SIZE; x++)		
	{
		// generate random numbers b/n 1 to 20
		intTable[x] = intrandom(myRng);
	}

	for (int x = 0; x < SIZE; x++)
	{
		// generate random numbers b/n 10 to 200
		doubleTable[x] = unif(re);
	}

	// Display the values in the intTablevector .
	std::cout << " These are the values in intTable :\n";
	for (int x = 0; x < SIZE; x++)
	{
		if (x % 10 == 0)
			std::cout << std::endl;
		std::cout << std::setw(3) << intTable[x] << " ";
	}
		
	std::cout << "\n" << std::endl;

	// sort elements in the intTable vector
	intTable.SortItems(intTable);

	std::cout << " These are the sorted values in intTable :\n";
	
	for (int x = 0; x < SIZE; x++)
	{
		if (x %10 == 0)
			std::cout << std::endl;
		std::cout << std::setw(3) << intTable[x] << " ";
	}

	std::cout << "\n" << std::endl;

	// Display the values in the doubleTable vector .
	std::cout << " These are the values in doubleTable :\n";
	for (int x = 0; x < SIZE; x++)
	{
		if (x %5 == 0)
			std::cout << std::endl;
		std::cout << std::fixed << std::setprecision(2);
		std::cout << ' ' << doubleTable[x] << '\t';
	}

	std::cout << "\n" << std::endl;

	// sort elements in the doubleTable vector
	doubleTable.SortItems();

	std::cout << " These are the sorted values in doubleTable :\n";

	for (int x = 0; x < SIZE; x++)
	{
		if (x % 5 == 0)
			std::cout << std::endl;
		std::cout << std::fixed << std::setprecision(2);
		std::cout << ' ' << doubleTable[x] << '\t';
	}
	
	std::cout << std::endl;
	std::cin.get();
	return 0;
}