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

    int numberOfDaysPerYear = json.at("NumberOfDaysInOneYear").get<int>();

    maturity = json.at("Option").at("MaturityInDays").get<int>() / double (numberOfDaysPerYear);

    std::string domesticCurrencyId;
    json.at("DomesticCurrencyId").get_to(domesticCurrencyId);

    auto jsonCurrencies = json.at("Currencies");
    this->foreignInterestRates.resize(jsonCurrencies.size());
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
    

    auto assets = json.at("Assets");
    int lenght = jsonCurrencies.size();
    this->assetCurrencyMapping.resize(lenght);
    std::map<std::string , int> dit_curr_nb;

    for(auto asset : assets) {
        std::string currencyId(asset.at("id").get<std::string>());
        dit_curr_nb[currencyId]++;
    }

    int index =  0 ;
    for (auto jsonCurrency : jsonCurrencies) {
        assetCurrencyMapping[index] = dit_curr_nb[jsonCurrency];
        index++;
    }

    
}

Option::~Option()
{
}

Option *instance_option(const nlohmann::json json)
{
    Option *opt = NULL;
    string optionType;
    json.at("option type").get_to(optionType);

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
