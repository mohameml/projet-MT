#include "InterestRateModel.hpp"
#include <iostream>

InterestRateModel::InterestRateModel()
{
}


InterestRateModel::InterestRateModel(double r, std::string id) :rate(r) , id(id)
{
}

InterestRateModel::~InterestRateModel()
{
}

double InterestRateModel::discount(double t1, double t2)
{
    double value = std::exp(-rate*(t2 - t1));
    return value;
}

double InterestRateModel::account(double t1, double t2)
{
    double value = std::exp(rate*(t2 - t1));
    return value;
}
