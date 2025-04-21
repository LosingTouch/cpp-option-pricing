#pragma once
#include "Option.h"

class AmericanOption : public Option{

protected:
    double _strike;

public:
    AmericanOption(double, double);
    ~AmericanOption();

    double GetStrike() const override;
    bool isAmericanOption() const override;

    virtual double payoff(double) const override = 0;
    virtual OptionType GetOptionType() const override = 0;

};