#include "GlobalModel.hpp"

GlobalModel::GlobalModel()
{
}

GlobalModel::~GlobalModel()
{
    pnl_vect_free(&G);
    pnl_mat_free(&C);
    pnl_mat_free(&L);
}


GlobalModel::GlobalModel(const nlohmann::json json)
{

    PnlVect* volatilityVector = pnl_vect_create(L->n);


    std::string domesticCurrencyId;
    json.at("DomesticCurrencyId").get_to(domesticCurrencyId);

    auto jsonAssets = json.at("Assets");
    int assetNb = jsonAssets.size();
    
    int index = 0 ;
    auto jsonCurrencies = json.at("Currencies");
    
    for (auto jsonCurrency : jsonCurrencies) {

        std::string currencyId(jsonCurrency.at("id").get<std::string>());
        double rf = jsonCurrency.at("InterestRate").get<double>();
        double realVolatility = jsonCurrency.at("Volatility").get<double>();

        if(currencyId == domesticCurrencyId) {
            this->domesticInterestRate = InterestRateModel(rf , currencyId);
        } else {


            pnl_mat_get_row(L , volatilityVector , assetNb + index);
            pnl_vect_mult_scalar(volatilityVector , realVolatility);
            auto currency = Currency(this->domesticInterestRate , InterestRateModel(rf , currencyId) , realVolatility , volatilityVector , assetNb + index);
            currencies.push_back(currency);
            index++;
        }    
    }

    int index_asset = 0 ;
    
    for (auto jsonAsset : jsonAssets) {

        std::string currencyId(jsonAsset.at("CurrencyId").get<std::string>());
        double realVolatility = jsonAsset.at("Volatility").get<double>();
        
        int index_xi = assetNb + index_asset ;
        PnlVect* sigmaVectorXi = currencies.at(index_xi).volatilityVector; 

    
        pnl_vect_get_row(L , volatilityVector , index_asset);
        pnl_vect_mult_scalar(volatilityVector , realVolatility);

        pnl_vect_plus_vect(volatilityVector , sigmaVectorXi);
        assets.push_back(RiskyAsset(domesticInterestRate , realVolatility + volatilityOfXi , volatilityVector , index_asset));

        index_asset++;

    }


    monitoringTimeGrid = createTimeGridFromJson(json);

    model_size = assets.size() + currencies.size();

    numberOfDaysPerYear = json.at("NumberOfDaysInOneYear").get<int>();

    json.at("Correlations").get_to(C);
    L = pnl_mat_create(model_size , model_size);
    for (int i = 0; i < model_size; i++)
        pnl_mat_set_diag(L, 1.0, i);
    pnl_mat_chol(L);

    G = pnl_vect_create(model_size);


    pnl_vect_free(&volatilityVector);


}



void GlobalModel::asset(const PnlMat *past, double t, double T, PnlMat *path, PnlRng *rng)
{

    
    int last_index = monitoringTimeGrid.getLastIndex(t);
    double isMonitoringDate = monitoringTimeGrid.has(t);

    
    if (last_index == - 1)
    {
        pnl_mat_extract_subblock(path, past, 0, path->m, 0, path->n);
        return;
    }



    pnl_mat_set_subblock(path, past, 0, 0);

    pnl_vect_rng_normal(G, model_size, rng);
    double step = monitoringTimeGrid.at(last_index + 1) - t ; 
    for (auto risky_asset : assets)
    {
        risky_asset.sampleNextDate(path , step , G , last_index + 1 , isMonitoringDate);
    }

    for (auto currency : currencies)
    {
        currency.sampleNextDate(path , step , G , last_index + 1 , isMonitoringDate);
    }



    for (size_t i = last_index + 2; i < monitoringTimeGrid.len() ; i++)
    {

        step = (monitoringTimeGrid.at(i)  - monitoringTimeGrid.at(i - 1)) / (double)numberOfDaysPerYear;
        pnl_vect_rng_normal(G, model_size, rng);

        for (auto risky_asset : assets)
        {
            risky_asset.sampleNextDate(path , step , G , i);
        }

        for (auto currency : currencies)
        {
            currency.sampleNextDate(path , step , G , i);
        }

    }

}



void GlobalModel::shift_asset(int d, double t, double h, PnlMat *path)
{

    int last_index = monitoringTimeGrid.getLastIndex(t);
    for (int i = last_index + 1; i < path->m; i++)
    {
        MLET(path, i, d) *= h;
    };
}
