#include "FixedTimeGrid.hpp"

FixedTimeGrid::FixedTimeGrid()
{
}

FixedTimeGrid::FixedTimeGrid(nlohmann::json json):TimeGrid(json)
{
    maturity = json.at("Option").at("MaturityInDays").get<int>();
    periode = json.at("Option").at("FixingDatesInDays").at("Period").get<int>();;
    std::vector<int> grid_time ;
    // grid_time.push_back(0); // t0

    for (size_t i = 0 ; i <= maturity; i+=periode)
    {
        grid_time.push_back(i);
    }
    
    setGridTime(grid_time);
}



FixedTimeGrid::~FixedTimeGrid()
{
}
