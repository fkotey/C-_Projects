// File: OptionPricer.cpp
// Programmer: Felix Neequaye Kotey
// Assignment: HW8
// Date submitted: 03/14/14
// -------------------------------------------------------------------------
// Description: M
// Input: 
// Output: 

#pragma warning(push)
#pragma warning(disable:4996)
#include <ql\quantlib.hpp>
#include <boost/timer.hpp>
#include <boost/tuple/tuple.hpp>									// Header file inclusion for Boost tuple library functions
#include <boost/tuple/tuple_io.hpp>									// Header file inclusion to use tuple input and output operators
#include <iostream>
#include <iomanip>

using namespace QuantLib;

void DefaultOption();
int getchoice();					// function to user choice
std::string getoptionType();		// function to get ticker symbol
double getStrikePrice();			// function to get strike price
double getRiskFreeRate();			// function to Risk-free interest rate
double getVolatility();				// function to get Volatility
boost::tuple<int, int, int> getDates();

int main(int, char*[])
{
	int choice;
	// Default American Option
	DefaultOption();

	bool loopEnd = false;
	do
	{
		std::cout << std::endl;
		choice = getchoice();															// get user input
		std::cin.clear();
		std::cout << std::endl;

		switch (choice)
		{
		case 1:
			try{

				// Option Parameters
				Option::Type type;
				Real underlying;
				Real strike;
				Rate riskFreeRate;
				Spread dividendYield = 0;
				Volatility volatility;
				double optionValue;
				Calendar calendar = TARGET();
				Date dtoday = QuantLib::Date::todaysDate();
				std::string optionType;

				// set inception date
				int startD;	int startM;	int startY;

				// set expiration date
				int maturityD;	int maturityM;	int maturityY;
				
				// get option type
				optionType = getoptionType();

				std::cout << "Today date is " << dtoday << std::endl;

				// get maturity date
				std::cout << "Inception date. ";
				boost::tuple<int, int, int> stdates = getDates();
				startD = stdates.get<0>();
				startM = stdates.get<1>();
				startY = stdates.get<2>();
				
				// get maturity date
				std::cout << "Maturity date. ";
				boost::tuple<int, int, int> optdates = getDates();
				maturityD = optdates.get<0>();
				maturityM = optdates.get<1>();
				maturityY = optdates.get<2>();

				std::cout << "Enter Underlying price: ";
				std::cin >> underlying;

				// get the strike price
				strike = getStrikePrice();

				// get the risk free rate interest rate
				riskFreeRate = getRiskFreeRate();

				// get the volatility
				volatility = getVolatility();

				if (optionType == "C")
					type = Option::Call;
				else 
					type = Option::Put;
				
				// Calendar stuff
				//Date today = QuantLib::Date::todaysDate();
				Date today(startD, Month(startM), startY);
				Settings::instance().evaluationDate() = today;
				DayCounter dayCounter = Actual365Fixed();
				Date maturity(maturityD, Month(maturityM), maturityY);

				// American exercise style option handler
				boost::shared_ptr<Exercise> americanExercise(
					new AmericanExercise(
					today, maturity));

				// Underlying price handler
				Handle<Quote> underlyingH(
					boost::shared_ptr<Quote>(
					new SimpleQuote(underlying)));

				// Yield term structure handler
				Handle<YieldTermStructure> flatTermStructure(
					boost::shared_ptr<YieldTermStructure>(
					new FlatForward(
					today,
					riskFreeRate / 100,
					dayCounter)));

				// Dividend handler
				Handle<YieldTermStructure> flatDividendTermStructure(
					boost::shared_ptr<YieldTermStructure>(
					new FlatForward(
					today,
					dividendYield,
					dayCounter)));

				// Volatility handler
				Handle<BlackVolTermStructure> flatVolTermStructure(
					boost::shared_ptr<BlackVolTermStructure>(
					new BlackConstantVol(
					today,
					calendar,
					volatility / 100,
					dayCounter)));

				// Payoff handler
				boost::shared_ptr<StrikedTypePayoff> payoff(
					new PlainVanillaPayoff(
					type,
					strike));

				// Black Scholes
				boost::shared_ptr<BlackScholesMertonProcess> BSMProcess(
					new BlackScholesMertonProcess(
					underlyingH,
					flatDividendTermStructure,
					flatTermStructure,
					flatVolTermStructure));

				// Option characteristics
				VanillaOption americanOption(payoff, americanExercise);

				// Pricing Engine : in this case Binomial Cox-Ross-Rubinstein
				Size timeSteps = 1000;

				americanOption.setPricingEngine(boost::shared_ptr<PricingEngine>(
					new BinomialVanillaEngine<CoxRossRubinstein>(BSMProcess,
					timeSteps)));

				optionValue = americanOption.NPV();

				// Outputting
				std::cout << "The Option price is :\t" << std::setprecision(5) << optionValue << std::endl;
				std::cout << std::endl;

			}
			catch (std::exception& err)
			{
				std::cerr << err.what() << std::endl;
				break;
			}
			catch (...)
			{
				std::cerr << "unknown error" << std::endl;
				break;
			}
		break;

		case 2:
			exit(1);
		}

	} while (choice != 2);
}

void DefaultOption()
{
	boost::timer timer;
	std::cout << std::endl;

	// Option Parameters
	Option::Type type(Option::Call);
	Real underlying = 36;
	Real strike = 40;
	Spread dividendYield = 0.00;
	Rate riskFreeRate = 0.06;
	Volatility volatility = 0.20;
	double optionValue;

	std::string optionType;

	// Calendar stuff
	Calendar calendar = TARGET();
	Date today = QuantLib::Date::todaysDate();
	Settings::instance().evaluationDate() = today;
	DayCounter dayCounter = Actual365Fixed();
	Date maturity = today + 12 * Months;

	// American exercise style option handler
	boost::shared_ptr<Exercise> americanExercise(
		new AmericanExercise(
		today, maturity));

	// Underlying price handler
	Handle<Quote> underlyingH(
		boost::shared_ptr<Quote>(
		new SimpleQuote(underlying)));

	// Yield term structure handler
	Handle<YieldTermStructure> flatTermStructure(
		boost::shared_ptr<YieldTermStructure>(
		new FlatForward(
		today,
		riskFreeRate,
		dayCounter)));

	// Dividend handler
	Handle<YieldTermStructure> flatDividendTermStructure(
		boost::shared_ptr<YieldTermStructure>(
		new FlatForward(
		today,
		dividendYield,
		dayCounter)));

	// Volatility handler
	Handle<BlackVolTermStructure> flatVolTermStructure(
		boost::shared_ptr<BlackVolTermStructure>(
		new BlackConstantVol(
		today,
		calendar,
		volatility,
		dayCounter)));

	// Payoff handler
	boost::shared_ptr<StrikedTypePayoff> payoff(
		new PlainVanillaPayoff(
		type,
		strike));

	// Black Scholes
	boost::shared_ptr<BlackScholesMertonProcess> BSMProcess(
		new BlackScholesMertonProcess(
		underlyingH,
		flatDividendTermStructure,
		flatTermStructure,
		flatVolTermStructure));

	// Option characteristics
	VanillaOption americanOption(payoff, americanExercise);

	// Pricing Engine : in this case Binomial Cox-Ross-Rubinstein
	Size timeSteps = 1000;

	americanOption.setPricingEngine(boost::shared_ptr<PricingEngine>(
		new BinomialVanillaEngine<CoxRossRubinstein>(BSMProcess,
		timeSteps)));

	std::cout << "American Option pricing using the Binomial CRR method" << std::endl << std::endl;
	std::cout << "Option type = " << type << std::endl;
	std::cout << "Initiation = " << today << std::endl;
	std::cout << "Maturity = " << maturity << std::endl;
	std::cout << "Underlying price = " << underlying << std::endl;
	std::cout << "Strike = " << strike << std::endl;
	std::cout << "Risk-free interest rate = " << io::rate(riskFreeRate)
		<< std::endl;
	std::cout << "Dividend yield = " << io::rate(dividendYield)
		<< std::endl;
	std::cout << "Volatility = " << io::volatility(volatility)
		<< std::endl;

	optionValue = americanOption.NPV();
	std::cout << "Option price :\t" << std::setprecision(5) << optionValue << std::endl;
	std::cout << std::endl;
}

int getchoice()		// function get user input
{
	int choice;		// variable to get user input
	while (true)
	{
		std::cout << "Enter 1 to price another American Option" << std::endl;
		std::cout << "Enter 2 to quit the program" << std::endl;
		std::cout << "Input Choice: " << std::flush; std::cin >> choice;
		std::cin.clear();

		if (std::cin.fail() || (choice != 1 && choice != 2))
		{
			std::cout << "\nHey, that's not a valid input for the choice\n" << std::endl;		// prompting user for correct hours used
			std::cin.clear();																// cin.clear() resets any error flags on the stream
			std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');			// will flush the input stream of garbage
			
		}
		else
		{
			std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');
			break;
		}
	}
	return choice;
}

std::string getoptionType()	// function to get option type
{
	std::string opttype;

	while (true)
	{
		// prompt user for option type
		std::cout << "Select Option type, C for Call, P for put: ";
		std::cin >> opttype;

		// convert option type to upper case
		transform(opttype.begin(), opttype.end(), opttype.begin(), toupper);

		// Validate validating entered option type
		if ((opttype != "C") && (opttype != "P"))
		{
			// cin.clear() resets any error flags on the stream
			std::cin.clear();
			// prompting user for coption type
			std::cout << "\nNot a valid option type" << std::endl;
		}
		else // Return a valid option type
		{
			break;
		}
	}
	return opttype;
}

double getStrikePrice()			// function to get strike price
{
	double StrikePrice;			

	while (true)
	{
		std::cout << "Enter the Strike Price: ";
		std::cin >> StrikePrice;

		// Validate validating entered strike price
		if ((!std::cin) || (StrikePrice <= 0))
		{
			// cin.clear() resets any error flags on the stream
			std::cin.clear();
			// prompting user for correct strike price
			std::cout << "\nHey, that's not a valid input" << std::endl;
		}
		else // Return a valid strike price
		{
			std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');
			break;
		}
	}
	return StrikePrice;
}


double getRiskFreeRate()			// function to Risk-free interest rate
{
	double RiskFreeRate;

	while (true)
	{
		std::cout << "Enter the Risk-free interest rate (%): ";
		std::cin >> RiskFreeRate;

		// Validate validating entered Risk-free interest rate
		if ((!std::cin) || (RiskFreeRate <= 0))
		{
			// cin.clear() resets any error flags on the stream
			std::cin.clear();
			// prompting user for correct Risk-free interest rate
			std::cout << "\nHey, that's not a valid input" << std::endl;
		}
		else // Return a valid Risk-free interest rate
		{
			std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');
			break;
		}
	}
	return RiskFreeRate;
}

double getVolatility()			// function to get Volatility
{
	double vol;

	while (true)
	{
		std::cout << "Enter the Volatility (%): ";
		std::cin >> vol;

		// Validate validating entered Volatility
		if ((!std::cin) || (vol <= 0))
		{
			// cin.clear() resets any error flags on the stream
			std::cin.clear();
			// prompting user for Volatility
			std::cout << "\nHey, that's not a valid input" << std::endl;
		}
		else // Return a valid Volatility
		{
			std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');
			break;
		}
	}
	return vol;
}

boost::tuple<int, int,int> getDates()
{ // Standard deviation and error

	int mdays; int mmonths; int ymears;

	while (true)
	{
		std::cout << "Enter date separated by space(dd mm yyyy): ";
		std::cin >> mdays >> mmonths >> ymears;

		// Validate entered user inputs for dates
		if ((mdays <= 0) || (mmonths <= 0) || (ymears <= 0))
		{
			// cin.clear() resets any error flags on the stream
			std::cin.clear();
			// prompting user for Volatility
			std::cout << "\nHey, that's not a valid input" << std::endl;
		}
		else // Return a valid Volatility
		{
			std::cin.ignore(std::numeric_limits <std::streamsize> ::max(), '\n');
			break;
		}
	}

	// return a tuple with days, month and year for date
	return boost::tuple<int, int, int>(mdays, mmonths, ymears);
}