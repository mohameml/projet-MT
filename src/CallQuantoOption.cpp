#include "CallQuantoOption.hpp"
#include "json_reader.hpp"

// Constructor
CallQuantoOption::CallQuantoOption(const nlohmann::json json): Option(json)
{
    // json.at("Strike").get_to(strike);
    strike = json.at("Option").at("Strike").get<double>();

}

// Method to calculate the payoff
double CallQuantoOption::payOff(const PnlMat *matrix){
    double r1 = this->foreignInterestRates[0].rate;
    return pnl_mat_get(matrix, matrix->m-1, 0)*exp(-this->maturity * r1) - strike > 0 ? pnl_mat_get(matrix, matrix->m-1, 0)*exp(-this->maturity * r1) - strike : 0;
}