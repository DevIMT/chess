#include "chess.h"
#include <string>

int main()
{
    Board grid;
    Player White('W');
    Player Black('B');

    grid.build();
    grid.set(White,Black);
    // grid.printCoords();

    grid.print();
    bool valid = false;
    string selected_piece;

    std::cout << "White to move \n";
    while (!valid){
        std::cout << "Select a piece (e.g. E2): ";
        std::cin >> selected_piece;

        for (auto &e: selected_piece){
            e = std::toupper(e);
        }


        if (selected_piece[0] >= 'A' && selected_piece[0] <= 'H' && 
            selected_piece[1] >= '1' && selected_piece[1] <= '8'){
                std::cout << "Selecting piece at " << selected_piece << ".\n";
                valid = true;
        } else {
            std::cerr << "Invalid coordinate.\n\n";
        }
    }

    pair<char,int> coord = make_pair(selected_piece[0],int(selected_piece[1]-48));
    std::cout << coord.first << " " << coord.second << "\n";
    

    // Program the pieces
        // Move by coordinates. 

        // Chess piece can only move in allowable directions
}