#include <iostream>
#include "Portfolio.hpp"
#include "json_reader.hpp"


Portfolio::Portfolio(nlohmann::json &jsonParams, MonteCarlo &monteCarlo) : monteCarlo(monteCarlo)
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

