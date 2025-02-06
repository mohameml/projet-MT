#include "Option.hpp"
#include <iostream>

#include "CallCurrencyOption.hpp"
#include "CallQuantoOption.hpp"
#include "ForeignAsianOption.hpp"
#include "QuantoExchangeOption.hpp"
#include "ForeignPerfBasketOption.hpp"
#include <map>

using namespace std;

Option::Option()
{
}

Option::Option(const nlohmann::json json)
{

    numberOfDaysPerYear = json.at("NumberOfDaysInOneYear").get<int>();

    maturity = json.at("Option").at("MaturityInDays").get<int>() / double (numberOfDaysPerYear);

    std::string domesticCurrencyId;
    json.at("DomesticCurrencyId").get_to(domesticCurrencyId);

    // this->foreignInterestRates.resize(jsonCurrencies.size());
    auto jsonCurrencies = json.at("Currencies");

    for (auto jsonCurrency : jsonCurrencies) {
    
        std::string currencyId(jsonCurrency.at("id").get<std::string>());
        double rf = jsonCurrency.at("InterestRate").get<double>();

        if(currencyId == domesticCurrencyId) {
            this->domesticInterestRate = InterestRateModel(rf , currencyId);
        } else {

            this->foreignInterestRates.push_back(InterestRateModel(rf , currencyId));
        }

    }

    this->monitoringTimeGrid = createTimeGridFromJson(json);
    


    std::map<std::string , int> dit_curr_nbRiskyAsset;
    auto assets = json.at("Assets");
    for(auto asset : assets) {
        std::string currencyId(asset.at("CurrencyId").get<std::string>());
        dit_curr_nbRiskyAsset[currencyId]++;
    }


    assetCurrencyMapping.push_back(dit_curr_nbRiskyAsset[domesticInterestRate.id]);
    for(auto curr : foreignInterestRates) {
        assetCurrencyMapping.push_back(dit_curr_nbRiskyAsset[curr.id]);
    }



    
}

Option::~Option()
{
}

Option *instance_option(const nlohmann::json json)
{
    Option *opt = NULL;
    string optionType  = json.at("Option").at("Type").get<std::string>();

    if (optionType == "call_currency")
        opt = new CallCurrencyOption(json);
    else if (optionType == "call_quanto")
        opt = new CallQuantoOption(json);
    else if (optionType == "foreign_asian")
        opt = new ForeignAsianOption(json);
    else if (optionType == "foreign_perf_basket")
        opt = new ForeignPerfBasketOption(json);
    else if (optionType == "quanto_exchange")
        opt = new QuantoExchangeOption(json);
    else
    {
        cout << "Option " << optionType << " unknow. Abort." << endl;
        abort();
    }

    return opt;
}
