#include "Position.hpp"
#include "json_reader.hpp"
#include <iostream>

Position::Position()
{
    date = 0 ;
    price = 0.0 ;
    priceStdDev = 0.0;
    deltas = pnl_vect_create_from_double(1 , 0.0);
    deltasStdDev = pnl_vect_create_from_double(1 , 0.0);
    portfolioValue = 0.0 ;
    cash = 0.0 ;
}

Position::~Position()
{
    pnl_vect_free(&deltas);
    pnl_vect_free(&deltasStdDev);
}

Position::Position(int date, double price, double priceStdDev, PnlVect *deltas, PnlVect *deltasStdDev, double portfolioValue)
    : date(date), price(price), priceStdDev(priceStdDev), portfolioValue(portfolioValue), deltas(deltas), deltasStdDev(deltasStdDev)
{
}

void to_json(nlohmann::json &j, const Position &position) {
    j["date"] = position.date;
    j["value"] = position.portfolioValue;
    j["price"] = position.price;
    j["priceStdDev"] = position.priceStdDev;
    j["deltas"] = position.deltas;
    j["deltasStdDev"] = position.deltasStdDev;
}

void Position::print() const {
    nlohmann::json j = *this;
    std::cout << j.dump(4);
}


double Position::UpdatePortfolioValue(int t, double r , PnlVect* spots , bool isFirstTime)
{

            
    if(isFirstTime) {
        portfolioValue = price ;
        cash = portfolioValue - ComputeValueOfRiskyAssets(spots); 
        date  = t ;
    } else {
        cash *= exp(r*(t - date));
        portfolioValue = cash + ComputeValueOfRiskyAssets(spots);
        date = t ;
    }
    


}

double Position::ComputeValueOfRiskyAssets(PnlVect *spots)
{
    double res = 0.0 ;

    for (size_t i = 0; i < deltas->size ; i++)
    {
        res += GET(deltas , i)*GET(spots , i);
    }
    

    return res;
}
