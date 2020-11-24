#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

#include "chess.h"

Piece::Piece(std::string coord)
{
    loc = coord;
}

Piece::Piece(char n, char t, std::string coord)
{
    name = n;
    type = t;
    loc = coord;
}

// Return string coordinates of piece (e.g. A4)
std::string Piece::location()
{
    return loc;
}

// Return name of the piece
char Piece::get_name()
{
    return name;
}

void Piece::setsymbol(std::string symb)
{
    symbol = symb;
}

char Piece::get_type()
{
    return type;
}

void Piece::setname(char n)
{
    name = n;
}

void Piece::settype(char t)
{
    type = t;
}

void Board::build()
{
    board = std::vector<std::vector<Piece>> (8, std::vector<Piece> (8));

    // Build the board
    for (int y = 0; y < 8; ++y){
        for (int x = 0; x < 8; ++x){
            board[y][x] = Piece(coordinates[y][x]);       
        }
    }

}

void Board::set()
{
    for (int y = 0; y < 8; ++y){
        for (int x = 0; x < 8; ++x){
            // Black pieces
            if (y <= 1){
                board[y][x].settype('B');
                if (y == 0){
                    if (x == 0 || x == 7){
                        board[y][x].setsymbol("\u2656");
                        board[y][x].setname('R');
                    }
                    else if (x == 1 || x == 6){
                        board[y][x].setsymbol("\u2658");
                        board[y][x].setname('k');
                    } else if (x == 2 || x == 5){
                        board[y][x].setsymbol("\u2657");
                        board[y][x].setname('B');
                    } else if (x == 3){
                        board[y][x].setsymbol("\u2654");
                        board[y][x].setname('K');
                    } else {
                        board[y][x].setsymbol("\u2655");
                        board[y][x].setname('Q');
                    }
                } else {
                    board[y][x].setsymbol("\u2659");
                    board[y][x].setname('P');
                }
            } 
            // White Pieces
            else if (y >= 6) {
                board[y][x].settype('W');
                if (y == 7){
                    if (x == 0 || x == 7){
                        board[y][x].setsymbol(u8"\u265C");
                        board[y][x].setname('R');
                    }
                    else if (x == 1 || x == 6){
                        board[y][x].setsymbol(u8"\u265E");
                        board[y][x].setname('k');
                    } else if (x == 2 || x == 5){
                        board[y][x].setsymbol(u8"\u265D");
                        board[y][x].setname('B');
                    } else if (x == 3){
                        board[y][x].setsymbol(u8"\u265A");
                        board[y][x].setname('K');
                    } else {
                        board[y][x].setsymbol(u8"\u265B");
                        board[y][x].setname('Q');
                    }
                } else {
                    board[y][x].setsymbol(u8"\u265F");
                    board[y][x].setname('P');
                }
            } else {
                board[y][x].settype('N');
                board[y][x].setname(' ');
                board[y][x].setsymbol(" ");

            }            
        }
    }    
}

void Board::printCoords()
{
    std::ofstream outfile("board.txt");    
    // First line
    outfile << "        --BLACK--         \n";
    outfile << " _________________________\n"; // 18
    int y_coord = 0;
    int x_coord = 0;
    for (int y = 0; y < 8; ++y){
        x_coord = 0;
        for (int x = 0; x < 18; ++x){
            if (x == 0)
                outfile << 8-(y);
            else {
                if (x % 2 == 0){
                    outfile << board[y_coord][x_coord++].location();
                } else {
                    outfile << "|";
                }
            }
        }
        y_coord++;
        outfile << "\n";
    }
    
    outfile << " |A |B |C |D |E |F |G |H |\n";
    outfile << "        --WHITE--         \n";

    outfile.close();
}

void Board::print()
{
    std::ofstream outfile("board.txt");    
    // First line
    outfile << "        --BLACK--         \n";
    outfile << " _________________________\n"; // 18
    int y_coord = 0;
    int x_coord = 0;
    Piece p;
    for (int y = 0; y < 8; ++y){
        x_coord = 0;
        for (int x = 0; x < 18; ++x){
            p = board[y_coord][x_coord];
            if (x == 0)
                outfile << 8-(y);
            else {
                if (x % 2 == 0){
                    if (p.get_type() == 'W'){
                        outfile << "\e[1m" << p.get_name() << std::setw(2);
                        x_coord++;
                    } else {
                        outfile << "\e[0m" << p.get_name() << std::setw(2);
                        x_coord++;
                    }

                } else {
                    outfile << "|" << std::setw(2);
                }
            }
        }
        y_coord++;
        outfile << "\n";
    }
    
    // outfile << " ";
    // char letter = 'A';
    // for (int i = 1; i < 17; ++i){
    //     if (i % 2 == 0){
    //         outfile << letter++ << std::setw(2);
    //     } else {
    //         outfile << "|" << std::setw(2);
    //     }
    // }
    outfile << "        --WHITE--         \n";

    outfile.close();
}

