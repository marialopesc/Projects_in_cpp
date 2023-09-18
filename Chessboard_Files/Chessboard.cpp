/*
 Student: Maria Bezerra
 UIN: 676493398
 CS 341 - Project #1
 Fall 2023
 */

#include "Chessboard.h"
#include <iostream>

using namespace std;

Chessboard::Chessboard() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j] = { None, Empty };
        }
    }
}

int Chessboard::place(int x, int y, Color c, Piece p) {
    if (x < 0 || x >= 8) return -1;
    if (y < 0 || y >= 8) return -2;

    // Validate color and piece
    if (c != White && c != Black) return -4;
    if (p < Rook || p > Pawn) return -5;

    // Check if the square is already occupied
    if (board[x][y].piece != Empty) return -3;

    board[x][y] = {c, p};
    return 1;
}

int Chessboard::get(int x, int y, Color &c, Piece &p) {
    if (x < 0 || x > 7) return -1;
    if (y < 0 || y > 7) return -2;
    if (board[x][y].piece == Empty) return -3;

    c = board[x][y].color;
    p = board[x][y].piece;
    return 1;
}

int Chessboard::move(int fromX, int fromY, int toX, int toY) {
    if (fromX < 0 || fromX > 7) return -1;
    if (fromY < 0 || fromY > 7) return -2;
    if (toX < 0 || toX > 7) return -3;
    if (toY < 0 || toY > 7) return -4;
    if (board[fromX][fromY].piece == Empty) return -5;
    if (board[toX][toY].piece != Empty) return -6;  // assuming we cannot capture in this simple example

    board[toX][toY] = board[fromX][fromY];
    board[fromX][fromY] = { None, Empty };
    return 1;
}

void Chessboard::print() {
    for (int y = 7; y >= 0; --y) {
        for (int x = 0; x < 8; ++x) {
            std::cout << "[" << x << "," << y << "] ";
        }
        std::cout << std::endl;
    }
}



Chessboard::Iterator::Iterator(Chessboard* cb, int pos) : board(cb), position(pos) {}

void Chessboard::Iterator::operator++() {
    position++;
}

void Chessboard::Iterator::xy(int &x, int &y) {
    x = position % 8;
    y = position / 8;
}

bool Chessboard::Iterator::operator!=(const Iterator &other) {
    return position != other.position;
}

Piece& Chessboard::Iterator::operator*() {
    int x, y;
    xy(x, y);
    return board->board[x][y].piece;
}

Color& Chessboard::Iterator::color() {
    int x, y;
    xy(x, y);
    return board->board[x][y].color;
}

Chessboard::Iterator Chessboard::begin() {
    return Iterator(this, 0);
}

Chessboard::Iterator Chessboard::end() {
    return Iterator(this, 64);
}
