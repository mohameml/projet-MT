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
    return pnl_mat_get(matrix, matrix->m-1, 0)-pnl_mat_get(matrix, matrix->m-1, 1) - strike > 0 ? pnl_mat_get(matrix, matrix->m-1, 0)-pnl_mat_get(matrix, matrix->m-1, 1) - strike : 0;
}

