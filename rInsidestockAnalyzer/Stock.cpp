// File: Stock.cpp
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
//		 Implementation of functions for stock class			            //
//																			//
//////////////////////////////////////////////////////////////////////////////


#include "Stock.hpp"

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
	NumericVector result(prices.size());
	result = prices;
	NumericVector rets = -diff(log(result));
	returns = as<std::vector<double> >(rets);
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
	std::strcpy(filename, symbol);					// copying ticker symbol to c string
	std::strcat(filename, ".csv");					// create name of file to read
	
	std::fstream inputFile(filename, std::ios::in);	// open the csv file

	if (!inputFile)							// check if file exist
	{
		std::cout << "Error opening file.\n";
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

		// store adjusted close prices and dates
		dates.push_back(date);								// push back dates into dates vector
		prices.push_back(adjusted);							// push back prices into prices vector
		linestream.clear();									// clear string stream object
		istr.clear();										// clear string stream object
	}
	inputFile.close();

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
		std::cout << "Program is terminating\n";
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
		std::cout << "Program is terminating\n";
		exit(1);
	}

	return result;
}

//*******************************************************************************
//																				*
// The getDates function takes an unsigned parameter n, and returns the n		*
//  most recent dates. n must be less than the prices vector					*
//																				*
//*******************************************************************************
std::vector<std::string> Stock::getDates(unsigned n)
{
	std::vector<std::string> result;

	if (n <= returns.size() && n > 0)
	{
		for (size_t i = 0; i < n; i++)
		{
			result.push_back(dates[i]);
		}
	}
	else
	{
		std::cout << "\n\nNumber is greater than data available\n";
		std::cout << "Program is terminating\n";
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
	// create numeric vector of size n
	NumericVector result(n);
	if (n <= returns.size() && n > 0)
	{
		// assign returns to NumericVector
		result = getReturns(n);
	}
	else
	{
		std::cout << "\n\nNumber is greater than data available\n";
		std::cout << "Program is terminating\n";
		exit(1);
	}
	// return the mean returns
	return mean(result);
}

//*******************************************************************************
//																				*
// The getReturnStdDev function takes an unsigned parameter n, and returns 		*
// the n most recent returns. n must be less than the prices vector				*
//																				*
//*******************************************************************************
double Stock::getReturnStdDev(unsigned n)
{
	// create numeric vector of size n
			NumericVector result(n);

	if (n <= returns.size() && n > 0)
	{
		result = getReturns(n);
	}
	else
	{
		std::cout << "\n\nNumber is greater than data available\n";
		std::cout << "Program is terminating\n";
		exit(1);
	}
	return sd(result);
}

void Stock::plotHistory(RInside& R_, unsigned n)				// to call R for new plot
{
	//compute annualized volatility
	double ann_vol = sqrt(250)*100*getReturnStdDev(n);
	//compute annualized mean return
	double ann_ret = 250*100*getMeanReturn(n);

	R_["annret"] = ann_ret; 			// create R instances of returns vector
	R_["annvol"] = ann_vol; 			// create R instances of returns vector
	R_["returns"] = getReturns(n); 		// create R instances of returns vector
	R_["prices"] = getPrices(n); 		// create R instances of prices vector
	R_["dates"] = getDates(n);			// create R instances of dates vector

	std::string txt = " suppressMessages(library(zoo))";
	R_.parseEvalQ(txt) ;		//load the zoo library

	// forcing a display to be able to plot to screen
	std::string cmd = 	"x11(); plot(zoo(cbind(prices,returns),order.by=as.Date(dates)),"
						"type =c('l','h'),col=4,main=main, xlab='');"
						"title(sub = paste('annuliazed return ',' = ', round(annret, 2), '%',',"
						" ','annuliazed vol ',' = ', round(annvol, 2), '%',sep =''));"
						"Sys.sleep(5);dev.off()";

	// parseEvalQ evluates without assignment
	R_.parseEvalQ(cmd);
}


