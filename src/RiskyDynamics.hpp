#ifndef _Risky_Dynamics_HPP
#define _Risky_Dynamics_HPP

#include "pnl/pnl_vector.h"
#include "json_reader.hpp"

class  RiskyDynamics {

public : 
    double drift ;
    PnlVect * volatilityVector ;

    RiskyDynamics();
    RiskyDynamics(nlohmann::json json);
    void sampleNextDate();

};


#endif 