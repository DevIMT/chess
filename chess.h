#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Piece {
    public:
        Piece() = default;
        Piece(pair<char,int> coord);
        Piece(string name, char type,pair<char,int> coord);
        vector<pair<int,int>> moves(); // TODO
        void setname(string name);
        void settype(char type);
        void setsymbol(string symb);
        string get_name();
        char get_type();
        string get_symbol();
        pair<char,int> location();
    private:
        string name = "Null";
        string symbol = " \u26C9 ";
        char type = 'N';
        int movecount = 0;
        pair<char,int> loc = make_pair('A',1);
};

class Player {
    public:
        Player() = default;
        Player(char s);
        string get_name();
        void capture_piece(Piece p);
        vector<Piece> list_pieces();
    private:
        string name = "White";
        char side = 'W';
        vector<Piece> captured_pieces;

};

class Board {
    public:
        Board() = default;
        void build();
        void set(); 
        Piece move(Piece p1, Piece p2);
        void printCoords();
        void printCoords(ofstream &outfile);
        void print();
    private:
        vector<vector<Piece>> board;
        vector<vector<pair<char,int>>> coordinates{
         {make_pair('A',8),make_pair('B',8),make_pair('C',8),make_pair('D',8),make_pair('E',8),make_pair('F',8),make_pair('G',8),make_pair('H',8)},
         {make_pair('A',7),make_pair('B',7),make_pair('C',7),make_pair('D',7),make_pair('E',7),make_pair('F',7),make_pair('G',7),make_pair('H',7)},
         {make_pair('A',6),make_pair('B',6),make_pair('C',6),make_pair('D',6),make_pair('E',6),make_pair('F',6),make_pair('G',6),make_pair('H',6)},
         {make_pair('A',5),make_pair('B',5),make_pair('C',5),make_pair('D',5),make_pair('E',5),make_pair('F',5),make_pair('G',5),make_pair('H',5)},
         {make_pair('A',4),make_pair('B',4),make_pair('C',4),make_pair('D',4),make_pair('E',4),make_pair('F',4),make_pair('G',4),make_pair('H',4)},
         {make_pair('A',3),make_pair('B',3),make_pair('C',3),make_pair('D',3),make_pair('E',3),make_pair('F',3),make_pair('G',3),make_pair('H',3)},
         {make_pair('A',2),make_pair('B',2),make_pair('C',2),make_pair('D',2),make_pair('E',2),make_pair('F',2),make_pair('G',2),make_pair('H',2)},
         {make_pair('A',1),make_pair('B',1),make_pair('C',1),make_pair('D',1),make_pair('E',1),make_pair('F',1),make_pair('G',1),make_pair('H',1)}};
};

class Game {
    public:
        Game();
        void start();
        string turn(Player P); // TODO
        void move(Player P);
    private:
};

pair<int,int> find_yx(pair<char,int> coord);