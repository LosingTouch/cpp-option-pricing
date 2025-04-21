#include "CallOption.h"

// Constructor
CallOption::CallOption(double expiry, double strike) : EuropeanVanillaOption(expiry, strike){}

// Destructor
CallOption::~CallOption(){}

// Payoff function
double CallOption::payoff(double z) const {
    return std::max(z - _strike, 0.0);
}

// Option Type
OptionType CallOption::GetOptionType() const{
    return OptionType::Call;
}