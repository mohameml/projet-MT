#ifndef OPTION_HPP
#define OPTION_HPP

#include <iostream>
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"
#include "json_reader.hpp"
#include "InterestRateModel.hpp"
#include <vector> 
#include "TimeGrid.hpp"




class Option
{
public:
    std::vector<int> assetCurrencyMapping; 
    std::vector<InterestRateModel> foreignInterestRates;
    InterestRateModel domesticInterestRate;
    TimeGrid monitoringTimeGrid;
    double maturity ;
    int numberOfDaysPerYear;

public:
    Option();
    /**
     * Constructeur de parsing :
     */
    Option(const nlohmann::json json);

    /**
     * Destructeur
     */
    ~Option();

    /**
     * Calcule la valeur du payoff
     *
     * @param[in] matrix est une matrice  de taille (dates + 1)*size
     *  ligne d'index i de la matrice continet la valeur de l'actif du sous-jacent à t = t_i
     */
    virtual double payOff(const PnlMat *matrix) = 0;
};

/**
 * return la classe de l'option selon OptionType
 */
extern Option *instance_option(const nlohmann::json json);

#endif



