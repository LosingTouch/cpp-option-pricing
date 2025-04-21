#pragma once
#include "Option.h"
#include <vector>

class AsianOption : public Option{

protected:
    std::vector<double> _timeSteps;

public:
    AsianOption(std::vector<double> timeSteps);
    ~AsianOption();

    virtual double payoff(double) const override = 0;
    virtual OptionType GetOptionType() const override = 0;

    std::vector<double> GetTimeSteps() override;
    double payoffPath(std::vector<double>) override;
    bool isAsianOption() const override;
    
};