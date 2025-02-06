#include "RiskyAsset.hpp"

RiskyAsset::RiskyAsset()
{
}

RiskyAsset::RiskyAsset(InterestRateModel domesticInterestRate, double realVolatility, PnlVect* volatilityVector , int index):RiskyDynamics(0.0 , realVolatility , volatilityVector , index)
{
    this->domesticInterestRate = domesticInterestRate;
    this->drift =  domesticInterestRate.rate ;
}



RiskyAsset::~RiskyAsset()
{
}

