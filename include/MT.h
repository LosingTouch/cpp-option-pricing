#pragma once
#include <random>

class MT{

private: 
    std::mt19937 _Gen;
    static std::uniform_real_distribution<double> _uniformDist;
    static std::normal_distribution<double> _normalDist;
    // Constructor in private 
    MT();

public:
    static double rand_unif();
    static double rand_norm();

    // Delete copy and assignement
    MT(const MT&) = delete; 
    MT& operator=(const MT&) = delete;
    static MT& getInstance(); 
};