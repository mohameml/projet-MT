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

    double SX_T = pnl_mat_get(matrix, matrix->m-1, 0);

    double payoff = std::max(SX_T - strike , 0.0);

    return payoff;
}