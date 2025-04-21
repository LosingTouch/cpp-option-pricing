#pragma once
#include "AmericanOption.h"

class AmericanCallOption : public AmericanOption{

public:
    AmericanCallOption(double, double);
    ~AmericanCallOption();

    double payoff(double) const override;
    OptionType GetOptionType() const override;

};