#ifndef _ForeignPerfBasketOption_HPP
#define _ForeignPerfBasketOption_HPP

#include "Option.hpp"

class ForeignPerfBasketOption : public Option
{

public:
    double strike;
    PnlVect *payoff_coeffcients;
    PnlVect *vect_ones;
    ForeignPerfBasketOption();
    ForeignPerfBasketOption(const nlohmann::json json);
    ~ForeignPerfBasketOption();

    double payOff(const PnlMat *matrix) override;
};

#endif