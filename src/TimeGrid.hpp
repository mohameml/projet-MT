#ifndef _TIME_GRID_HPP
#define _TIME_GRID_HPP


#include <nlohmann/json.hpp>


class TimeGrid {

public : 

    int at(int index);
    int len();
    bool has(int nDays);



};



/**
 * return la classe de TimeGrid selon TimeGridType :
 */
extern TimeGrid *createTimeGridFromJson(const nlohmann::json json);


#endif 