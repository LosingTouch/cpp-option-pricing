#include "CRRPricer.h"
#include <vector>
#include <stdexcept>

// Constructor
CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate) :
 _option(option), _depth(depth), _asset_price(asset_price), _up(up), _down(down), _interest_rate(interest_rate), _tree(depth)
{
    if (!(_down < _interest_rate && _interest_rate < _up)) {
        throw std::invalid_argument("Error: Arbitrage opportunity.");
    }

    if (_option->isAsianOption() == true){
        throw std::invalid_argument("Error: CRR Pricer not compatible with Asian Options");
    }
}

// Overloaded constructor to compute U, D and R using volatility
CRRPricer::CRRPricer(Option* option, int depth, double asset_price, double r, double volatility) :
 _option(option), _depth(depth), _asset_price(asset_price), _tree(depth)
{
    if (_option->isAsianOption() == true){
        throw std::invalid_argument("Error: CRR Pricer not compatible with Asian Options");
    }
    else{
        float h = option->getExpiry() / depth;
        _up = std::exp((r + (volatility * volatility) / 2 ) * h + volatility * std::sqrt(h)) - 1;
        _down = std::exp((r + (volatility * volatility) / 2 ) * h - volatility * std::sqrt(h)) - 1;
        _interest_rate = std::exp(r * h) - 1;
    
        if (!(_down < _interest_rate && _interest_rate < _up)) {
            throw std::invalid_argument("Error: Arbitrage opportunity.");
        }
    }
}

// Destructor
CRRPricer::~CRRPricer(){}

// Create the Tree with Asset Prices
void CRRPricer::compute(){
    for (int i = 0; i <= _depth; i++){
        for (int j = 0; j <= i; ++j) {
            _tree.setNode(i, j, _asset_price * std::pow(1 + _up, j) * std::pow(1 + _down, i - j));
        }
    }
}

// Getter Method
double CRRPricer::get(int step, int node){
    return _option->payoff(_tree.getNode(step, node));
}

// Get Exercice Method
bool CRRPricer::getExercice(int step, int node){
    return _exercise.getNode(step, node);
}

// Factorial function
long double CRRPricer::getFacto(int n){
    if (n < 0) 
    {
        throw std::invalid_argument("Error : n should be positive.");
    }
    else if (n==0 || n==1)
    {
        return 1;
    }
    return n * getFacto(n-1);
}

// Operator Method
double CRRPricer::operator()(bool closed_form){

    // We create the prices tree
    compute();
    double q = (_interest_rate - _down) / (_up - _down);

    if(closed_form){

        // We use the closed-form formula
        float price_closed_form = 0;
        for(int i = 0; i <= _depth; i++){
            double binomial = getFacto(_depth) / (getFacto(i) * getFacto(_depth - i));
            price_closed_form += binomial * std::pow(q, i) * std::pow(1 - q, _depth - i) * _option->payoff(_tree.getNode(_depth, i));
 
        }
        return price_closed_form / pow(1 + _interest_rate, _depth);
    }
    else{

        // We create another tree that contains the Option discounted prices
        BinaryTree<double> option_prices = BinaryTree<double> (_depth);
        // Tree that will contain the exercise conditions for american options
        BinaryTree<bool> exercise_tree = BinaryTree<bool>(_depth);

        // For the last time period we only need the payoff
        for(int i = 0; i <= _depth; i++){
            option_prices.setNode(_depth, i, get(_depth, i));
            exercise_tree.setNode(_depth, i, false);
        }
        
        // Now we can discount the option's payoff and get the new price for each node
        double intrinsic_value = 0;
        bool exercise_condition = false;

        for(int i = _depth - 1; i >= 0; i--){
            for(int j = 0; j <= i; j++){

                double continuous_value = (q * option_prices.getNode(i + 1, j + 1) + (1 - q) * option_prices.getNode(i + 1, j)) / (1 + _interest_rate);

                // For American Options
                if (_option->isAmericanOption()) {
					intrinsic_value = this->get(i, j);

					if (intrinsic_value >= continuous_value) {
						option_prices.setNode(i, j, intrinsic_value);
						exercise_condition = true;
						exercise_tree.setNode(i, j, exercise_condition);
					}
					else {
						option_prices.setNode(i, j, continuous_value);
						exercise_tree.setNode(i, j, exercise_condition);
					}
				}
                // For Others
                else
                {
                    option_prices.setNode(i, j, continuous_value);
                }
            }
        }
        return option_prices.getNode(0, 0);
    }
}