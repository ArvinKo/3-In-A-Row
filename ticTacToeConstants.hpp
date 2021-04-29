#ifndef TICTACTOECONSTANTS_HPP
#define TICTACTOECONSTANTS_HPP

using namespace std;

//constants for creating the board
const int TICTACTOECOLUMNS = 16;
const int TICTACTOEROWS = 6;

//constants used in the BoardPlacement class
const int TICTACTOEPLACEMENTROWS = 3;
const int TICTACTOEPLACEMENTCOLS = 3;
const int TICTACTOEPLACEMENTLOCATIONSROWS = 9;
const int TICTACTOEPLACEMENTLOCATIONSCOLS = 2;
const int TICTACTOEPLACEMENTLOCATIONS[TICTACTOEPLACEMENTLOCATIONSROWS][TICTACTOEPLACEMENTLOCATIONSCOLS] = {{0,0},{0,1},{0,2},{1,0},{1,1},{1,2},{2,0},{2,1},{2,2}};
const int COL1 = 0;
const int COL2 = 1;

const int PLAYER1SPOT = 1;
const int PLAYER2SPOT = 2;

const string VALIDBOARDPOSITIONS[TICTACTOEPLACEMENTLOCATIONSROWS] =  {"1","2","3","4","5","6","7","8","9"};

//constants used by enemy AI
const int CHECKROWS = 3;
const int CHECKCOLS = 4;
const int ENEMYROWS = 6;
const int ENEMYCOLS = 3;

const int HORIZONTALCHECK[CHECKROWS][CHECKCOLS] = {{1,2,2,3},{4,5,5,6},{7,8,8,9}};
const int VERTICALCHECK[CHECKROWS][CHECKCOLS] = {{1,4,4,7},{2,5,5,8},{3,6,6,9}};
const int DIAGONALCHECK[CHECKROWS-1][CHECKCOLS] = {{1,5,5,9},{3,5,5,7}};

const int ENEMYPLAY[ENEMYROWS][ENEMYCOLS] = {{3,6,9},{1,4,7},{7,8,9},{1,2,3},{9,7,0},{1,3,0}};

#endif