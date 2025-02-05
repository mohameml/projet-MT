#ifndef __HEDGER__HPP
#define __HEDGER__HPP


#include "Portfolio.hpp"

class Hedger {

public :

    Portfolio& hedgingPortfolio;

    Hedger(Portfolio& hedgingPortfolio);
    ~Hedger();

    void hedge(PnlMat* dataHistorique);
    void foreignMarketToDomesticMarket(PnlMat* Past);


};


#endif