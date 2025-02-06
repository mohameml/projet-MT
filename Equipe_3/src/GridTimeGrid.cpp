#include "GridTimeGrid.hpp"

GridTimeGrid::GridTimeGrid()
{
}

GridTimeGrid::GridTimeGrid(nlohmann::json json)
{
    std::vector<int> grid_time = json.at("Option").at("FixingDatesInDays").at("DatesInDays").get<std::vector<int>>();
    if(grid_time.at(0) != 0) 
        grid_time.insert(grid_time.begin() , 0); // t0 = 0 ;
    setGridTime(grid_time);
}

GridTimeGrid::~GridTimeGrid()
{
}
