#pragma once
#include "EuropeanDigitalOption.h"

class EuropeanDigitalCallOption : public EuropeanDigitalOption {

public:
    EuropeanDigitalCallOption(double expiry, double strike);
    ~EuropeanDigitalCallOption();
    
    double payoff(double) const override;
    OptionType GetOptionType() const override;

};