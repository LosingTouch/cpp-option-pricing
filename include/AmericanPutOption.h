#pragma once
#include "AmericanOption.h"

class AmericanPutOption : public AmericanOption{

public:
    AmericanPutOption(double, double);
    ~AmericanPutOption();

    double payoff(double) const override;
    OptionType GetOptionType() const override;

};