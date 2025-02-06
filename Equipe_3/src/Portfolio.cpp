#include <iostream>
#include "Portfolio.hpp"
#include "json_reader.hpp"



Portfolio::Portfolio(nlohmann::json &jsonParams)
{
    rebalacingOrcale = createRebalancingOracleFromJson(jsonParams);
    numberOfDaysPerYear = jsonParams.at("NumberOfDaysInOneYear").get<int>();
    cashGlobal = 0.0 ;
    lastTimeUpdate = 0 ;
    isFirstTime = true ;

}


void Portfolio::addPosition(Position *position, int t, double r , PnlVect* spots)
{
    if(isFirstTime) {
        isFirstTime = false ;
        cashGlobal = position->GetValueOfCash(spots);
        lastTimeUpdate = t ;
    } else {
        
        double step = ((double)t - (double)lastTimeUpdate)/ (double) numberOfDaysPerYear;
        double cash = cashGlobal*exp(r*step);
        
        PnlVect* last_deltas = positions.back()->deltas;
        position->UpdatePortfolioValue(cash , spots , last_deltas);
        
        cashGlobal = position->GetValueOfCash(spots);
        lastTimeUpdate = t ;
        
    }


    positions.push_back(position);
}

Portfolio::~Portfolio()
{
    for (Position* pos : positions) {
        delete pos;  
        pos = nullptr;
    }
    positions.clear();  

}
