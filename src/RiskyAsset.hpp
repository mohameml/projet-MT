#ifndef _Risky_Asset_HPP
#define _Risky_Asset_HPP

#include "pnl/pnl_vector.h"
#include "json_reader.hpp"
#include "InterestRateModel.hpp"
#include "RiskyDynamics.hpp"

class  RiskyAsset : public RiskyDynamics {

public : 


    RiskyAsset();
    RiskyAsset(nlohmann::json json);

};


#endif 