#include "CallQuantoOption.hpp"
#include "json_reader.hpp"

// Constructor
CallQuantoOption::CallQuantoOption(const nlohmann::json json): Option(json)
{
    json.at("Strike").get_to(strike);

}

// Method to calculate the payoff
double CallQuantoOption::payOff(const PnlMat *matrix){
    return pnl_mat_get(matrix, matrix->m-1, 0) - strike > 0 ? pnl_mat_get(matrix, matrix->m-1, 0) - strike : 0;
}