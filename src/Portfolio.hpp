#ifndef __PORTFOLIO_HPP
#define __PORTFOLIO_HPP


#include <list>
#include "MonteCarlo.hpp"
#include "TimeGrid.hpp"
#include "RebalacingOracle.hpp"
#include "Position.hpp"

class Portfolio {
public:
    MonteCarlo &monteCarlo;
    std::list<Position> positions;
    double cash ;
    RebalancingOracle rebalacingOrcale;

    Portfolio(nlohmann::json &jsonParams, MonteCarlo &monteCarlo);
    ~Portfolio();


};


#endif 