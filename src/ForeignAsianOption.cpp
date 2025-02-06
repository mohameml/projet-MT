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
    
    int N = matrix->m;

    double sum = 0.0 ;

    for (size_t j = 0 ; j < N ; j++)
    {
        sum += MGET(matrix , j , 1);
    }
    sum /= (double)N ;
    
    

    double S0_T = MGET(matrix, N - 1 ,0);

    double payOff = std::max(sum - S0_T , 0.0);

    return payOff;
}
