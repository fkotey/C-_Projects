// File: Stock.hpp
// Programmer: Felix Neequaye Kotey
// Assignment: HW8
// Date submitted: 03/14/14
// -------------------------------------------------------------------------
// Description: 
// Input: 
// Output: 
// -------------------------------------------------------------------------

//////////////////////////////////////////////////////////////////////////////
//																			//
//				Header file for Stock class									//
//																			//
//////////////////////////////////////////////////////////////////////////////


#include <RInside.h>                    // for the embedded R via RInside
#include <Rcpp.h>
#include <vector>
#include <iostream>   
#include <algorithm> 
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstddef>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>

using namespace Rcpp;

#ifndef stock_HPP
#define stock_HPP

class Stock
{
private:

	// member variables
	std::vector<double> prices;				// variable that hold the adjusted close prices
	std::vector<double> returns;			// variable that hold the continuously compounded returns
	std::vector<std::string> dates;			// variable that hold the continuously compounded returns
	
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
	std::vector<std::string> getDates(unsigned n);
	double getMeanReturn(unsigned n);
	double getReturnStdDev(unsigned n);

	void plotHistory(RInside& R_, unsigned n);				// to call R for new plot
};

#endif	//end transaction_HPP
