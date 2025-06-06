#pragma once
#include <cmath>
#include "EuropeanVanillaOption.h"
#include "EuropeanDigitalOption.h"


class BlackScholesPricer{
private:
    Option* _option;
    double _asset_price;
    double _interest_rate;
    double _volatility;

public:
    BlackScholesPricer(Option* option, double asset_price, double interest_rate, double volatility);
    ~BlackScholesPricer();
    double StandardGaussianDistribution(double x) const;
    double operator()();
    double delta();
};