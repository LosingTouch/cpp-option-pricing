// Méthode Optimisée, variable antithétiques 
#include "BlackScholesMCPricer.h"
#include "MT.h"
#include <cmath>
#include <vector>

// Constructor
BlackScholesMCPricer::BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility) :
    _option(option), _initial_price(initial_price), _interest_rate(interest_rate), _volatility(volatility), _nb_paths(0), _current_price_estimate(0.0), _sum_payoff(0.0), _squared_payoff(0.0) {}

// Destructor
BlackScholesMCPricer::~BlackScholesMCPricer() {}

// Getter Method for _nb_paths
int BlackScholesMCPricer::getNbPaths() const {
    return _nb_paths;
}

// Method to generate new paths with Variance Reduction
void BlackScholesMCPricer::generate(int nb_paths) {
    double m = _option->isAsianOption() ? _option->GetTimeSteps().size() : 1;
    double expiry = _option->getExpiry();
    double dt = expiry / m;
    double drift = (_interest_rate - 0.5 * _volatility * _volatility) * dt;
    double diffusion = _volatility * std::sqrt(dt);

    for (int i = 0; i < nb_paths ; ++i) { 
        std::vector<double> spot_prices(m + 1, _initial_price);
        std::vector<double> antithetic_prices(m + 1, _initial_price);

        for (int j = 1; j <= m; ++j) {
            double normal = MT::rand_norm(); // Generate random normal number
            double antithetic_normal = -normal;

            // Calculate paths
            spot_prices[j] = spot_prices[j - 1] * std::exp(drift + diffusion * normal);
            antithetic_prices[j] = antithetic_prices[j - 1] * std::exp(drift + diffusion * antithetic_normal);
        }

        // Calculate payoffs
        double payoff = _option->payoffPath(spot_prices);
        double antithetic_payoff = _option->payoffPath(antithetic_prices);

        // Discounted payoffs
        double discounted_payoff = std::exp(-_interest_rate * expiry) * payoff;
        double discounted_antithetic_payoff = std::exp(-_interest_rate * expiry) * antithetic_payoff;

        // Update sums
        _sum_payoff += (discounted_payoff + discounted_antithetic_payoff) / 2.0;
        _squared_payoff += (discounted_payoff * discounted_payoff + discounted_antithetic_payoff * discounted_antithetic_payoff) / 2.0;

        // Update the current price estimate
        _current_price_estimate = (_nb_paths * _current_price_estimate + discounted_payoff + discounted_antithetic_payoff) / (_nb_paths + 2);
        _nb_paths += 2;
    }
}

// Method to get the current estimation of the Option Price
double BlackScholesMCPricer::operator()() const {
    if (_current_price_estimate == -1) {
        throw std::invalid_argument("Error: The current estimate is undefined.");
    }
    else {
        return _current_price_estimate;
    }
}

// Confidence Interval Method with Reduced Variance
std::vector<double> BlackScholesMCPricer::confidenceInterval() const {
    double mean = _sum_payoff / _nb_paths;
    double variance = (_squared_payoff / _nb_paths) - (mean * mean);
    double standard_error = std::sqrt(variance / _nb_paths);
    return { mean - 1.96 * standard_error, mean + 1.96 * standard_error };
}


// Méthode Classique
/*
#include "BlackScholesMCPricer.h"
#include "MT.h"

// Constructor
BlackScholesMCPricer::BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility) : 
_option(option), _initial_price(initial_price), _interest_rate(interest_rate), _volatility(volatility), _nb_paths(0), _current_price_estimate(0.0), _sum_payoff(0.0), _squared_payoff(0.0){}

// Destructor
BlackScholesMCPricer::~BlackScholesMCPricer(){}

// Getter Method for _nb_paths
int BlackScholesMCPricer::getNbPaths() const{
    return _nb_paths;
}

// Method to generate new paths
void BlackScholesMCPricer::generate(int nb_paths) {
    double m = _option->isAsianOption() ? _option->GetTimeSteps().size() : 1;
    
    double expiry = _option->getExpiry();
    double dt = expiry / m;

    //std::vector<double> spot_prices(m + 1, _initial_price);
    
    for (int i = 0; i < nb_paths; i++) {
        std::vector<double> spot_prices(m + 1, _initial_price);
        
        //spot_prices[0] = _initial_price;

        for (int j = 1; j <= m; ++j) {
            double normal = MT::rand_norm(); // Generate a random normal number
            spot_prices[j] = spot_prices[j - 1] * std::exp(((_interest_rate - 0.5 * _volatility * _volatility) * dt) + (_volatility * std::sqrt(dt) * normal));
        }

        double payoff = _option->payoffPath(spot_prices);
        double discounted_payoff = std::exp(-_interest_rate * expiry) * payoff; // Actualized payoff

        _sum_payoff += discounted_payoff;
        _squared_payoff += discounted_payoff * discounted_payoff;

        _current_price_estimate = (_nb_paths * _current_price_estimate + discounted_payoff) / (_nb_paths + 1);
        _nb_paths++;
    }
}


// Method to get the currrent estimation of the Option Price
double BlackScholesMCPricer::operator()() const{
    if (_current_price_estimate == -1){
        throw std::invalid_argument("Error : The current estimate is undefined.");
    }
	else{
		return _current_price_estimate;
    }
}

// Method to get the Confidence Interval
std::vector<double> BlackScholesMCPricer::confidenceInterval() const {
    double mean = _sum_payoff / _nb_paths;
    double variance = (_squared_payoff / _nb_paths) - (mean * mean);
    double standard_error = std::sqrt(variance / _nb_paths);
    return {mean - 1.96 * standard_error, mean + 1.96 * standard_error};
}
*/