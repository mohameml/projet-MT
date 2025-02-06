#ifndef __PORTFOLIO_HPP
#define __PORTFOLIO_HPP


#include <list>
#include "MonteCarlo.hpp"
#include "TimeGrid.hpp"
#include "RebalacingOracle.hpp"
#include "Position.hpp"

class Portfolio {
public:
    std::list<Position*> positions;
    double cashGlobal ;
    int lastTimeUpdate ;
    int numberOfDaysPerYear;
    bool isFirstTime;
    RebalancingOracle rebalacingOrcale;

    Portfolio(nlohmann::json &jsonParams);
    void addPosition(Position* position , int  t , double r ,  PnlVect* spots);
    ~Portfolio();


};


#endif 