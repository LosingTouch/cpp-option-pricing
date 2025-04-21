#include "AsianOption.h"

// Constructor
AsianOption::AsianOption(std::vector<double> timeSteps) : Option(timeSteps.back()), _timeSteps(timeSteps){}

// Destructor
AsianOption::~AsianOption(){}

// Getter Method for Time Steps
std::vector<double> AsianOption::GetTimeSteps(){
    return _timeSteps;
}

// Overriden version
double AsianOption::payoffPath(std::vector<double> asset_prices){

    if (asset_prices.empty()) {
        return 0.0;
    }
    
    double sum = 0;
	for (size_t i = 0; i < asset_prices.size(); i++)
    {
    	sum += asset_prices.at(i);
    }
    // We return the payoff of the mean price
	return payoff(sum / asset_prices.size());
}

// Overriden version of isAsian method
bool AsianOption::isAsianOption() const{
    return true;
}
