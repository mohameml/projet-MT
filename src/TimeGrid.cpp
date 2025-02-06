#include "TimeGrid.hpp"
#include <nlohmann/json.hpp>
#include <iostream>
#include "FixedTimeGrid.hpp"
#include "GridTimeGrid.hpp"


TimeGrid::TimeGrid()
{
}

TimeGrid::~TimeGrid()
{
}

TimeGrid::TimeGrid(nlohmann::json json)
{
    TimeGridType = json.at("Option").at("FixingDatesInDays").at("Type").get<std::string>();

}


int TimeGrid::at(int index)
{
    if(index >= grid_time.size()) {
        std::cout << "bad index : index must be less then size" << std::endl ;
        std::exit(1);
    }
    return this->grid_time.at(index);
}


int TimeGrid::len()
{
    return grid_time.size();
}

bool TimeGrid::has(int nDays)
{
    for (int elem : grid_time) {
        if (elem == nDays) {
            return true;
        }
    }
    return false;
}

void TimeGrid::setGridTime(std::vector<int> grid_time)
{
    this->grid_time = grid_time;
}

int TimeGrid::getLastIndex(int t)
{
    for (int i = 0; i < grid_time.size(); i++)
    {
        if(grid_time.at(i) > t) {
            return i - 1;
        }
    }
    
    return grid_time.size() - 1;
}

std::vector<int> TimeGrid::getAllDates()
{
    std::vector<int> allDates ;
    int T = grid_time.at(grid_time.size() - 1);

    for (int t = 1 ; t < T ; t++)
    {
        allDates.push_back(t);
    }

    return allDates;    
}

TimeGrid createTimeGridFromJson(const nlohmann::json json)
{
    std::string type = json.at("Option").at("FixingDatesInDays").at("Type").get<std::string>();
    TimeGrid timeGrid  ;
    if(type == "Fixed") 
        timeGrid = FixedTimeGrid(json);
    else if(type == "Grid")
        timeGrid = GridTimeGrid(json);
    else
    {
        std::cout << "Option " << type << " unknow. Abort." << std::endl;
        abort();
    }

    return timeGrid;
}
