#ifndef __HEDGER__HPP
#define __HEDGER__HPP


#include "Portfolio.hpp"
#include "MonteCarlo.hpp"


class Hedger {

public :

    Portfolio* hedgingPortfolio;
    MonteCarlo* monteCarlo;


    Hedger(nlohmann::json json);
    ~Hedger();

    void hedge(PnlMat* dataHistorique);
    void foreignMarketToDomesticMarket(PnlMat* Past);


};


#endif