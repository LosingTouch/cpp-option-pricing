#pragma once
#include "AsianOption.h"

class AsianCallOption : public AsianOption{

private:
    double _strike;

public:
    AsianCallOption(std::vector<double> timeSteps, double z);
    ~AsianCallOption();

    double payoff(double) const override;
    double GetStrike() const override;
    OptionType GetOptionType() const override;
};