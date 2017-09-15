// File: RInsideDriver.cpp
// Programmer: Felix Neequaye Kotey
// Assignment: HW8
// Date submitted: 03/14/14
// -------------------------------------------------------------------------
// Description: 
// Input: 
// Output: 
// -------------------------------------------------------------------------


#include "Stock.hpp"

unsigned int  getNumDays();			// function to get number of days
std::string getFileName();			// function to get ticker symbol

int main(int argc, char *argv[])
{
	RInside R(argc, argv);              // create an embedded R instance

	std::string mysymbol;

	unsigned numDays;

	do
	{
		// create a stock class object
		Stock symbol;

		// prompt user for stock ticker symbol
		mysymbol =  getFileName();

		// get number of days to display prices
		// and returns and plot data
		numDays = getNumDays();

		// read file for a particular stock ticker symbol
		symbol.loadPricesFromFile(mysymbol.c_str());

 		// display mean returns and std dev for n number of days for a symbol
		std::cout << std::setw(20) << std::fixed << "Mean Return = ";
		std::cout << std::setprecision(9) << symbol.getMeanReturn(numDays) << std::endl;
		std::cout << std::setw(20) << std::fixed << "Return SDev = ";
		std::cout << std::setprecision(7) << symbol.getReturnStdDev(numDays) << std::endl;

		// create an RInside instance for plot title
		R["main"] = mysymbol;

		// call plotHistory to plot zoo object
		symbol.plotHistory(R,numDays);
		std::cin.clear();

	}while (true);

	return 0;
}


unsigned int getNumDays()	// function to get number of days
{
	int numdays;			// set number of days to 0

	while (true)
	{
		std::cout <<"Enter number of days: ";
		std::cin >> numdays;		// get user choice

		// Validate validating entered number of days
		if ((!std::cin) || (numdays <= 0))
		{
			// cin.clear() resets any error flags on the stream
			std::cin.clear();
			// prompting user for correct number of days
			std::cout << "\nHey, that's not a valid input for number of days" << std::endl;
		}
		else // Return a valid month for bill
		{
			std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');
			break;
		}
	}
	return numdays;
}


std::string getFileName()	// function to get ticker symbol
{
	std::string ticker;

	while (true)
	{
		// prompt user for stock ticker symbol
		std::cout <<"Enter symbol: ";
		std::getline(std::cin,ticker);

		// terminate program when user press enter
		if(ticker[0]=='\0')
		{
			std::cout << "All Done" << std::endl;
			exit(1);
		}

		// convert ticker symbol to upper case
		transform(ticker.begin(), ticker.end(), ticker.begin(), toupper);

		// Validate validating entered ticker symbol
		if ((ticker != "MSFT") && (ticker != "COST") && (ticker != "AMZN"))
		{
			// cin.clear() resets any error flags on the stream
			std::cin.clear();
			// prompting user for correct number of days
			std::cout << "\nEntered file does not file" << std::endl;
		}
		else // Return a valid ticker symbol
		{
			break;
		}
	}
	return ticker;
}
