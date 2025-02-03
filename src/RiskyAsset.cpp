#include "RiskyAsset.hpp"

RiskyAsset::RiskyAsset()
{
}

RiskyAsset::RiskyAsset(InterestRateModel domesticInterestRate, double realVolatility, PnlVect L_i , int index):RiskyDynamics(0.0 , realVolatility , L_i , index)
{
    this->domesticInterestRate = domesticInterestRate;
    this->drift =  domesticInterestRate.rate ;
}



RiskyAsset::~RiskyAsset()
{
}

