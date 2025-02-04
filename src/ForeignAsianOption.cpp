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
    int N = matrix->m ;
    PnlVect *col = pnl_vect_create(N);
    pnl_mat_get_col(col,matrix, 1);

    double r1 = this->foreignInterestRates[0].rate;


    double sum = pnl_vect_sum(col) * exp(-this->maturity * r1); 

    pnl_vect_free(&col);

    return sum/N -pnl_mat_get(matrix,N,0) >0 ? sum/N -pnl_mat_get(matrix,N,0) : 0;
}
