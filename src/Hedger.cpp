#include "Hedger.hpp"


Hedger::Hedger(Portfolio hedgingPortfolio):hedgingPortfolio(hedgingPortfolio)
{
}

Hedger::~Hedger()
{
}


void Hedger::hedge(PnlMat* dataHistorique)
{

    MonteCarlo monteCarlo = hedgingPortfolio.monteCarlo;
    int nbDays = monteCarlo.nbDays;

    foreignMarketToDomesticMarket(dataHistorique);

    PnlVect* spots = pnl_vect_create_from_scalar(dataHistorique->n , 0.0);
    pnl_mat_get_row(spots , dataHistorique ,0 );

    PnlMat* past = pnl_mat_create(1 , 1);
    double r = monteCarlo.model->domesticInterestRate.rate ;
    bool isFirstTime = true ;


    // for (int t : monteCarlo.model->monitoringTimeGrid.getAllDates())
    // {
    //     /* code */
    // }
    

    for (int t = 1 ; t <= nbDays ; t++)
    {
        

        if(monteCarlo.model->monitoringTimeGrid.has(t)) {
            pnl_mat_get_row(spots , dataHistorique , t);
            pnl_mat_resize(past , past->m + 1 , past->n );
            pnl_mat_set_row(past , spots  , past->m - 1);
        }


        if(hedgingPortfolio.rebalacingOrcale.IsRebalancing(t)) {
            

            pnl_mat_get_row(spots , dataHistorique , t);

            if(!monteCarlo.model->monitoringTimeGrid.has(t)) {
                pnl_mat_resize(past , past->m + 1 , past->n );
                pnl_mat_set_row(past , spots  , past->m - 1);
            }

            Position position ;  
            // double t_ = (double)t / (double)nbDays;
            monteCarlo.priceAndDelta(t , past , &position);
            
            
            position.UpdatePortfolioValue(t , r ,spots , isFirstTime);


            hedgingPortfolio.positions.push_back(position);
            isFirstTime = false ;


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