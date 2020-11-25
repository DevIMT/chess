#include "chess.h"

int main()
{
    Board grid;
    Player White('W');
    Player Black('B');

    grid.build();
    grid.set(White,Black);
    // grid.printCoords();

    grid.print();

    std::cout << "White's Pieces: " ;
    for (auto e : White.pieces_list()){
        std::cout << e.get_symbol() << ", ";
    }
    std::cout << "\nBlack's Pieces: ";
    for (auto e : Black.pieces_list()){
        std::cout << e.get_symbol() << ", ";
    }
    std::cout << "\n";
    // Set the board (with pawns)

    // Program the pieces
        // Move by coordinates. 

        // Chess piece can only move in allowable directions
}