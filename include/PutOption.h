#pragma once
#include "EuropeanVanillaOption.h"

class PutOption : public EuropeanVanillaOption {

public:
    PutOption(double expiry, double strike);
    ~PutOption();
    double payoff(double) const override;
    OptionType GetOptionType() const override;

};