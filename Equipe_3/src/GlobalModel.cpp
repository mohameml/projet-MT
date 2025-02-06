#include "GlobalModel.hpp"

GlobalModel::GlobalModel()
{
}

GlobalModel::~GlobalModel()
{
    pnl_vect_free(&G);
    pnl_mat_free(&L);
}


GlobalModel::GlobalModel(const nlohmann::json json)
{

    // ====== monitoringTimeGrid === 

    monitoringTimeGrid = createTimeGridFromJson(json);
    
    // ==== Correlations and matrice cholesky :  ==== 

    json.at("Correlations").get_to(L);
    pnl_mat_chol(L);

    model_size = L->n;
    
    // pnl_mat_print(C);

    // L = pnl_mat_create(model_size , model_size);
    // for (int i = 0; i < model_size; i++)
    //     pnl_mat_set_diag(L, 1.0, i);
    
    // pnl_mat_print(L);
    // pnl_mat_print(L);

    // ====== numberOfDaysPerYear ===== 
    numberOfDaysPerYear = json.at("NumberOfDaysInOneYear").get<int>();

    // ===== vecteur of simulation G : ===== 
    G = pnl_vect_create_from_double(model_size , 0.0);

    // ================== Currencies ============== 

    PnlVect* volatilityVector = pnl_vect_create_from_double(model_size , 0.0);

    std::string domesticCurrencyId;
    json.at("DomesticCurrencyId").get_to(domesticCurrencyId);

    int index = 0 ;
    auto jsonCurrencies = json.at("Currencies");
    int assetNb = model_size - (jsonCurrencies.size() - 1);
    
    for (auto jsonCurrency : jsonCurrencies) {

        std::string currencyId(jsonCurrency.at("id").get<std::string>());
        double rf = jsonCurrency.at("InterestRate").get<double>();
        double realVolatility = jsonCurrency.at("Volatility").get<double>();

        if(currencyId == domesticCurrencyId) {
            this->domesticInterestRate = InterestRateModel(rf , currencyId);
        } else {

            pnl_mat_get_row(volatilityVector , L , assetNb + index);
            pnl_vect_mult_scalar(volatilityVector , realVolatility);
        
            currencies.push_back(std::make_unique<Currency>(domesticInterestRate , InterestRateModel(rf , currencyId) , realVolatility , volatilityVector , assetNb + index));
        
            index++;
        }    
    }

    // ================== Assets ============== 

    int index_asset = 0 ;
    auto jsonAssets = json.at("Assets");
    
    for (auto jsonAsset : jsonAssets) {

        std::string currencyId(jsonAsset.at("CurrencyId").get<std::string>());
        double realVolatility = jsonAsset.at("Volatility").get<double>();
        
        if(currencyId == domesticCurrencyId) {
            pnl_mat_get_row(volatilityVector , L , index_asset);
            pnl_vect_mult_scalar(volatilityVector , realVolatility);
            assets.push_back(std::make_unique<RiskyAsset>(domesticInterestRate , realVolatility , volatilityVector , index_asset));

        } else {

            Currency* currencyOfAsset = getCurrencyById(currencyId); 

            pnl_mat_get_row(volatilityVector , L , index_asset);
            pnl_vect_mult_scalar(volatilityVector , realVolatility);
            pnl_vect_plus_vect(volatilityVector , currencyOfAsset->volatilityVector);

            double real_vol = pnl_vect_norm_two(volatilityVector);

            assets.push_back(std::make_unique<RiskyAsset>(domesticInterestRate , real_vol, volatilityVector , index_asset));
        }




        index_asset++;

    }






    pnl_vect_free(&volatilityVector);


}


Currency* GlobalModel::getCurrencyById(std::string id) {
    for (const auto& curr : currencies)
    {
        if(curr->foreignInterestRate.id == id) {
            return curr.get();
        }
    }

    return nullptr;
    
}





void GlobalModel::asset(const PnlMat *past, int t, PnlMat *path, PnlRng *rng)
{

    
    int last_index = monitoringTimeGrid.getLastIndex(t);

    if (last_index ==  monitoringTimeGrid.len() - 1)
    {
        pnl_mat_extract_subblock(path, past, 0, path->m, 0, path->n);
        return;
    }


    pnl_mat_set_subblock(path, past, 0, 0);
    pnl_vect_rng_normal(G, model_size, rng);
    double step = (monitoringTimeGrid.at(last_index + 1) - t)  / (double)numberOfDaysPerYear ;
    bool isMonitoringDate = monitoringTimeGrid.has(t);

    for (const auto& risky_asset : assets)
    {
        risky_asset->sampleNextDate(path , step , G , last_index + 1 , isMonitoringDate);
    }

    for (const auto& currency : currencies)
    {
        currency->sampleNextDate(path , step , G , last_index + 1 , isMonitoringDate);
    }



    for (size_t i = last_index + 2; i < monitoringTimeGrid.len() ; i++)
    {

        step = (monitoringTimeGrid.at(i)  - monitoringTimeGrid.at(i - 1)) / (double)numberOfDaysPerYear;
        pnl_vect_rng_normal(G, model_size, rng);

        for (const auto& risky_asset : assets)
        {
            risky_asset->sampleNextDate(path , step , G , i);
        }

        for (const auto& currency : currencies)
        {
            currency->sampleNextDate(path , step , G , i);
        }

    }

}



void GlobalModel::shift_asset(int d, int t, double h, PnlMat *path)
{

    int last_index;
    
    if(monitoringTimeGrid.has(t)) {
        last_index = monitoringTimeGrid.getLastIndex(t);
    } else {
        last_index = monitoringTimeGrid.getLastIndex(t) + 1 ;
    }

    
    for (int i = last_index ; i < path->m; i++)
    {
        MLET(path, i, d) *= h;
    };
}
