#include "GridTimeGrid.hpp"

GridTimeGrid::GridTimeGrid()
{
}

GridTimeGrid::GridTimeGrid(nlohmann::json json)
{
    std::vector<int> grid_time = json.at("Option").at("FixingDatesInDays").at("DatesInDays").get<std::vector<int>>();
    setGridTime(grid_time);
}

GridTimeGrid::~GridTimeGrid()
{
}
