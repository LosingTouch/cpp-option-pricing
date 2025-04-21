#pragma once
#include <vector>
#include <cmath>
#include "Option.h"

class BlackScholesMCPricer{

private:
    Option* _option;
    double _initial_price;
    double _interest_rate;
    double _volatility;
    int _nb_paths;
    double _current_price_estimate;
    double _sum_payoff;
    double _squared_payoff;

public:
    BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility);
    ~BlackScholesMCPricer();

    int getNbPaths() const;
    void generate(int);
    double operator()() const;
    std::vector<double> confidenceInterval() const;
};