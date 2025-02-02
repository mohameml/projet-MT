#ifndef _Quanto_Exchange_Option_HPP
#define _Quanto_Exchange_Option_HPP

#include "Option.hpp"

class QuantoExchangeOption : public Option
{

public:
    double strike;
    PnlVect *payoff_coeffcients;
    PnlVect *vect_ones;
    QuantoExchangeOption();
    QuantoExchangeOption(const nlohmann::json json);
    ~QuantoExchangeOption();

    double payOff(const PnlMat *matrix) override;
};

#endif