#include "RebalacingOracle.hpp"



RebalancingOracle::RebalancingOracle()
{
}

RebalancingOracle::RebalancingOracle(const nlohmann::json json)
{
    this->time_grid = createTimeGridFromJson(json);
}

RebalancingOracle::~RebalancingOracle()
{
}

bool RebalancingOracle::IsRebalancing(int t) 
{
    return this->time_grid.has(t);
}


