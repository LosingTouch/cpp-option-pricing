#pragma once
#include "Option.h"
#include "BinaryTree.h"
#include <cmath>

class CRRPricer{

private:
    Option* _option;
    int _depth;
    double _asset_price;
    double _up;
    double _down;
    double _interest_rate;
    BinaryTree<double> _tree;
    BinaryTree<bool> _exercise;
    
public:
    CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate);
    CRRPricer(Option* option, int depth, double asset_price, double interest_rate, double volatility);
    ~CRRPricer();
    void compute();
    double get(int id1, int id2);
    double operator()(bool closed_form=false);
    long double getFacto(int n);
    bool getExercice(int, int);
};