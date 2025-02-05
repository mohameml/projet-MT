// #include <iostream>
// #include <cassert>
// #include "../ForeignPerfBasketOption.hpp"
// #include "pnl/pnl_matrix.h"
// #include "../json_reader.hpp"

// void test_payOff() {

    
//     // Create an instance of ForeignPerfBasketOption




//     ForeignPerfBasketOption option(jsonConfig);

//     // Create a sample PnlMat matrix
//     PnlMat *matrix = pnl_mat_create_from_scalar(3, 5, 100.0);

//     // Set specific values in the matrix to simulate different scenarios
//     MLET(matrix, 0, 0) = 110; MLET(matrix, 0, 1) = 120;
//     MLET(matrix, 1, 0) = 130; MLET(matrix, 1, 1) = 140;
//     MLET(matrix, 2, 0) = 150; MLET(matrix, 2, 1) = 160;

//     // Call the payOff function
//     double result = option.payOff(matrix);

//     // Expected result calculation
//     double expectedPayOff = 0; // Replace with the expected value based on your logic

//     // Assert the result
//     assert(result == expectedPayOff);

//     // Free the matrix
//     pnl_mat_free(&matrix);

//     std::cout << "Test passed!" << std::endl;
// }

// int main() {
//     // test_payOff();
//     return 0;
// }
