#include "CallCurrencyOption.hpp"

CallCurrencyOption::CallCurrencyOption()
{
}

CallCurrencyOption::CallCurrencyOption(const nlohmann::json json): Option(json)
{
    // this->strike = json["strike"];
    strike = json.at("Option").at("Strike").get<double>();
    
}

CallCurrencyOption::~CallCurrencyOption()
{
}

double CallCurrencyOption::payOff(const PnlMat *matrix)
{   
    
    return pnl_mat_get(matrix, matrix->m-1, 0) - strike > 0 ? pnl_mat_get(matrix, matrix->m-1, 0) - strike : 0;
}

