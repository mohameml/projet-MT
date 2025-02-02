#ifndef __MONTE_CARLO_HPP__
#define __MONTE_CARLO_HPP__

#include "Option.hpp"
#include "GlobalModel.hpp"
#include "pnl/pnl_random.h"

class MonteCarlo {


public:

    Option *option;           /// pointeur sur l'option
    GlobalModel *model; /// pointeur vers le modèle
    int sample_number;        /// nombre de tirage de MC
    double fd_step;           /// pas de méthode de différance fini
    PnlRng *rng;    

public : 

    MonteCarlo(const nlohmann::json json);

};


#endif 