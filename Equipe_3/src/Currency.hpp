#ifndef _Currency_HPP
#define _Currency_HPP

#include "json_reader.hpp"
#include "InterestRateModel.hpp"
#include "RiskyDynamics.hpp"

class  Currency : public RiskyDynamics {

public : 
    InterestRateModel domesticInterestRate;
    InterestRateModel foreignInterestRate;
    Currency();
    Currency(InterestRateModel domesticInterestRate , InterestRateModel foreignInterestRate , double volatility , PnlVect* volatilityVector , int index);
    ~Currency();


};


#endif 