#include "RiskyDynamics.hpp"
#include "pnl/pnl_vector.h"

RiskyDynamics::RiskyDynamics()
{
}

RiskyDynamics::RiskyDynamics(double dirft, double realVolatility, PnlVect L_i , int index):drift(drift),realVolatility(realVolatility),volatilityVector(&L_i),index(index)
{
    pnl_vect_mult_scalar(this->volatilityVector, realVolatility);
}


RiskyDynamics::~RiskyDynamics()
{
    pnl_vect_free(&volatilityVector);
}



void RiskyDynamics::sampleNextDate(PnlMat *path, double step, const PnlVect *G, int index_time)
{
    
    double value =  exp((drift- realVolatility * realVolatility / 2.0) * step +  sqrt(step) * pnl_vect_scalar_prod(volatilityVector, G));

    double s_t_d = MGET(path, index_time - 1, index);
    MLET(path , index_time , index) = s_t_d*value ;
}


void RiskyDynamics::sampleNextDate(PnlMat *path, double step, const PnlVect *G, int index_time , bool isMonitoringDate)
{
    
    double value =  exp((drift- realVolatility * realVolatility / 2.0) * step +  sqrt(step) * pnl_vect_scalar_prod(volatilityVector, G));

    if(isMonitoringDate) {

        double s_t_d = MGET(path, index_time - 1, index);
        MLET(path , index_time , index) = s_t_d*value ;

    
    } else {

        double s_t_d = MGET(path, index_time, index);
        MLET(path , index_time , index) = s_t_d*value ;
        
    }

}
