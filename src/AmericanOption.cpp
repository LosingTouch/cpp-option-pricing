#include "AmericanOption.h"

// Constructor
AmericanOption::AmericanOption(double expiry, double strike) : Option(expiry){
    if (strike <= 0){
		throw std::invalid_argument("Error: Strike should be positive.");
	}
	else {
		_strike = strike;
	}
}

// Destructor
AmericanOption::~AmericanOption(){}

// Overriden version of GetStrike method from option
double AmericanOption::GetStrike() const{
	return _strike;
}

// Overriden version of isAmericanOption
bool AmericanOption::isAmericanOption() const{
    return true;
}