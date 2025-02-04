#ifndef REBALANCING_ORACLE_HPP
#define REBALANCING_ORACLE_HPP

#include "TimeGrid.hpp"

class RebalancingOracle {

public:
    TimeGrid time_grid;
    RebalancingOracle();
    RebalancingOracle(const nlohmann::json json);
    ~RebalancingOracle() ;
    bool IsRebalancing(int date) ;

};




#endif 