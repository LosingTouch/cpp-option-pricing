#pragma once
#include "EuropeanVanillaOption.h"

class CallOption : public EuropeanVanillaOption { 
public:
    CallOption(double expiry, double strike);
    ~CallOption();
    
    double payoff(double z) const override;
    OptionType GetOptionType() const override;

};