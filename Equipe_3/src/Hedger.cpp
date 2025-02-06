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

    PnlMat* past = pnl_mat_create(1 , dataHistorique->n);
    pnl_mat_set_row(past , spots  , 0);



    double price = 0.0 ;
    double price_std = 0.0 ;
    PnlVect *deltas = pnl_vect_create_from_zero(monteCarlo->model_size);
    PnlVect *deltas_std_dev = pnl_vect_create_from_zero(monteCarlo->model_size);

    double r = monteCarlo->model->domesticInterestRate.rate ;

    for (int t = 0 ; t <= nbDays ; t++)
    {

        if(hedgingPortfolio->rebalacingOrcale.IsRebalancing(t)) {
            

            if(!monteCarlo->model->monitoringTimeGrid.has(t) && monteCarlo->model->monitoringTimeGrid.has(t - 1)) { 
                PnlMat* mat_clone = pnl_mat_create(past->m , past->n);
                pnl_mat_clone(mat_clone , past);
                pnl_mat_resize(past , past->m + 1 , past->n );
                pnl_mat_set_subblock(past , mat_clone , 0 , 0);
                pnl_mat_free(&mat_clone);
            }

            pnl_mat_get_row(spots , dataHistorique , t);
            pnl_mat_set_row(past , spots  , past->m - 1);

            monteCarlo->priceAndDelta(t , past , price , price_std  , deltas , deltas_std_dev);

            Position* position = new Position(t , price , price_std , deltas , deltas_std_dev ,price);
            hedgingPortfolio->addPosition(position , t , r , spots);

        }
    }

    pnl_mat_free(&past);
    pnl_vect_free(&spots);
    pnl_vect_free(&deltas);
    pnl_vect_free(&deltas_std_dev);
    
}


void Hedger::foreignMarketToDomesticMarket(PnlMat *Past)
{
    auto assetCurrencyMapping = monteCarlo->option->assetCurrencyMapping;
    int n0 = assetCurrencyMapping.at(0);
    int nbAsset = monteCarlo->model->assets.size();

    int index = n0 ;

    for (size_t t = 0; t < Past->m ; t++)
    {


        for (size_t i = 1 ; i < assetCurrencyMapping.size(); i++)
        {
            int ni = assetCurrencyMapping.at(i);
            int index_xi = nbAsset + i - 1;
            
            for (size_t j = index ; j < index + ni ; j++)
            {
                MLET(Past , t , j) = MGET(Past , t , j)*MGET(Past , t , index_xi); 
            }

            index+=ni;

        }
        index = n0 ;


        for (size_t j = 0; j < monteCarlo->model->currencies.size(); j++)
        {
            double t_ = (double) t / (double) monteCarlo->numberOfDaysPerYear;
            double rf = monteCarlo->option->foreignInterestRates.at(j).rate;
            MLET(Past , t , nbAsset + j) = MLET(Past , t , nbAsset + j)*std::exp(rf*t_);
        }
        
        
        
        
    }
    

}