#pragma once
#include "AsianOption.h"

class AsianPutOption : public AsianOption{

private:
    double _strike;

public:
    AsianPutOption(std::vector<double> timeSteps, double z);
    ~AsianPutOption();

    double payoff(double) const override;
    double GetStrike() const override;
    OptionType GetOptionType() const override;
};