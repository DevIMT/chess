#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include "chess.h"

using namespace std;

Piece::Piece(pair<char,int> coord)
{
    loc = coord;
}

Piece::Piece(string n, char t, pair<char,int> coord)
{
    name = n;
    type = t;
    loc = coord;
}

// Return a std::pair coordinates of piece (e.g. ('A',4))
pair<char,int> Piece::location()
{
    return loc;
}

// Return name of the piece
string Piece::get_name()
{
    return name;
}

// Set the piece's unicode symbol
void Piece::setsymbol(string symb)
{
    symbol = symb;
}

// Return the piece's color (type)
char Piece::get_type()
{
    return type;
}

// Returns the piece's unicode symbol
string Piece::get_symbol()
{
    return symbol;
}

// Changes the piece's name to n
void Piece::setname(string n)
{
    name = n;
}

// Changes the piece's name to t
void Piece::settype(char t)
{
    type = t;
}

// Add's pieces to the 8x8 board
void Board::build()
{
    board = vector<vector<Piece>> (8, vector<Piece> (8));

    // Build the board
    for (int y = 0; y < 8; ++y){
        for (int x = 0; x < 8; ++x){
            board[y][x] = Piece(coordinates[y][x]);       
        }
    }

}

// Sets the values of the pieces on the board
void Board::set(Player &White, Player &Black)
{
    for (int y = 0; y < 8; ++y){
        for (int x = 0; x < 8; ++x){
            // Black pieces
            if (y <= 1){
                board[y][x].settype('B');
                if (y == 0){
                    if (x == 0 || x == 7){
                        board[y][x].setsymbol(" \u2656 ");
                        board[y][x].setname("Rook");
                    }
                    else if (x == 1 || x == 6){
                        board[y][x].setsymbol(" \u2658 ");
                        board[y][x].setname("Knight");
                    } else if (x == 2 || x == 5){
                        board[y][x].setsymbol(" \u2657 ");
                        board[y][x].setname("Bishop");
                    } else if (x == 3){
                        board[y][x].setsymbol(" \u2654 ");
                        board[y][x].setname("King");
                    } else {
                        board[y][x].setsymbol(" \u2655 ");
                        board[y][x].setname("Queen");
                    }
                } else {
                    board[y][x].setsymbol(" \u2659 ");
                    board[y][x].setname("Pawn");
                }
                Black.add_piece(board[y][x]);
            } 
            // White Pieces
            else if (y >= 6) {
                board[y][x].settype('W');
                if (y == 7){
                    if (x == 0 || x == 7){
                        board[y][x].setsymbol(u8" \u265C ");
                        board[y][x].setname("Rook");
                    }
                    else if (x == 1 || x == 6){
                        board[y][x].setsymbol(u8" \u265E ");
                        board[y][x].setname("Knight");
                    } else if (x == 2 || x == 5){
                        board[y][x].setsymbol(u8" \u265D ");
                        board[y][x].setname("Bishop"); 
                    } else if (x == 3){
                        board[y][x].setsymbol(u8" \u265A ");
                        board[y][x].setname("King");
                    } else {
                        board[y][x].setsymbol(u8" \u265B ");
                        board[y][x].setname("Queen");
                    }
                } else {
                    board[y][x].setsymbol(u8" \u265F ");
                    board[y][x].setname("Pawn");
                }
                White.add_piece(board[y][x]);
            } else {
                board[y][x].settype('N');
                board[y][x].setname("Null");
                board[y][x].setsymbol(" \u26C9 ");

            }            
        }
    }    
}

// Prints the coordinates of the board elements
void Board::printCoords()
{
    ofstream outfile("board.txt");    
    // First line
    outfile << "       --BLACK--         \n";
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
                    outfile << "(" << board[y_coord][x_coord].location().first << ", "
                            << board[y_coord][x_coord].location().second << ")";
                    x_coord++;
                } else {
                    outfile << "|";
                }
            }
        }
        y_coord++;
        outfile << "\n";
    }
    
    outfile << " |A |B |C |D |E |F |G |H |\n";
    outfile << "       --WHITE--         \n";

    outfile.close();
}

// Prints coordinates within another print function (allows for side-by-side view)
void Board::printCoords(ofstream &outfile)
{   
    // First line
    outfile << "\n\n" << setw(31) << "--BLACK--";
    outfile << "\n _____________________________________________________\n"; // 18
    int y_coord = 0;
    int x_coord = 0;
    for (int y = 0; y < 8; ++y){
        x_coord = 0;
        for (int x = 0; x < 18; ++x){
            if (x == 0)
                outfile << 8-(y);
            else {
                if (x % 2 == 0){
                    outfile << "(" << board[y_coord][x_coord].location().first << ","
                            << board[y_coord][x_coord].location().second << ")";
                    x_coord++;
                } else {
                    outfile << " | ";
                }
            }
        }
        y_coord++;
        outfile << "\n";
    }
    
    outfile << "  |  ";
    char letter = 'A';
    for (int i = 2; i < 18; ++i){
        if (i % 2 == 0){
            outfile << letter++;
        } else {
            outfile << setw(7);
        }
    }
    outfile << "\n" << setw(31) << "--WHITE--";

}

// Prints the board with pieces
void Board::print()
{
    ofstream outfile("board.txt");    
    // First line
    outfile << setw(31) << "--BLACK--";
    outfile << "\n _____________________________________________________\n"; // 18
    int y_coord = 0;
    int x_coord = 0;
    for (int y = 0; y < 8; ++y){
        x_coord = 0;
        for (int x = 0; x < 18; ++x){
            if (x == 0)
                outfile << 8-(y);
            else {
                if (x % 2 == 0){
                    outfile << board[y_coord][x_coord++].get_symbol();
                } else {
                    outfile << " | ";
                }
            }
        }
        y_coord++;
        outfile << "\n";
    }
    
    outfile << "  |  ";
    char letter = 'A';
    for (int i = 2; i < 18; ++i){
        if (i % 2 == 0){
            outfile << letter++;
        } else {
            outfile << setw(7);
        }
    }
    outfile << "\n" << setw(31) << "--WHITE--";

    printCoords(outfile); 
    outfile.close();
}

Player::Player(char s)
{
    side = s;
}

void Player::add_piece(Piece p)
{
    pieces.push_back(p);
}

vector<Piece> Player::pieces_list()
{
    return pieces;
}



