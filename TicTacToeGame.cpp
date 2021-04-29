#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <string>
#include <cctype>
#include "ticTacToeConstants.hpp"
#include "ticTacToeClass.hpp"

using namespace std;

void createTicTacToeBoard(string ticTacToeBoard[TICTACTOEROWS][TICTACTOECOLUMNS], int boardBox);

void showTicTacToeBoard(string ticTacToeBoard[TICTACTOEROWS][TICTACTOECOLUMNS]);

void addingToTicTacToeBoard(XandO players, string& placement, BoardPlacement& ticTacToeSetUp, bool& playerOneTurn);

void adjustTicTacToeBoard(string ticTacToeBoard[TICTACTOEROWS][TICTACTOECOLUMNS], string placement, XandO players);

int main()
{
    //variables
    string ticTacToeBoard[TICTACTOEROWS][TICTACTOECOLUMNS];
    string players = "";
    int boardBox = 1;
    string placement = "";
    string name = "";
    char symbol;
    char playAgain;
    string enemyPlay = "";

    //class variables
    XandO player1;
    XandO player2;
    AI enemy;

    do
    {
        //variable that need to be redeclared at start of game
        BoardPlacement ticTacToeSetUp;
        bool playerOneTurn = true;
        bool singlePlayer = false;

        cout << "Welcome To TicTacToe!" << endl;

        do//asks for number of players
        {

            cout << "Would You Like To Play With 1 or 2 Players? (1/2)" << endl;
            cin >> players;

        } while (players != "1" && players != "2" );//checks for valid entry
    
        for(int count = 0; count < stoi(players); count++)//obtains player(s) names and symbols to use
        {
            do
            {
                if(count == 0)
                {
                    cout << "Player 1, enter your name and symbol you want to use (X or O) seperated with a space" << endl;
                    cin >> name >> symbol;
                }
                else
                {
                    cout << "Player 2, enter your name" << endl;
                    cin >> name;
                }
            
            } while (toupper(symbol) != 'X' && toupper(symbol) != 'O');

            if(count == 0)
            {
                player1.setName(name);
                player1.setSymbol(toupper(symbol));
                player1.setPlayer1Or2(PLAYER1SPOT);
            }
            else
            {
                player2.setName(name);
                player2.oppositeSymbol(toupper(symbol));
                player2.setPlayer1Or2(PLAYER2SPOT);
           
            }
        }    

        if(players == "1")//creates enemy AI if 1 player was chosen
        {
            singlePlayer = true;
            enemy.setName("ENEMY");
            enemy.oppositeSymbol(toupper(symbol));
            enemy.setPlayer1Or2(PLAYER2SPOT);

        }

        createTicTacToeBoard(ticTacToeBoard, boardBox);//creates the tictactoe board inside a 2D array

        showTicTacToeBoard(ticTacToeBoard);//displays the tictactoe board to the console

        //allows the game to be played until a side wins or if there is a tie
        do
        {

            if(playerOneTurn)//player 1's turn
            {
                addingToTicTacToeBoard(player1, placement, ticTacToeSetUp, playerOneTurn);

                adjustTicTacToeBoard(ticTacToeBoard, placement, player1);

                showTicTacToeBoard(ticTacToeBoard);
            }
            else//player 2's or AI's turn
            {
                if(singlePlayer)//AI
                {
                    enemyPlay = to_string(enemy.enemyPlacement(ticTacToeSetUp));

                    ticTacToeSetUp.setPlacement(stoi(enemyPlay), enemy.getPlayer1Or2());

                    playerOneTurn = !playerOneTurn;

                    adjustTicTacToeBoard(ticTacToeBoard, enemyPlay, enemy);

                    cout << endl;

                    showTicTacToeBoard(ticTacToeBoard);
                    
                }
                else//player 2
                {
                    addingToTicTacToeBoard(player2, placement, ticTacToeSetUp, playerOneTurn);
                
                    adjustTicTacToeBoard(ticTacToeBoard, placement, player2);

                    showTicTacToeBoard(ticTacToeBoard);
                }
              
            }

        } while (!ticTacToeSetUp.checkIfWon(playerOneTurn) && !ticTacToeSetUp.checkIfTie());//checks for win or tie
        
        //displays message based on who wins
        if(!playerOneTurn && ticTacToeSetUp.checkIfWon(playerOneTurn))
        {
            cout << "CONGRATULATIONS " << player1.getName() << ", YOU WIN!" << endl;
        }
        else if(ticTacToeSetUp.checkIfWon(playerOneTurn) && !singlePlayer)
        {
            cout << "CONGRATULATIONS " << player2.getName() << ", YOU WIN!" << endl;
        }
        else if(ticTacToeSetUp.checkIfWon(playerOneTurn))
        {
            cout << "SORRY " << player1.getName() << ", YOU LOST!" << endl;
        }
        else
        {
            cout << "IT'S A TIE!" << endl;
        }

        cout << "Would you like to play again? (Y for YES)(Any other character for NO)" << endl;
        
        cin >> playAgain;

    } while (toupper(playAgain) == 'Y');//repeats the game
        
    
    
}
//creates a 2D array that will be the tictactoe board
void createTicTacToeBoard(string ticTacToeBoard[TICTACTOEROWS][TICTACTOECOLUMNS], int boardBox)
{
    
    for(int row = 0; row < TICTACTOEROWS; row++)
    {
        for(int col = 0; col < TICTACTOECOLUMNS; col++)
        {
            if(col == 0 || col == 5 || col == 10 || col == 15)
                ticTacToeBoard[row][col] = "|";
            else if((col == 2 || col == 7 || col == 12) && (row == 0 || row == 2 || row == 4))
                ticTacToeBoard[row][col] = "#";
            else if((col == 3 || col == 8 || col == 13) && (row == 0 || row == 2 || row == 4))
            {
                ticTacToeBoard[row][col] = to_string(boardBox);
                boardBox++;
            }     
            else
                ticTacToeBoard[row][col] = " ";
            
        }
    }
}

//displays the 2D that contains the tictactoe board
void showTicTacToeBoard(string ticTacToeBoard[TICTACTOEROWS][TICTACTOECOLUMNS])
{
    
   for(int row = 0; row < TICTACTOEROWS; row++)
    {
        for(int col = 0; col < TICTACTOECOLUMNS; col++)
        {
            cout << ticTacToeBoard[row][col];
        }

        cout << endl;
    }
}

//prompts a player for a placement on the tictactoe board
void addingToTicTacToeBoard(XandO players, string& placement, BoardPlacement& ticTacToeSetUp, bool& playerOneTurn)
{
    do
    {
        cout << players.getName() << "! Choose a location To Place An " << players.getSymbol() << "! (Enter The Number)" << endl;
        cin >> placement;

    } while (!ticTacToeSetUp.checkIfValidPlacement(placement));

    ticTacToeSetUp.setPlacement(stoi(placement), players.getPlayer1Or2());

    playerOneTurn = !playerOneTurn;
}

//adds a symbol to a desired location of the 2D array containing the tictactoe board
void adjustTicTacToeBoard(string ticTacToeBoard[TICTACTOEROWS][TICTACTOECOLUMNS],string newPlacement, XandO players)
{
    int placement = stoi(newPlacement);

    if(players.getSymbol() == 'X')
    {
        ticTacToeBoard[int(0 + 2*(floor(placement/3.5)))][int(1 + (placement - 3*(floor(placement/3.5)) - 1)*5)] = "\\";
        ticTacToeBoard[int(1 + 2*(floor(placement/3.5)))][int(1 + (placement - 3*(floor(placement/3.5)) - 1)*5)] = "/";
        ticTacToeBoard[int(0 + 2*(floor(placement/3.5)))][int(4 + (placement - 3*(floor(placement/3.5)) - 1)*5)] = "/";
        ticTacToeBoard[int(1 + 2*(floor(placement/3.5)))][int(4 + (placement - 3*(floor(placement/3.5)) - 1)*5)] = "\\";

        ticTacToeBoard[int(2*(floor(placement/3.5)))][int(2 + (placement - 3*(floor(placement/3.5)) - 1)*5)] = " ";
        ticTacToeBoard[int(2*(floor(placement/3.5)))][int(3 + (placement - 3*(floor(placement/3.5)) - 1)*5)] = " ";
    }
    else
    {
        ticTacToeBoard[int(0 + 2*(floor(placement/3.5)))][int(1 + (placement - 3*(floor(placement/3.5)) - 1)*5)] = "[";
        ticTacToeBoard[int(1 + 2*(floor(placement/3.5)))][int(1 + (placement - 3*(floor(placement/3.5)) - 1)*5)] = "[";
        ticTacToeBoard[int(0 + 2*(floor(placement/3.5)))][int(4 + (placement - 3*(floor(placement/3.5)) - 1)*5)] = "]";
        ticTacToeBoard[int(1 + 2*(floor(placement/3.5)))][int(4 + (placement - 3*(floor(placement/3.5)) - 1)*5)] = "]";

        ticTacToeBoard[int(2*(floor(placement/3.5)))][int(2 + (placement - 3*(floor(placement/3.5)) - 1)*5)] = " ";
        ticTacToeBoard[int(2*(floor(placement/3.5)))][int(3 + (placement - 3*(floor(placement/3.5)) - 1)*5)] = " ";
    }
}
