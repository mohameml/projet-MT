#ifndef GridRebalacing_HPP
#define GridRebalacing_HPP

#include "RebalacingOracle.hpp"
#include <nlohmann/json.hpp>

class GridRebalacing : public RebalancingOracle {

public:

    GridRebalacing(nlohmann::json json);

    bool IsRebalancing(int date) const override;

};

#endif // FIXEDREBALACING_HPP