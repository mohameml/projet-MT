#include <iostream>
#include "Portfolio.hpp"
#include "json_reader.hpp"



Portfolio::Portfolio(nlohmann::json &jsonParams)
{
    rebalacingOrcale = createRebalancingOracleFromJson(jsonParams);
}

Portfolio::~Portfolio()
{
    // for (auto& pos : positions)
    // {
    //     delete pos;  
    // }
    
}

