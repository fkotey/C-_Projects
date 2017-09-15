// File: Stock.hpp
// Programmer: Felix Neequaye Kotey
// Assignment: HW6
// Date submitted: 02/25/14
// -------------------------------------------------------------------------
// Description: 
// Input: 
// Output: 
// -------------------------------------------------------------------------
// This program shows reads the historical closed prices 
// for MSFT, COST, and AMZN, compute the mean return and
// standard deviation

#include "Stock.hpp"

int main()
{
	Stock symbol[3];
	//int input;
	
	const char* tickers[] = { "MSFT", "COST", "AMZN" };
	int strsize = sizeof(tickers) / sizeof(tickers[0]);

	symbol[0].loadPricesFromFile("MSFT");
	symbol[1].loadPricesFromFile("COST");
	symbol[2].loadPricesFromFile("AMZN");

	///////////////////////////////////////////////////////////////////////////////
	//                   display of last 10 days stats							 //
	///////////////////////////////////////////////////////////////////////////////
	std::cout << "\nStatistics for the last 10 days:\n" << std::endl;
	std::cout << std::left << "Ticker" << std::setw(18) << std::right;
	std::cout << std::fixed << "Mean Return";
	std::cout << std::setw(18) << "Return Std.Dev" << std::endl;

	for (int i = 0; i < strsize; i++)
	{
		// 10 Statistics for ticker symbols
		std::cout << std::left << tickers[i] << std::setw(20) << std::right;
		std::cout << std::fixed << std::setprecision(6) << symbol[i].getMeanReturn(10);
		std::cout << std::setw(18) << symbol[i].getReturnStdDev(10) << std::endl;
	}

	///////////////////////////////////////////////////////////////////////////////
	//                   display of last 250 days stats							 //
	///////////////////////////////////////////////////////////////////////////////
	std::cout << "\nStatistics for the last 250 days:\n" << std::endl;
	std::cout << std::left << "Ticker" << std::setw(18) << std::right;
	std::cout << std::fixed << "Mean Return";
	std::cout << std::setw(18) << "Return Std.Dev" << std::endl;

	for (int i = 0; i < strsize; i++)
	{
		// 250 Statistics for ticker symbols
		std::cout << std::left << tickers[i] << std::setw(20) << std::right;
		std::cout << std::fixed << std::setprecision(6) << symbol[i].getMeanReturn(250);
		std::cout << std::setw(18) << symbol[i].getReturnStdDev(250) << std::endl;
	}

	///////////////////////////////////////////////////////////////////////////////
	//                   display of last 125 days stats							 //
	///////////////////////////////////////////////////////////////////////////////
	std::cout << "\nStatistics for the last 125 days:\n" << std::endl;
	std::cout << std::left << "Ticker" << std::setw(18) << std::right;
	std::cout << std::fixed << "Mean Return";
	std::cout << std::setw(18) << "Return Std.Dev" << std::endl;

	for (int i = 0; i < strsize; i++)
	{
		 // 125 Statistics for ticker symbols
		std::cout << std::left << tickers[i] << std::setw(20) << std::right;
		std::cout << std::fixed << std::setprecision(6) << symbol[i].getMeanReturn(125);
		std::cout << std::setw(18) << symbol[i].getReturnStdDev(125) << std::endl;
	}

	// Display recent price history symbols
	std::cout << "\nRecent history:\n" << std::endl;

	for (int i = 0; i < strsize; i++)
	{
		std::cout << tickers[i] << ":" << std::endl;
		std::cout << "Prices:" << std::setw(11);
		for (int j = 0; j < 5; j++)
		{
			std::cout << std::fixed << std::setprecision(2);
			std::cout << symbol[i].getPrices(5)[j] << std::setw(8);
		}

		std::cout << "\nreturns:" << std::setw(10);

		for (int k = 0; k < 5; k++)
		{
			std::cout << std::fixed << std::setprecision(4);
			std::cout << symbol[i].getReturns(5)[k] << std::setw(8);
		}
		std::cout <<  "\n"<< std::endl;
	}

	//std::cin.get();
	return 0;
}
