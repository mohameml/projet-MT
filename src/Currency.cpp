#include "Currency.hpp"

Currency::Currency()
{
}

Currency::Currency(InterestRateModel domesticInterestRate, InterestRateModel foreignInterestRate, double volatility, PnlVect L_i , int index):RiskyDynamics(0.0 , volatility , L_i , index)
{
    this->domesticInterestRate = domesticInterestRate;
    this->foreignInterestRate = foreignInterestRate;
    this->drift = domesticInterestRate.rate - foreignInterestRate.rate ;
}




Currency::~Currency()
{
}

