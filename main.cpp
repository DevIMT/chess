#include "chess.h"
#include <string>

int main()
{
    Board board;
    Game chess(board);
    Player White('W');
    Player Black('B');
    chess.start();
    int move = 1;
    string move_input;
    int move_status;
    while (true){
        if (move % 2 == 0){
            move_input = chess.turn(Black);
            move_status = chess.move(Black,move_input);
            
        } else {
            move_input = chess.turn(White);
            move_status = chess.move(White,move_input);

        }   

        if (move_status == 0){
            move++;
        }

        std::cout << "\n\n";
    }
    

    // Program the pieces
        // Move by coordinates. 

        // Chess piece can only move in allowable directions
}