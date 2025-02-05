#ifndef _POSITION_HPP
#define _POSITION_HPP

#include "pnl/pnl_vector.h"
#include "nlohmann/json.hpp"

class Position {
public:
    int date;
    PnlVect *deltas = nullptr;
    PnlVect *deltasStdDev = nullptr;
    double price;
    double priceStdDev;
    double portfolioValue;

    ~Position();
    Position(int date, double price, double priceStdDev, PnlVect* deltas, PnlVect* deltasStdDev, double portfolioValue);
    
    friend void to_json(nlohmann::json &j, const Position &positions);
    void print() const;
    
    double GetValueOfCash(PnlVect* spots);
    double UpdatePortfolioValue(double cash,PnlVect* spots , PnlVect* last_deltas );
    double ComputeValueOfRiskyAssets(PnlVect* spots ,  PnlVect* deltas_);
};


#endif 