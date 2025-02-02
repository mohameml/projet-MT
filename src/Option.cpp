#include "Option.hpp"
#include <iostream>

#include "CallCurrencyOption.hpp"
#include "CallQuantoOption.hpp"
#include "ForeignAsianOption.hpp"
#include "QuantoExchangeOption.hpp"
#include "ForeignPerfBasketOption.hpp"

using namespace std;

Option::Option()
{
}

Option::Option(const nlohmann::json json)
{

    json.at("maturity").get_to(maturity);
    json.at("option size").get_to(size);
    json.at("fixing dates number").get_to(dates);
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
