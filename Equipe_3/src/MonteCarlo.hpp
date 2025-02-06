#ifndef __MONTE_CARLO_HPP__
#define __MONTE_CARLO_HPP__

#include "Option.hpp"
#include "GlobalModel.hpp"
#include "pnl/pnl_random.h"
#include "Position.hpp"

class MonteCarlo {


public:

    Option *option;           /// pointeur sur l'option
    GlobalModel *model; /// pointeur vers le modèle
    int sample_number;        /// nombre de tirage de MC
    double fd_step;           /// pas de méthode de différance fini
    PnlRng *rng;    
    int model_size ; /// size of the model 
    int nbDays ;
    int numberOfDaysPerYear;

public : 
    MonteCarlo();
    MonteCarlo(const nlohmann::json json);
    ~MonteCarlo();

    /**
     * calcul du prix à t  avec le delta de l'option à t   :
     *
     * @param[in] t : current time
     * @param[in] position : classe contient : price , price_std , deltas_vect , stddev_deltas_vect
     * @param[in] Past : matrice de taille (last_index + 1)*D ou (last_index)*D qui continet s_t0 , s_t1 , ..... , st_i , st
     */
    void priceAndDelta(int t, const PnlMat *Past, double& price , double& price_std , PnlVect* deltas_vect , PnlVect*  stddev_deltas_vect);


protected:
    /**
     * terime le  calucl de prix et std_prix :
     *
     * @param[in, out] price
     * @param[in, out] stdDev
     * @param nSamples : nombre de tirage de MC
     * @param t current date
     */
    void end_of_calcul_price(double &price, double &stdDev, double t) const;

    /**
     * terime le  calucl de delta :
     *
     * @param[in, out] price
     * @param[in, out] stdDev
     * @param nSamples : nombre de tirage de MC
     * @param t current date
     * @param St : vecteur de prix du sous-jacent
     */
    void end_of_calcul_delta(PnlVect *delta, PnlVect *delta_stdev, double t, PnlVect *St) const;

};


#endif 