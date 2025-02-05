#include "Position.hpp"
#include "json_reader.hpp"
#include <iostream>


Position::~Position()
{
    if(deltas) {

        pnl_vect_free(&deltas);
    }

    if(deltasStdDev) {

        pnl_vect_free(&deltasStdDev);
    }
}

// : date(date), price(price), priceStdDev(priceStdDev), portfolioValue(portfolioValue), deltas(deltas), deltasStdDev(deltasStdDev)
Position::Position(int date, double price, double priceStdDev, PnlVect *deltas, PnlVect *deltasStdDev, double portfolioValue)
{
    this->date = date ;
    this->price = price ;
    this->priceStdDev = priceStdDev;
    this->deltas = pnl_vect_copy(deltas);
    this->deltasStdDev = pnl_vect_copy(deltasStdDev);
    this->portfolioValue = portfolioValue;

}

void to_json(nlohmann::json &j, const Position& position) {


    j["date"] = position.date;
    j["value"] = position.portfolioValue;
    j["price"] = position.price;
    j["priceStdDev"] = position.priceStdDev;
    j["deltas"] = position.deltas;
    j["deltasStdDev"] = position.deltasStdDev;


    // j["date"] = position->date;
    // j["value"] = position->portfolioValue;
    // j["price"] = position->price;
    // j["priceStdDev"] = position->priceStdDev;
    // j["deltas"] = position->deltas;
    // j["deltasStdDev"] = position->deltasStdDev;

}

void Position::print() const {
    nlohmann::json j = *this;
    std::cout << j.dump(4);
}


double Position::UpdatePortfolioValue(double cash , PnlVect* spots , PnlVect* last_deltas )
{

    portfolioValue = cash + ComputeValueOfRiskyAssets(spots , last_deltas);
}


double Position::ComputeValueOfRiskyAssets(PnlVect *spots , PnlVect* deltas_)
{
    double res = 0.0 ;

    for (size_t i = 0; i < deltas_->size ; i++)
    {
        res += GET(deltas_ , i)*GET(spots , i);
    }
    

    return res;
}

double Position::GetValueOfCash(PnlVect *spots)
{
    double cash = portfolioValue - ComputeValueOfRiskyAssets(spots , deltas);

    return cash ;
}
