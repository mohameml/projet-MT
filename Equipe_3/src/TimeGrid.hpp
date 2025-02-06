#ifndef _TIME_GRID_HPP
#define _TIME_GRID_HPP


#include <nlohmann/json.hpp>
#include <vector>
#include <iostream>

class TimeGrid {



public : 

    std::vector<int> grid_time;
    std::string TimeGridType ;
    TimeGrid();
    ~TimeGrid();
    TimeGrid(nlohmann::json json);
    int at(int index);
    int len();
    bool has(int nDays);
    void setGridTime(std::vector<int> grid_time);
    int getLastIndex(int t);
    std::vector<int> getAllDates();

};



/**
 * return la classe de TimeGrid selon TimeGridType :
 */
extern TimeGrid createTimeGridFromJson(const nlohmann::json json);


#endif 