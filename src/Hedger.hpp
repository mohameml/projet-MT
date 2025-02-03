#ifndef __HEDGER__HPP
#define __HEDGER__HPP


#include "Portfolio.hpp"

class Hedger {

public :

    Portfolio hedgingPortfolio;
    PnlMat* dataHistorique ;

    Hedger();
    Hedger(Portfolio hedgingPortfolio , PnlMat* dataHistorique);
    ~Hedger();

    void hedge();
    void foreignMarketToDomesticMarket(PnlMat* Past);


};


#endif