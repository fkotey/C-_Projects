// File: Stock.hpp
// Programmer: Felix Neequaye Kotey
// Assignment: HW6
// Date submitted: 02/25/14
// -------------------------------------------------------------------------
// Description: 
// Input: 
// Output: 

//////////////////////////////////////////////////////////////////////////////
//																			//
//		 Implementation of functions for stock class			            //
//																			//
//////////////////////////////////////////////////////////////////////////////


#include "stock.hpp"

// Default constructor
Stock::Stock() {}

// Copy constructor
Stock::Stock(const Stock& stk) : prices(stk.prices), returns(stk.returns) {}

// Default Destructor
Stock::~Stock(){}

// calculate the continuously compounded 
// returns and store them in the returns vector
void Stock::calcReturns()
{
	double ret;
	for (size_t i = 0; i < prices.size()-1; i++)
	{
		ret = log(prices[i] / prices[i+1]);
		returns.push_back(ret);
	}
}

//*******************************************************************************
//																				*
// The function loadPricesFromFile should take a ticker symbol parameter and    *
// read the associated csv file(supplied as part of the assignment) storing		*
// the adjusted close in the vector prices; it should then also call the		*
// calReturns function which will calculate the continuously compounded			*
// returns and store them in the returns vector.								*
//																				*
//*******************************************************************************
void Stock::loadPricesFromFile(const char * symbol)
{
	std::string line;								// strings to read line by line from file
	std::string date;								// strings to hold date from quotes
	double open;									// variable to store open price
	double high;									// variable to store high price
	double low;										// variable to store low price
	double close;									// variable to store close price
	long volume;									// variable to store volume price
	double adjusted;								// variable to store adjusted closed price
	
	char filename[20];								// c string for filename
	strcpy_s(filename, symbol);						// copying ticker symbol to c string
	strcat_s(filename, ".csv");						// create name of file to read
	
	std::fstream inputFile(filename, std::ios::in);	// open the csv file

	if (!inputFile)							// check if file exist
	{
		throw "Error opening file.\n";
	}

	std::getline(inputFile, line);			// read header from file

	while (std::getline(inputFile, line))
	{
		std::istringstream linestream(line);				// stream object to extract strings from line
		std::string b4comma;								// string to store data with no commas
		std::string aftcomma;								// string to combine data with no commas

		while (std::getline(linestream, b4comma, ','))		// removing commas and passing to string
		{
			aftcomma += b4comma + " ";						// put string together and separating with space
		}

		std::istringstream istr(aftcomma);					// extract data from string with no commas

		// passing stream object to variables as the right data-type
		istr >> date >> open >> high >> low >> close >> volume >> adjusted;

		//std::cout << std::fixed << std::setprecision(2) << adjusted << '\t';

		// store adjusted close prices in the price vector
		prices.push_back(adjusted);

		linestream.clear();												// clear string stream object
		istr.clear();													// clear string stream object
	}
	inputFile.close();
	/*std::cout << "\nReading of " << symbol << " file is complete" << std::endl;
	std::cout << "Size of " << symbol << " file is " << prices.size() << " long"<< std::endl;*/

	calcReturns();
}

//*******************************************************************************
//																				*
// The getPrices takes an unsigned parameter n, and returns the n				*
//  most recent returns. n must be less than the prices vector					*
//																				*
//*******************************************************************************
std::vector<double> Stock::getPrices(unsigned n)
{
	std::vector<double> result;

	if (n <= prices.size() && n > 0)
	{
		for (size_t i = 0; i < n; i++)
		{
			result.push_back(prices[i]);
		}
	}
	else
	{
		std::cout << "\nNumber is greater than data available";
		exit(1);
	}
		
	
	return result;
}

//*******************************************************************************
//																				*
// The getReturns function takes an unsigned parameter n, and returns the n		*
//  most recent returns. n must be less than the prices vector					*
//																				*
//*******************************************************************************
std::vector<double> Stock::getReturns(unsigned n)
{
	std::vector<double> result;

	if (n <= returns.size() && n > 0)
	{
		for (size_t i = 0; i < n; i++)
		{
			result.push_back(returns[i]);
		}
	}
	else
	{
		std::cout << "\n\nNumber is greater than data available\n";
		exit(1);
	}

	return result;
}

//*******************************************************************************
//																				*
// The getMeanReturn function takes an unsigned parameter n, and returns the n	*
//  most recent returns. n must be less than the prices vector					*
//																				*
//*******************************************************************************
double Stock::getMeanReturn(unsigned n)
{
	accumulator_set<double, stats<tag::mean> > acc;

	if (n <= returns.size() && n > 0)
	{
		for (size_t i = 0; i < n; i++)
		{
			acc(returns[i]);
		}
	}
	else
	{
		std::cout << "\n\nNumber is greater than data available\n";
		exit(1);
	}
	return mean(acc);
}

//*******************************************************************************
//																				*
// The getReturnStdDev function takes an unsigned parameter n, and returns 		*
// the n most recent returns. n must be less than the prices vector				*
//																				*
//*******************************************************************************
double Stock::getReturnStdDev(unsigned n)
{
	accumulator_set<double, stats<tag::variance> > acc;

	if (n <= returns.size() && n > 0)
	{
		for (unsigned i = 0; i < n; i++)
		{
			acc(returns[i]);
		}
	}
	else
	{
		std::cout << "\n\nNumber is greater than data available\n";
		exit(1);
	}
	return sqrt(variance(acc) * n / (n - 1));
}