#include    "ForeignPerfBasketOption.hpp"
#include    "pnl/pnl_vector.h"

ForeignPerfBasketOption::ForeignPerfBasketOption(const nlohmann::json json) : Option(json) {
    // this->strike = 0;
    strike = json.at("Option").at("Strike").get<double>();
}

ForeignPerfBasketOption::~ForeignPerfBasketOption()
{
}

double ForeignPerfBasketOption::payOff(const PnlMat *matrix)
{
    int nbAsset = 0;
    for(int j = 0; j < assetCurrencyMapping.size(); j++)
    {
        nbAsset += assetCurrencyMapping.at(j);
    }



    int n0 = assetCurrencyMapping.at(0);
    int imax =0;

    int t1 = matrix->m-3;
    int t2 = matrix->m-2;
    int t3 = matrix->m-1;

    double performance =0;
    for (size_t i = 1 ; i < assetCurrencyMapping.size(); i++)
    {
        int ni = assetCurrencyMapping.at(i);
        double sum2 = 0;
        double sum1 = 0; 
        for (size_t j = n0 ; j < n0 + ni ; j++)
        {
            int index_xi = nbAsset + i;
            double si_t1 = MGET(matrix , t1 , j) /MGET(matrix , t1 , index_xi);
            double si_t2 = MGET(matrix , t2 , j) /MGET(matrix , t2 , index_xi); 

            sum1 += si_t1;
            sum2 += si_t2;
        }

        double ri = foreignInterestRates.at(i).rate;
        sum1 *= exp(-ri * t1);
        sum2 *= exp(-ri * t2);
        double perf = sum2/sum1;
        if(perf >= performance)
        {
            performance = perf;
            imax = i;
        }

        n0+=ni;

    }


    PnlVect spot = pnl_vect_wrap_mat_row(matrix, t3);



    // calcul de payOff1
    double payOff1 = 0;

    int index_deb = 0;
    for(int j = 0; j < imax; j++)
    {
        index_deb += assetCurrencyMapping.at(j);
    }

    for(int i = 0; i < assetCurrencyMapping.at(imax); i++)
    {
        double r = foreignInterestRates.at(imax).rate;
        payOff1 += GET(&spot, index_deb + imax + i)*exp(-r*t3);
    }

    payOff1 = payOff1 / assetCurrencyMapping.at(imax);



    // calcul de payOff2

    double payOff2 = 0;

    for(int i = 0; i < assetCurrencyMapping.at(0); i++)
    {

        payOff2 += GET(&spot,i);
    }
    payOff2 /= assetCurrencyMapping.at(0);

    return (payOff1 - payOff2 - strike) > 0 ? (payOff1 - payOff2 - strike) : 0;
}


