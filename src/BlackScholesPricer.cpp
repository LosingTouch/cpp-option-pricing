#define _USE_MATH_DEFINES
#include "BlackScholesPricer.h"
#include <cmath>


// Constructor
BlackScholesPricer::BlackScholesPricer(Option* option, double asset_price, double interest_rate, double volatility){
        _option = option;
        _asset_price = asset_price;
        _interest_rate = interest_rate;
        _volatility = volatility;
    }

// Destructor
BlackScholesPricer::~BlackScholesPricer(){}

// Gaussian density function
double BlackScholesPricer::StandardGaussianDistribution(double x) const {
    return (1.0 / std::sqrt(2 * M_PI)) * std::exp(-0.5 * x * x); // Using Pi from cmath
}


// Option Price
double BlackScholesPricer::operator()(){

    // Compute d1 and d2 to use the B-S closed formula
    double strike = _option->GetStrike();
    double expiry = _option->getExpiry();
    double d1 = (std::log(_asset_price / strike) + ( _interest_rate + 0.5 * _volatility * _volatility) * expiry) / (_volatility * std::sqrt(expiry));
    double d2 = d1 - _volatility * std::sqrt(expiry);


    if(_option->GetOptionType() == OptionType::Call)
    {
        if(_option->isDigital() == true)
        {
            return std::exp(- _interest_rate * expiry) * 0.5 * std::erfc(- d2 / std::sqrt(2));
        }
        else // We are using the approximation of the Gaussian CDF (erfc)
        {
            return _asset_price * 0.5 * std::erfc(- d1 / std::sqrt(2)) - strike * std::exp(- _interest_rate * expiry)* 0.5 * std::erfc(- d2 / std::sqrt(2));
        }
    }
    else
    {
        if(_option->isDigital() == true) 
        {
            return std::exp(- _interest_rate * expiry) * 0.5 * std::erfc(d2 / std::sqrt(2));
        }
        else
        {
            return strike * std::exp(- _interest_rate * expiry)* 0.5 * std::erfc(d2 / std::sqrt(2)) - _asset_price * 0.5 * std::erfc(d1 / std::sqrt(2));
        }
    }
}

// Option's Delta
double BlackScholesPricer::delta(){

    double strike = _option->GetStrike();
    double expiry = _option->getExpiry();
    double d1 = (std::log(_asset_price / strike) + ( _interest_rate + 0.5 * _volatility * _volatility) * expiry) / (_volatility * std::sqrt(expiry));
    double d2 = d1 - _volatility * std::sqrt(expiry);
    
    if(_option->GetOptionType() == OptionType::Call) // Compute DELTA for the Call
    {   
        if(_option->isDigital() == true) // Digital Call
        {
            return (std::exp(-_interest_rate * expiry) * StandardGaussianDistribution(d2)) / (_volatility * _asset_price * std::sqrt(expiry));
        }
        else // Vanilla Call
        {
            return 0.5 * std::erfc(- d1 / std::sqrt(2));
        }
    }
    else // Compute DELTA for the Put
    {
        if(_option->isDigital() == true) // Digital Put
        {
            return - (std::exp(-_interest_rate * expiry) * StandardGaussianDistribution(d2)) / (_volatility * _asset_price * std::sqrt(expiry));
        }
        else // Vanilla Put
        {
            return 0.5 * std::erfc(- d1 / std::sqrt(2)) - 1;
        }

    }
}
