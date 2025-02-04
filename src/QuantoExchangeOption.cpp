#include "QuantoExchangeOption.hpp"

QuantoExchangeOption::QuantoExchangeOption()
{
}

QuantoExchangeOption::QuantoExchangeOption(const nlohmann::json json)
{
    this->strike = json["strike"];
}

QuantoExchangeOption::~QuantoExchangeOption()
{
}

double QuantoExchangeOption::payOff(const PnlMat *matrix)
{   
    double r1 = this->foreignInterestRates[0].rate;
    return pnl_mat_get(matrix, matrix->m-1, 0)-pnl_mat_get(matrix, matrix->m-1, 1)*exp(-this->maturity * r1) - strike > 0 ? pnl_mat_get(matrix, matrix->m-1, 0)-pnl_mat_get(matrix, matrix->m-1, 1)*exp(-this->maturity * r1) - strike : 0;
}

