#include "RebalacingOracle.hpp"
#include "RebalacingFixed.hpp"
#include "RebalacingGrid.hpp"

RebalancingOracle::RebalancingOracle()
{
}

RebalancingOracle::RebalancingOracle(const nlohmann::json json)
{

}

RebalancingOracle::~RebalancingOracle()
{
}

bool RebalancingOracle::IsRebalancing(int t) 
{
    return this->time_grid.has(t);
}

RebalancingOracle createRebalancingOracleFromJson(const nlohmann::json json)
{
    std::string type = json.at("PortfolioRebalancingOracleDescription").at("Type").get<std::string>();
    RebalancingOracle rebalacing ;
    if(type == "Fixed") 
        rebalacing = RebalacingFixed(json);
    else if(type == "Grid")
        rebalacing = RebalacingGrid(json);
    else
    {
        std::cout << "Type of Rebalacing " << type << " unknow. Abort." << std::endl;
        abort();
    }

    return rebalacing;
}
