#include "Hedger.hpp"

Hedger::Hedger()
{
}

Hedger::Hedger(Portfolio hedgingPortfolio, PnlMat *dataHistorique):hedgingPortfolio(hedgingPortfolio),dataHistorique(dataHistorique)
{
}

Hedger::~Hedger()
{
    pnl_mat_free(&dataHistorique);
}


void Hedger::hedge()
{

    MonteCarlo monteCarlo = hedgingPortfolio.monteCarlo;
    int nbDays = monteCarlo.nbDays;

    foreignMarketToDomesticMarket(dataHistorique);

    PnlVect* vect = pnl_vect_create_from_scalar(dataHistorique->n , 0.0);
    pnl_mat_get_row(vect , dataHistorique ,0 );

    PnlMat* past = pnl_mat_create(1 , 1);

    for (int t = 1 ; t <= nbDays ; t++)
    {

        if(monteCarlo.model->monitoringTimeGrid.has(t)) {
            // int index = monteCarlo.model->monitoringTimeGrid.getLastIndex(t);
            pnl_mat_get_row(vect , dataHistorique , t);
            pnl_mat_resize(past , past->m + 1 , past->n );
            pnl_mat_set_row(past , vect  , past->m - 1);
        }


        if(hedgingPortfolio.rebalacingOrcale.IsRebalancing(t)) {
            

            if(!monteCarlo.model->monitoringTimeGrid.has(t)) {
                pnl_mat_get_row(vect , dataHistorique , t);
                pnl_mat_resize(past , past->m + 1 , past->n );
                pnl_mat_set_row(past , vect  , past->m - 1);
            }

            Position postion ;  
            monteCarlo.priceAndDelta(t , past , &postion);
            hedgingPortfolio.positions.push_back(postion);

        }

    }
    
}


void Hedger::foreignMarketToDomesticMarket(PnlMat *Past)
{
    auto assetCurrencyMapping = hedgingPortfolio.monteCarlo.option->assetCurrencyMapping;
    int n0 = assetCurrencyMapping.at(0);
    int nbAsset = hedgingPortfolio.monteCarlo.model->assets.size();

    for (size_t t = 0; t < Past->m ; t++)
    {


        for (size_t i = 1 ; i < assetCurrencyMapping.size(); i++)
        {
            int ni = assetCurrencyMapping.at(i);
            
            for (size_t j = n0 ; j < n0 + ni ; j++)
            {
                int index_xi = nbAsset + i;
                MLET(Past , t , j) *= MGET(Past , t , index_xi); 
            }

            n0+=ni;

        }
        
        
        
    }
    

}