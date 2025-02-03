#include "InterestRateModel.hpp"
#include <iostream>

InterestRateModel::InterestRateModel()
{
}

InterestRateModel::InterestRateModel(nlohmann::json json)
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
    return 0.0;
}

double InterestRateModel::account(double t1, double t2)
{
    return 0.0;
}
