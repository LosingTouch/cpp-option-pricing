#include "AmericanPutOption.h"

// Constructor
AmericanPutOption::AmericanPutOption(double expiry, double strike) : AmericanOption(expiry, strike){}

// Destructor
AmericanPutOption::~AmericanPutOption(){}

// Overidden Payoff method
double AmericanPutOption::payoff(double z) const {
    return std::max(_strike - z, 0.0);
}

// Overidden GetOptionType method
OptionType AmericanPutOption::GetOptionType() const {
    return OptionType::Call;
}