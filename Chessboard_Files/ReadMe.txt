# Projects_in_cpp
Projects created using C++

// Chessboard Container and Iterator in C++
This C++ project demonstrates how to implement a 2D matrix (8x8) chessboard along with an iterator to traverse the board. 
The program offers a simple API to place, get, and move pieces on the board.

// Features
8x8 Chessboard Matrix
Enumerations for Colors and Pieces
Place pieces on the board
Get the piece at a specific position
Move a piece from one position to another
Print the board state
Iterator for the board
Requirements
C++11 or higher
CMake 3.10 or higher (for building the project)

// API
int place(int x, int y, Color c, Piece p): Places a piece on the board at coordinates (x,y). Returns various status codes depending on the success of the operation.
int get(int x, int y, Color &c, Piece &p): Gets the piece and its color at coordinates (x,y). Returns a status code.
int move(int fromX, int fromY, int toX, int toY): Moves a piece from coordinates (fromX, fromY) to (toX, toY). Returns a status code.
void print(): Prints the current state of the board.

// Extended Description
This project aims to emulate a chessboard and its operations in a simplified manner using C++. It provides a container class named Chessboard that abstracts the complexities 
of piece placement, movement, and board state representation. The class offers a rich API that can be easily used to implement chess logic.

Each cell on the board is represented as an object containing color and piece information, making it easier to extend the program's functionalities in the future.

One of the key features is the board iterator, which can be used to loop through all cells in the board in a specific order, making it convenient to apply algorithms and 
search techniques for game development.

With minimal dependencies and a straightforward setup, this project serves as an excellent base for those looking to understand container implementation and iterators in C++. It can be further extended to include more advanced features like game rules, AI, etc.
