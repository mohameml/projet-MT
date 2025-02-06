#include "RebalacingGrid.hpp"

RebalacingGrid::RebalacingGrid()
{
}

RebalacingGrid::RebalacingGrid(nlohmann::json json)
{
    std::vector<int> grid_time = json.at("PortfolioRebalancingOracleDescription").at("DatesInDays").get<std::vector<int>>();
    for (size_t i = 0; i < grid_time.size(); i++)
    {
        this->time_grid.grid_time.push_back(grid_time.at(i));
    }
    
    this->time_grid.setGridTime(grid_time);
}

RebalacingGrid::~RebalacingGrid()
{
}
