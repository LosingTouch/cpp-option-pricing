#pragma once
#include <iostream>
#include <vector>

enum class OptionType{
    Call,
    Put};

class Option{

// Protected to allow derived class to access the expiry
protected:
    double _expiry;

public:
    Option(double expiry);
    virtual ~Option();

    double getExpiry() const;

    virtual double GetStrike() const = 0;
    virtual double payoff(double) const = 0;
    virtual OptionType GetOptionType() const = 0;
    
    virtual double payoffPath(std::vector<double>);
    virtual std::vector<double> GetTimeSteps();
    virtual bool isDigital() const;
    virtual bool isAsianOption() const;
    virtual bool isAmericanOption() const;
};