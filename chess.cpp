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
pair<int,int> Piece::get_location()
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

// Changes the piece's y,x coordinates
void Piece::setloc(pair<int,int> pos)
{
    loc = pos;
}

// Increments the piece's movecount (affects moves list for Pawns)
void Piece::move()
{
    movecount++;
}

// Returns the opposite type of the piece's type (White/Black)
char Piece::opp()
{
    if (type == 'W'){
        return 'B';
    } else if (type == 'B'){
        return 'W';
    }

    return 'N';
}

// Add's pieces to the 8x8 board
void Board::build()
{
    board = vector<vector<Piece>> (8, vector<Piece> (8));

    // Build the board
    for (int y = 0; y < 8; ++y){
        for (int x = 0; x < 8; ++x){
            board[y][x] = Piece(make_pair(y,x));       
        }
    }

}

// Sets the values of the pieces on the board
void Board::set()
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
                    outfile << "(" << coordinates[y_coord][x_coord].first << ", "
                            << coordinates[y_coord][x_coord].second << ")";
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
                    // Print y,x coordinates
                    outfile << "(" << y_coord << "," << x_coord << ")";
                                        
                    // Prints char,int coordinates  
                    // outfile << "(" << board[y_coord][x_coord].location().first << ","
                    //         << board[y_coord][x_coord].location().second << ")";
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

Piece Board::find_piece(pair<int,int> yx)
{
    return board[yx.first][yx.second];
}

pair<int,int> find_yx(pair<char,int> coord)
{
    // Convert coord into x,y coordinates to find on 2d vector 'board'
    int x;
    int y;
    if (coord.first == 'A'){x=0;}
    else if (coord.first == 'B'){x=1;}
    else if (coord.first == 'C'){x=2;}
    else if (coord.first == 'D'){x=3;}
    else if (coord.first == 'E'){x=4;}
    else if (coord.first == 'F'){x=5;}
    else if (coord.first == 'G'){x=6;}
    else if (coord.first == 'H'){x=7;}
    else {std::cerr << "Error converting x coordinate\n";}

    if (coord.second == 8){y=0;}
    else if (coord.second == 7){y=1;}
    else if (coord.second == 6){y=2;}
    else if (coord.second == 5){y=3;}
    else if (coord.second == 4){y=4;}
    else if (coord.second == 3){y=5;}
    else if (coord.second == 2){y=6;}
    else if (coord.second == 1){y=7;}
    else {std::cerr << "Error converting y coordinate\n";}

    return make_pair(y,x);
}

// Chess Piece Moves
vector<vector<pair<int,int>>> Piece::moves()
{
    int x = loc.second;
    int y = loc.first;
    int dir = 0; // Number of total directions piece can move
    if (type == 'W'){
        if (name == "Pawn"){
            dir = 3;
            vector<vector<pair<int,int>>> p_moves(dir, vector<pair<int,int>>(0));
            if (movecount == 0){
                p_moves[0].push_back(make_pair(y-1,x));
                p_moves[0].push_back(make_pair(y-2,x));
                p_moves[1].push_back(make_pair(y-1,x-1)); // left diag
                p_moves[2].push_back(make_pair(y-1,x+1)); // right diag
                return p_moves;
            } else {
                p_moves[0].push_back(make_pair(y-1,x));
                p_moves[1].push_back(make_pair(y-1,x-1));
                p_moves[2].push_back(make_pair(y-1,x+1));
                return p_moves;
            }
        }
    } else if (type == 'B'){
        if (name == "Pawn"){
            dir = 3;
            vector<vector<pair<int,int>>> p_moves(dir, vector<pair<int,int>>(0));
            if (movecount == 0){
                p_moves[0].push_back(make_pair(y+1,x));
                p_moves[0].push_back(make_pair(y+2,x));
                p_moves[1].push_back(make_pair(y+1,x-1)); // left diag
                p_moves[2].push_back(make_pair(y+1,x+1)); // right diag
                return p_moves;
            } else {
                p_moves[0].push_back(make_pair(y+1,x));
                p_moves[1].push_back(make_pair(y+1,x-1));
                p_moves[2].push_back(make_pair(y+1,x+1));
                return p_moves;
            }
        }
    }

    return vector<vector<pair<int,int>>>(0);
}

// Places a null piece at the passed yx board coordinates
Piece Board::null_piece(pair<int,int> pos)
{
    return Piece(coordinates[pos.first][pos.second]);
}

Player::Player(char s)
{
    s = toupper(s);
    side = s;
    if (s == 'W'){
        name = "White";
    } else {
        name = "Black";
    }
}

string Player::get_name()
{
    return name;
}

// TODO: Inserts chess pieces into player's pieces_list
void Player::capture_piece(Piece p)
{
    captured_pieces.push_back(p);
}

// TODO: Returns a vector of the player's pieces
vector<Piece> Player::list_pieces()
{
    return captured_pieces;
}

Game::Game(Board b)
{
    board = b;
}

void Game::start()
{
    board.build();
    board.set();

    board.print();
}

string Game::turn(Player P)
{
    bool valid = false;
    string selected_piece;

    std::cout << P.get_name() << " to move \n";
    while (!valid){
        std::cout << "Select a piece: ";
        std::cin >> selected_piece;

        for (auto &e: selected_piece){
            e = std::toupper(e);
        }


        if (selected_piece[0] >= 'A' && selected_piece[0] <= 'H' && 
            selected_piece[1] >= '1' && selected_piece[1] <= '8'){
                // std::cout << "Selecting piece at " << selected_piece << ".\n";
                valid = true;
        } else {
            std::cerr << "Invalid coordinate.\n\n";
        }
    }
    
    return selected_piece;
}

string Game::move_prompt(Player P, string start_pos)
{
    bool valid = false;
    string end_pos;

    while (!valid){
        std::cout << "Move piece to: ";
        std::cin >> end_pos;

        for (auto &e: end_pos){
            e = std::toupper(e);
        }


        if (end_pos[0] >= 'A' && end_pos[0] <= 'H' && 
            end_pos[1] >= '1' && end_pos[1] <= '8' && end_pos != start_pos){
                valid = true;
        } else {
            std::cerr << "Invalid coordinate.\n\n";
        }
    }
    
    return end_pos;
}

int Game::move(Player P, string start_pos)
{
    pair<char,int> coord = make_pair(start_pos[0],int(start_pos[1]-48));
    pair<int,int> yx_start = find_yx(coord);

    string end_pos = move_prompt(P, start_pos);
    pair<int,int> yx_end = find_yx(make_pair(end_pos[0],int(end_pos[1]-48)));
    // std::cout << "Start pos: (" << yx_start.first << "," << yx_start.second << ")\n"; 
    // std::cout << "End pos: (" << yx_end.first << "," << yx_end.second << ")\n"; 

    int status = board.move(yx_start,yx_end);
    board.print();

    return status;
}

// TODO: Remove moves from p1_moves if they aren't valid
int Board::validate_move(Piece &p1, Piece &p2)
{
    vector<vector<pair<int,int>>> p1_moves = p1.moves();

    bool found = false;
    int i = 0;
    int j;
    // Filter moves from list
    for (auto dir : p1_moves){
        j = 0;
        for (auto move: dir){
            // If possible move doesn't land on a null piece, removes all further moves
            if (find_piece(move).get_type() != 'N'){
                p1_moves[i].erase(p1_moves[i].begin()+(j+1),p1_moves[i].end());
            } 
            // If possible move lands on same piece type
            if (find_piece(move).get_type() == p1.get_type()){
                p1_moves[i].erase(p1_moves[i].begin()+j,p1_moves[i].end());
            }
            if (p1.get_name() == "Pawn"){
                if (p1.get_location().second != move.second && p2.get_type() != p1.opp()){
                    p1_moves[i].pop_back();
                } else if (p1.get_location().second == move.second && find_piece(move).get_type() != 'N'){
                    p1_moves[i].pop_back();
                }
            }
            j++;            
        }
        i++;
    }

    
    // std::cout << "Piece moves: ";
    for (auto e:p1_moves){
        for (auto f:e){
            // std::cout << "(" << f.first << "," << f.second << "), ";
            if (f == p2.get_location()){
                found = true;
            }
        }
    }

    if (found != true){
        std::cerr << "Invalid Move.\n";
        return 2;
    } 
    if (p2.get_type() == 'N'){
        return 0;
    } else if (p2.get_type() == p1.get_type()){
        std::cerr << "Same piece.\n";
        return 2;
    } else
        return 1;
    
}

int Board::move(pair<int,int> p1_yx, pair<int,int> p2_yx)
{    
    
    // Checks to see if p2_yx is in p1's move list
    int task = validate_move(board[p1_yx.first][p1_yx.second],board[p2_yx.first][p2_yx.second]);

    if (task == 1){ // p2 is enemy piece (Take and replace with N)
        board[p1_yx.first][p1_yx.second].setloc(p2_yx);
        board[p1_yx.first][p1_yx.second].move();

        board[p2_yx.first][p2_yx.second] = board[p1_yx.first][p1_yx.second];
        board[p1_yx.first][p1_yx.second] = null_piece(p1_yx);
        return 0;
    } else if (task == 0){ // p2 is an empty space (swap pieces)
        // Updates the Pieces' y,x coords are they are swapped
        board[p1_yx.first][p1_yx.second].setloc(p2_yx);
        board[p1_yx.first][p1_yx.second].move();

        board[p2_yx.first][p2_yx.second].setloc(p1_yx);
        swap(board[p1_yx.first][p1_yx.second],board[p2_yx.first][p2_yx.second]);
        return 0;
    } else {
        return 1;  
    }
}