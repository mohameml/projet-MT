#ifndef _Risky_Asset_HPP
#define _Risky_Asset_HPP

#include "pnl/pnl_vector.h"
#include "json_reader.hpp"
#include "InterestRateModel.hpp"
#include "RiskyDynamics.hpp"

class  RiskyAsset : public RiskyDynamics {

public : 

    InterestRateModel domesticInterestRate;
    RiskyAsset();
    RiskyAsset(InterestRateModel domesticInterestRate , double realVolatility , PnlVect* volatilityVector , int index);
    ~RiskyAsset();

};


#endif 