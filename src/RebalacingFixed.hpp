#ifndef _REBALACING_FIXED_HPP
#define _REBALACING_FIXED_HPP


#include "RebalacingOracle.hpp"

class RebalacingFixed : public RebalancingOracle {

public :

    RebalacingFixed();
    RebalacingFixed(nlohmann::json json);
    ~RebalacingFixed();
    

};


#endif 