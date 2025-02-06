#ifndef GRIDTIMEGRID_HPP
#define GRIDTIMEGRID_HPP

#include <vector>
#include "TimeGrid.hpp"

class GridTimeGrid : public TimeGrid {
public:
    GridTimeGrid() ;
    GridTimeGrid(nlohmann::json json);
    ~GridTimeGrid() ;

};

#endif