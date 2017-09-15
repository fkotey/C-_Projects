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
//				Header file for Stock class									//
//																			//
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include <vector>
#include <iostream>   
#include <algorithm> 
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstddef>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/variance.hpp>
#ifndef stock_HPP
#define stock_HPP

using namespace boost::accumulators;

class Stock
{
private:

	// member variables
	std::vector<double> prices;				// variable that hold the adjusted close prices
	std::vector<double> returns;			// variable that hold the continuously compounded returns
	
	// private member function				
	void calcReturns();						// calculate the continuously compounded 
											// returns and store them in the returns vector
public:

	// Constructors
	Stock();										// Default constructor
	Stock(const Stock& stk);						// Copy constructor
	virtual ~Stock();								// Default Destructor

	void loadPricesFromFile(const char * symbol);
	std::vector<double> getPrices(unsigned n);
	std::vector<double> getReturns(unsigned n);
	double getMeanReturn(unsigned n);
	double getReturnStdDev(unsigned n);
};

#endif	//end transaction_HPP