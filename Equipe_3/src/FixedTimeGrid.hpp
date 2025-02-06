#ifndef FIXEDTIMEGRID_HPP
#define FIXEDTIMEGRID_HPP

#include "TimeGrid.hpp"

class FixedTimeGrid : public TimeGrid {

private : 
    int periode ;
    int maturity ;

public:
    FixedTimeGrid();
    FixedTimeGrid(nlohmann::json json);
    ~FixedTimeGrid();




};

#endif 