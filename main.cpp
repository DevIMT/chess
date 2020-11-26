#include "chess.h"
#include <string>

int main()
{
    Game chess;
    Player White('W');
    Player Black('B');
    chess.start();
    int move = 1;
    while (true){
        if (move % 2 == 0){
            chess.turn(Black);
        } else {
            chess.turn(White);
        }
    }


    pair<char,int> coord = make_pair(piece[0],int(piece[1]-48));
    std::cout << coord.first << " " << coord.second << "\n";
    

    // Program the pieces
        // Move by coordinates. 

        // Chess piece can only move in allowable directions
}