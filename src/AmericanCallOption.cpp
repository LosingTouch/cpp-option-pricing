#include "AmericanCallOption.h"

// Constructor
AmericanCallOption::AmericanCallOption(double expiry, double strike) : AmericanOption(expiry, strike){}

// Destructor
AmericanCallOption::~AmericanCallOption(){}


// Overidden Payoff method
double AmericanCallOption::payoff(double z) const {
    return std::max(z - _strike, 0.0);
}

// Overidden GetOptionType method
OptionType AmericanCallOption::GetOptionType() const {
    return OptionType::Call;
}