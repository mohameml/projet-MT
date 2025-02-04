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

    // ====== monitoringTimeGrid === 

    monitoringTimeGrid = createTimeGridFromJson(json);
    
    // ==== Correlations and matrice cholesky :  ==== 

    json.at("Correlations").get_to(C);
    model_size = C->n;

    L = pnl_mat_create(model_size , model_size);
    for (int i = 0; i < model_size; i++)
        pnl_mat_set_diag(L, 1.0, i);
    pnl_mat_chol(L);

    // ====== numberOfDaysPerYear ===== 
    numberOfDaysPerYear = json.at("NumberOfDaysInOneYear").get<int>();

    // ===== vecteur of simulation G : ===== 
    G = pnl_vect_create(model_size);

    // ================== Currencies ============== 

    PnlVect* volatilityVector = pnl_vect_create(model_size);

    std::string domesticCurrencyId;
    json.at("DomesticCurrencyId").get_to(domesticCurrencyId);

    int index = 0 ;
    auto jsonCurrencies = json.at("Currencies");
    int assetNb = model_size - jsonCurrencies.size();
    
    for (auto jsonCurrency : jsonCurrencies) {

        std::string currencyId(jsonCurrency.at("id").get<std::string>());
        double rf = jsonCurrency.at("InterestRate").get<double>();
        double realVolatility = jsonCurrency.at("Volatility").get<double>();

        if(currencyId == domesticCurrencyId) {
            this->domesticInterestRate = InterestRateModel(rf , currencyId);
        } else {

            pnl_mat_get_row(volatilityVector , L , assetNb + index);
            pnl_vect_mult_scalar(volatilityVector , realVolatility);
            auto currency = Currency(domesticInterestRate , InterestRateModel(rf , currencyId) , realVolatility , *volatilityVector , assetNb + index);
            currencies.push_back(currency);
            index++;
        }    
    }

    // ================== Assets ============== 

    int index_asset = 0 ;
    auto jsonAssets = json.at("Assets");
    
    for (auto jsonAsset : jsonAssets) {

        std::string currencyId(jsonAsset.at("CurrencyId").get<std::string>());
        double realVolatility = jsonAsset.at("Volatility").get<double>();
        
        Currency currencyOfAsset = getCurrencyById(currencyId); 

        pnl_mat_get_row(volatilityVector , L , index_asset);
        pnl_vect_mult_scalar(volatilityVector , realVolatility);
        pnl_vect_plus_vect(volatilityVector , currencyOfAsset.volatilityVector);

        assets.push_back(RiskyAsset(domesticInterestRate , realVolatility + currencyOfAsset.realVolatility , *volatilityVector , index_asset));

        index_asset++;

    }






    pnl_vect_free(&volatilityVector);


}


Currency GlobalModel::getCurrencyById(std::string id) {
    for (auto curr : currencies)
    {
        if(curr.foreignInterestRate.id == id) {
            return curr;
        }
    }
    
}





void GlobalModel::asset(const PnlMat *past, int t, PnlMat *path, PnlRng *rng)
{

    
    int last_index = monitoringTimeGrid.getLastIndex(t);

    if (last_index == - 1)
    {
        pnl_mat_extract_subblock(path, past, 0, path->m, 0, path->n);
        return;
    }


    pnl_mat_set_subblock(path, past, 0, 0);
    pnl_vect_rng_normal(G, model_size, rng);
    double step = (monitoringTimeGrid.at(last_index + 1) - t)  / (double)numberOfDaysPerYear;; 
    double isMonitoringDate = monitoringTimeGrid.has(t);

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



void GlobalModel::shift_asset(int d, int t, double h, PnlMat *path)
{

    int last_index = monitoringTimeGrid.getLastIndex(t);
    for (int i = last_index + 1; i < path->m; i++)
    {
        MLET(path, i, d) *= h;
    };
}
