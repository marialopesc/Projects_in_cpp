/*
 Student: Maria Bezerra
 UIN: 676493398
 CS 341 - Project #1
 Fall 2023
 */

enum Color { White, Black, None };
enum Piece { Rook, Knight, Bishop, Queen, King, Pawn, Empty };

class Chessboard {
public:
    Chessboard();
    int place(int x, int y, Color c, Piece p);
    int get(int x, int y, Color &c, Piece &p);
    int move(int fromX, int fromY, int toX, int toY);
    void print();

    class Iterator {
    public:
        Iterator(Chessboard* cb, int pos);
        void operator++();
        void xy(int &x, int &y);
        bool operator!=(const Iterator &other);
        Piece& operator*();
        Color& color();

    private:
        Chessboard* board;
        int position;
    };

    Iterator begin();
    Iterator end();

private:
    struct Cell {
        Color color;
        Piece piece;
    };

    Cell board[8][8];
};


