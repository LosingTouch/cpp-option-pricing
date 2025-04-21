#pragma once
#include "EuropeanDigitalOption.h"

class EuropeanDigitalPutOption : public EuropeanDigitalOption {

public:
    EuropeanDigitalPutOption(double expiry, double strike);
    ~EuropeanDigitalPutOption();
    
    double payoff(double) const override;
    OptionType GetOptionType() const override;

};