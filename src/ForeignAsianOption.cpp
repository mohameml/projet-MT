#include "ForeignAsianOption.hpp"
#include "pnl/pnl_vector.h"
// Constructor
ForeignAsianOption::ForeignAsianOption(const nlohmann::json json): Option(json) 
{
}

// Destructor
ForeignAsianOption::~ForeignAsianOption(){}

// Method to calculate the payoff
double ForeignAsianOption::payOff(const PnlMat *matrix) {
    
    int N = matrix->m - 1;

    double sum = 0.0 ;

    for (size_t i = 1 ; i <= N ; i++)
    {
        sum += MGET(matrix , i , 1);
    }
    sum /= N ;
    
    

    double S0_T = pnl_mat_get(matrix, N ,0);

    double payOff = std::max(sum - S0_T , 0.0);

    return payOff;
}
