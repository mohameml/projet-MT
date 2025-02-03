#include "FixedRebalacing.hpp"

FixedRebalacing::FixedRebalacing(nlohmann::json json)
{
    time_grid = createTimeGridFromJson(json);
}

bool FixedRebalacing::IsRebalancing(int date) 
{
    bool res = time_grid.has(date);

    return res ;
}
