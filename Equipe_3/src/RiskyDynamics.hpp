#ifndef _Risky_Dynamics_HPP
#define _Risky_Dynamics_HPP

#include "pnl/pnl_vector.h"
#include "json_reader.hpp"

class  RiskyDynamics {

public : 
    int index ;
    double drift ;
    double realVolatility;
    PnlVect*  volatilityVector ;

    RiskyDynamics();
    RiskyDynamics(double dirft , double realVolatility , PnlVect* volatilityVector , int index);
    ~RiskyDynamics();
    void sampleNextDate(PnlMat* path , double step , const PnlVect* G  , int index_time , bool isMonitoringDate) ;
    void sampleNextDate(PnlMat *path, double step, const PnlVect *G, int index_time);
};


#endif 