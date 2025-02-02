#ifndef _Foreign_Asian_Option_HPP
#define _Foreign_Asian_Option_HPP

#include "Option.hpp"

class ForeignAsianOption : public Option
{

public:
    double strike;
    PnlVect *payoff_coeffcients;
    PnlVect *vect_ones;
    ForeignAsianOption();
    ForeignAsianOption(const nlohmann::json json);
    ~ForeignAsianOption();

    double payOff(const PnlMat *matrix) override;
};

#endif