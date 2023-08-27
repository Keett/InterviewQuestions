// CS_Tech_Mulakat.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include <string>

#include "Piece.h"
#include "ParseChessboard.cpp"
#include "CalculateScore.cpp"

int main() {

    ParseChessboard parseChessboard;
    std::vector<std::vector<Piece>> chessboard(Chessboard::CHESSBOARD_SIZE, std::vector<Piece>(Chessboard::CHESSBOARD_SIZE));
    chessboard = parseChessboard.parse();

    if (!chessboard.empty()) {
        try {
            CalculateScore calculateScore;
            auto scoreInfo = calculateScore.calculateScore(chessboard);

            std::cout << "Total White Score: " << scoreInfo["WhiteScore"] << std::endl;
            std::cout << "Total Black Score: " << scoreInfo["BlackScore"] << std::endl;
        }
        catch (const std::exception& ex) {
            std::cout << "Exception : " << ex.what();
        }
    }

    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
