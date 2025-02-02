#include <fstream>
#include <iostream>
#include "Portfolio.hpp"
#include <nlohmann/json.hpp>
#include "MonteCarlo.hpp"

int main(int argc, char *argv[])
{


    if (argc != 4)
    {
        std::cout << "Le nombre d'arguments attendu est 4" << std::endl;
        exit(1);
    }

    std::ifstream file(argv[1]);
    if (!file.is_open())
    {
        std::cerr << "Error opening file" << std::endl;
        exit(1);
    }
    PnlMat *data = pnl_mat_create_from_file(argv[2]);
    
    nlohmann::json json = nlohmann::json::parse(file);

    MonteCarlo *monte_carlo = new MonteCarlo(json);


    
    Portfolio hedgingPortfolio(json, *monte_carlo);
    
    // calculer le portefeuille de couverture
    
    
    // ....
    nlohmann::json jsonPortfolio = hedgingPortfolio.positions;
    std::ofstream ifout(argv[3], std::ios_base::out);
    if (!ifout.is_open()) {
        std::cout << "Unable to open file " << argv[3] << std::endl;
        std::exit(1);
    }
    ifout << jsonPortfolio.dump(4);
    ifout.close();


    return 0;
}
