#include    "ForeignPerfBasketOption.hpp"
#include    "pnl/pnl_vector.h"

ForeignPerfBasketOption::ForeignPerfBasketOption(const nlohmann::json json) : Option(json) {
    this->strike = 0;
}

ForeignPerfBasketOption::~ForeignPerfBasketOption()
{
}

double ForeignPerfBasketOption::payOff(const PnlMat *matrix)
{
    for(int i = 1; i < assetCurrencyMapping.size() ; i++)
    {
        
    }
}