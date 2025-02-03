#pragma once

#include <list>
#include "MonteCarlo.hpp"
#include "TimeGrid.hpp"
#include "RebalacingOracle.cpp"
#include "Position.hpp"

class Portfolio {
public:
    MonteCarlo &monteCarlo;
    std::list<Position> positions;
    double cash ;
    RebalancingOracle rebalacingOrcale;

    Portfolio();
    Portfolio(nlohmann::json &jsonParams, MonteCarlo &monteCarlo);
    ~Portfolio();
    void UpdatePortfolio();
    void GetPortfolioValue(int t1 , int t2 , double cash);
    void ComputeValueOfRiskyAssets();

};
