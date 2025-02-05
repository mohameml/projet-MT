#include "RebalacingFixed.hpp"

RebalacingFixed::RebalacingFixed()
{
}

RebalacingFixed::RebalacingFixed(nlohmann::json json)
{
    int maturity = json.at("Option").at("MaturityInDays").get<int>();
    int periode = json.at("PortfolioRebalancingOracleDescription").at("Period").get<int>();;

    for (size_t i = 0 ; i <= maturity; i+=periode)
    {
        this->time_grid.grid_time.push_back(i);
    }
    
}

RebalacingFixed::~RebalacingFixed()
{
}
