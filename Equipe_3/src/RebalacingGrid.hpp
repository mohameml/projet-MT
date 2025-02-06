#ifndef __REBALACING_GRID_HPP
#define __REBALACING_GRID_HPP


#include "RebalacingOracle.hpp"

class RebalacingGrid : public RebalancingOracle {

public :

    RebalacingGrid();
    RebalacingGrid(nlohmann::json json);
    ~RebalacingGrid();
};

#endif 