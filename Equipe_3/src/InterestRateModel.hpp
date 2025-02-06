#ifndef _Interest_RateModel_HPP
#define _Interest_RateModel_HPP
#include <iostream>
#include <nlohmann/json.hpp>

class InterestRateModel {

public :
    double rate ; 
    std::string id ;

    InterestRateModel();
    InterestRateModel(double r , std::string id);
    ~InterestRateModel();


    double discount(double t1 , double t2);
    double account(double t1 , double t2);

};


#endif