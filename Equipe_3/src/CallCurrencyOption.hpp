#ifndef _CALL_CURR_Optiont_H
#define _CALL_CURR_Optiont_H

#include "Option.hpp"

class CallCurrencyOption : public Option
{

public:
    double strike;
    CallCurrencyOption();
    CallCurrencyOption(const nlohmann::json json);
    ~CallCurrencyOption();

    double payOff(const PnlMat *matrix) override;
};

#endif