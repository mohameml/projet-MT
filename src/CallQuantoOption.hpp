#ifndef _CALL_QUANTO_Option_H
#define _CALL_QUANTO_Option_H

#include "Option.hpp"

class CallQuantoOption : public Option
{

public:
    double strike;
    CallQuantoOption();
    CallQuantoOption(const nlohmann::json json);
    ~CallQuantoOption();

    double payOff(const PnlMat *matrix) override;
};

#endif