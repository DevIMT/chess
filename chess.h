#include <iostream>
#include <vector>

// TODO: Create a Piece class. Fill Board with Pieces (Null, White, Black)
class Piece {
    public:
        Piece() = default;
        Piece(std::string coord);
        Piece(char name, char type,std::string coord);
        void move(); // TODO
        void setname(char name); // TODO
        void settype(char type); // TODO
        void setsymbol(std::string symb);
        char get_name();
        char get_type();
        std::string get_symbol();
        std::string location();
    private:
        char name = ' ';
        std::string symbol = " \u26C9 ";
        char type = 'N';
        std::string loc;
};

class Board {
    public:
        Board() = default;
        void build();
        void set(); 
        void printCoords();
        void print();
    private:
        std::vector<std::vector<Piece>> board;
        const std::vector<std::vector<std::string>> coordinates{
         {"A8","B8","C8","D8","E8","F8","G8","H8"},
         {"A7","B7","C7","D7","E7","F7","G7","H7"},
         {"A6","B6","C6","D6","E6","F6","G6","H6"},
         {"A5","B5","C5","D5","E5","F5","G5","H5"},
         {"A4","B4","C4","D4","E4","F4","G4","H4"},
         {"A3","B3","C3","D3","E3","F3","G3","H3"},
         {"A2","B2","C2","D2","E2","F2","G2","H2"},
         {"A1","B1","C1","D1","E1","F1","G1","H1"}};
};

class Player {
    public:
        Player();
        Player(char side);
        void setpieces();
        void movePiece();
    private:
        char side = 'W';
        Piece pieces[16];

};