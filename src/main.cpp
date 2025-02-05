#include <fstream>
#include <iostream>
#include "Portfolio.hpp"
#include <nlohmann/json.hpp>
#include "MonteCarlo.hpp"
#include "Hedger.hpp"


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

    // les fichiers : fichier 1 params.json , fichier 2 data.csv
    
    nlohmann::json json = nlohmann::json::parse(file);
    PnlMat *dataHistorique = pnl_mat_create_from_file(argv[2]);
    


    // class Hedger :

    Hedger* hedger = new Hedger(json);

    // calcul de positions :

    hedger->hedge(dataHistorique);
    
    
    // fichier json de sortie 
    

    std::list<Position> list_postion ;

    for (const auto& pos : hedger->hedgingPortfolio->positions)
    {
        list_postion.push_back(*(pos));
    }
    

    nlohmann::json jsonPortfolio = list_postion;



    std::ofstream ifout(argv[3], std::ios_base::out);
    if (!ifout.is_open()) {
        std::cout << "Unable to open file " << argv[3] << std::endl;
        std::exit(1);
    }
    ifout << jsonPortfolio.dump(4);
    ifout.close();


    delete hedger;
    pnl_mat_free(&dataHistorique);

    return 0;
}
