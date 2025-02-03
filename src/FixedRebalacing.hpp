#ifndef FIXEDREBALACING_HPP
#define FIXEDREBALACING_HPP

#include "RebalacingOracle.hpp"
#include <nlohmann/json.hpp>

class FixedRebalacing : public RebalancingOracle {

public:
    
    FixedRebalacing(nlohmann::json json);
    bool IsRebalancing(int date) const override;

};

#endif /