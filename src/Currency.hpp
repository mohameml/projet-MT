#ifndef _Currency_HPP
#define _Currency_HPP

#include "json_reader.hpp"
#include "InterestRateModel.hpp"
#include "RiskyDynamics.hpp"

class  Currency : public RiskyDynamics {

public : 

    Currency();
    Currency(nlohmann::json json);


};


#endif 