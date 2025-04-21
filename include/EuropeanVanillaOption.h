#pragma once
#include "Option.h"

class EuropeanVanillaOption : public Option{
protected:
    double _strike;

public:
    EuropeanVanillaOption(double expiry, double strike);
    ~EuropeanVanillaOption();

    friend class BlackScholesPricer;
    double GetStrike() const override;

    virtual double payoff(double) const override = 0;
    virtual OptionType GetOptionType() const override = 0;
};
