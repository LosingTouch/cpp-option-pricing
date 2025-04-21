#include "AsianPutOption.h"

// Constructor
AsianPutOption::AsianPutOption(std::vector<double> timeSteps, double strike) : AsianOption(timeSteps){
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
AsianPutOption::~AsianPutOption(){}

// Payoff Function
double AsianPutOption::payoff(double z) const {
    return std::max(_strike - z, 0.0);
}

// Overriden Get Strike method
double AsianPutOption::GetStrike() const{
    return _strike;
}

//Overriden OptionType method
OptionType AsianPutOption::GetOptionType() const{
    return OptionType::Put;
}