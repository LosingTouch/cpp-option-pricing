#pragma once
#include "Option.h"
#include "EuropeanVanillaOption.h"

class EuropeanDigitalOption : public Option{
protected:
    double _strike;

public:
    EuropeanDigitalOption(double expiry, double strike);
    ~EuropeanDigitalOption();

    virtual double payoff(double) const override = 0;
    virtual OptionType GetOptionType() const override = 0;
    virtual double GetStrike() const override;
    bool isDigital() const override;

    friend class BlackScholesPricer;
};
