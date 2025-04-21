#include "AsianCallOption.h"

// Constructor
AsianCallOption::AsianCallOption(std::vector<double> timeSteps, double strike) : AsianOption(timeSteps){
     if(strike <= 0)
    {
        throw std::invalid_argument("Error: Strike should be positive.");
    }
    else
    {
        _strike = strike;
    }

} 

// Destructor
AsianCallOption::~AsianCallOption(){}

// Payoff Function
double AsianCallOption::payoff(double z) const {
    return std::max(z - _strike, 0.0);
}

// Overriden Get Strike method
double AsianCallOption::GetStrike() const{
    return _strike;
}

//Overriden OptionType method
OptionType AsianCallOption::GetOptionType() const{
    return OptionType::Call;
}