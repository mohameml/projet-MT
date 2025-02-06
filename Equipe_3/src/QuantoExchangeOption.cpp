#include "QuantoExchangeOption.hpp"

QuantoExchangeOption::QuantoExchangeOption()
{
}

QuantoExchangeOption::QuantoExchangeOption(const nlohmann::json json):Option(json)
{
    // this->strike = json["strike"];
    strike = json.at("Option").at("Strike").get<double>();
}

QuantoExchangeOption::~QuantoExchangeOption()
{
}

double QuantoExchangeOption::payOff(const PnlMat *matrix)
{   
    double S0_T = pnl_mat_get(matrix, matrix->m-1, 0); 
    double SX_T = pnl_mat_get(matrix, matrix->m-1, 1);

    double payOff = std::max(S0_T - SX_T - strike , 0.0);

    return payOff;
}

