#include "CallCurrencyOption.hpp"

CallCurrencyOption::CallCurrencyOption()
{
}

CallCurrencyOption::CallCurrencyOption(const nlohmann::json json): Option(json)
{
    this->strike = json["strike"];
}

CallCurrencyOption::~CallCurrencyOption()
{
}

double CallCurrencyOption::payOff(const PnlMat *matrix)
{   
    double r1 = this->foreignInterestRates[0].rate;
    return pnl_mat_get(matrix, matrix->m-1, 0)*exp(this->maturity * r1) - strike > 0 ? pnl_mat_get(matrix, matrix->m-1, 0)*exp(this->maturity * r1) - strike : 0;
}

