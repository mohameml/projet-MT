#ifndef _Foreign_Asian_Option_HPP
#define _Foreign_Asian_Option_HPP

#include "Option.hpp"

class ForeignAsianOption : public Option
{

public:

    ForeignAsianOption();
    ForeignAsianOption(const nlohmann::json json);
    ~ForeignAsianOption();

    double payOff(const PnlMat *matrix) override;
};

#endif