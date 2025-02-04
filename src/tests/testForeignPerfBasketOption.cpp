// #include <iostream>
// #include <cassert>
// #include "../ForeignPerfBasketOption.hpp"
// #include "pnl/pnl_matrix.h"
// #include "../json_reader.hpp"


// void test_payOff() {
//     // Sample JSON configuration
//     nlohmann::json jsonConfig = {
//         {"strike", 0},
//         {"assetCurrencyMapping", {2, 3}}
//     };

//     // Create ForeignPerfBasketOption object
//     ForeignPerfBasketOption option(jsonConfig);

//     // Create a sample PnlMat matrix
//     PnlMat *matrix = pnl_mat_create_from_scalar(3, 5, 1.0);
//     MLET(matrix, 0, 0) = 100;
//     MLET(matrix, 0, 1) = 110;
//     MLET(matrix, 0, 2) = 120;
//     MLET(matrix, 0, 3) = 130;
//     MLET(matrix, 0, 4) = 140;

//     MLET(matrix, 1, 0) = 105;
//     MLET(matrix, 1, 1) = 115;
//     MLET(matrix, 1, 2) = 125;
//     MLET(matrix, 1, 3) = 135;
//     MLET(matrix, 1, 4) = 145;

//     MLET(matrix, 2, 0) = 110;
//     MLET(matrix, 2, 1) = 120;
//     MLET(matrix, 2, 2) = 130;
//     MLET(matrix, 2, 3) = 140;
//     MLET(matrix, 2, 4) = 150;

//     // Calculate payoff
//     double payoff = option.payOff(matrix);

//     // Expected payoff calculation
//     double expectedPayoff = 0;
//     assert(payoff == expectedPayoff);

//     // Clean up
//     pnl_mat_free(&matrix);

//     std::cout << "Test passed!" << std::endl;
// }

// int main() {
//     test_payOff();
//     return 0;
// }


#include <iostream>
#include <cassert>
#include "../ForeignPerfBasketOption.hpp"
#include "pnl/pnl_matrix.h"
#include "../json_reader.hpp"

void test_payOff() {
    // Sample JSON configuration
    nlohmann::json jsonConfig = {
        {"strike", 100},
        {"assetCurrencyMapping", {2, 3}},
        {"foreignInterestRates", {
            {{"rate", 0.01}},
            {{"rate", 0.02}}
        }}
    };

    // Create an instance of ForeignPerfBasketOption
    ForeignPerfBasketOption option(jsonConfig);

    // Create a sample PnlMat matrix
    PnlMat *matrix = pnl_mat_create_from_scalar(3, 5, 100.0);

    // Set specific values in the matrix to simulate different scenarios
    MLET(matrix, 0, 0) = 110; MLET(matrix, 0, 1) = 120;
    MLET(matrix, 1, 0) = 130; MLET(matrix, 1, 1) = 140;
    MLET(matrix, 2, 0) = 150; MLET(matrix, 2, 1) = 160;

    // Call the payOff function
    double result = option.payOff(matrix);

    // Expected result calculation
    double expectedPayOff = 0; // Replace with the expected value based on your logic

    // Assert the result
    assert(result == expectedPayOff);

    // Free the matrix
    pnl_mat_free(&matrix);

    std::cout << "Test passed!" << std::endl;
}

int main() {
    test_payOff();
    return 0;
}