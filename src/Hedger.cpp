#include "Hedger.hpp"



Hedger::Hedger(nlohmann::json json)
{
    monteCarlo = new MonteCarlo(json);
    hedgingPortfolio = new Portfolio(json);
}

Hedger::~Hedger()
{
    delete monteCarlo;
    delete hedgingPortfolio;
}


void Hedger::hedge(PnlMat* dataHistorique)
{


    int nbDays = monteCarlo->nbDays;

    foreignMarketToDomesticMarket(dataHistorique);

    PnlVect* spots = pnl_vect_create_from_scalar(dataHistorique->n , 0.0);
    pnl_mat_get_row(spots , dataHistorique ,0 );

    PnlMat* past = pnl_mat_create(1 , 1);
    pnl_mat_set_row(past , spots  , 0);

    double r = monteCarlo->model->domesticInterestRate.rate ;
    bool isFirstTime = true ;



    double price = 0.0 ;
    double price_std = 0.0 ;
    PnlVect *deltas = pnl_vect_create_from_zero(monteCarlo->model_size);
    PnlVect *deltas_std_dev = pnl_vect_create_from_zero(monteCarlo->model_size);


    for (int t = 1 ; t <= 2 ; t++)
    {
        

        // if(monteCarlo.model->monitoringTimeGrid.has(t)) {
        //     pnl_mat_get_row(spots , dataHistorique , t);
        //     // pnl_mat_resize(past , past->m + 1 , past->n );
        //     pnl_mat_set_row(past , spots  , past->m - 1);
        // }

        if(hedgingPortfolio->rebalacingOrcale.IsRebalancing(t)) {
            


            if(!monteCarlo->model->monitoringTimeGrid.has(t) && monteCarlo->model->monitoringTimeGrid.has(t - 1)) { // 0 est une data de constattion  t_0 = 0 
                pnl_mat_resize(past , past->m + 1 , past->n );
                // pnl_mat_set_row(past , spots  , past->m - 1);
            }

            pnl_mat_get_row(spots , dataHistorique , t);
            pnl_mat_set_row(past , spots  , past->m - 1);

            
            
            monteCarlo->priceAndDelta(t , past , price , price_std  , deltas , deltas_std_dev);


            Position* position = new Position(t , price , price_std , deltas , deltas_std_dev , 0.0); 


            position->UpdatePortfolioValue(t , r ,spots , isFirstTime);


            hedgingPortfolio->positions.push_back(position);
            isFirstTime = false ;


        }

    }


    pnl_vect_free(&spots);
    pnl_vect_free(&deltas);
    pnl_vect_free(&deltas_std_dev);
    
}


void Hedger::foreignMarketToDomesticMarket(PnlMat *Past)
{
    auto assetCurrencyMapping = monteCarlo->option->assetCurrencyMapping;
    int n0 = assetCurrencyMapping.at(0);
    int nbAsset = monteCarlo->model->assets.size();

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