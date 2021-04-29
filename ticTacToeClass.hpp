#ifndef TICTACTOECLASS_HPP
#define TICTACTOECLASS_HPP
#include "ticTacToeConstants.hpp"

using namespace std;
//class containing information about the player
class Player
{
  protected:
    char symbol;      
    string name;
    int player1Or2;

  public:
    //constructors
    Player()
    {
        symbol;
        name = "";
        player1Or2 = 1;
    }

    Player(string newName, char newSymbol, int newPlayer1Or2)
    {
        name = newName;
        symbol = newSymbol;
        player1Or2 = newPlayer1Or2;
    }
    
    //accessors and mutators
    string getName() const
    {
        return name;
    }
    
    char getSymbol() const
    {
        return symbol;
    }
    
    int getPlayer1Or2() const
    {
        return player1Or2;
    }

    void setName(string newName)
    {
        name = newName;
    }

    void setSymbol(char newSymbol)
    {
        symbol = newSymbol;
    }

    void setPlayer1Or2(int newPlayer1Or2)
    {
        player1Or2 = newPlayer1Or2;
    }
    
};

//class derived from the Player class 
class XandO: public Player
{
    private:

    public:
        //function that changes the symbol of an object from the XandO class to the opposite symbol given
        void oppositeSymbol(char newSymbol) 
        {
            if(newSymbol == 'O')
            {
                symbol = 'X';
            }
            else
            {
                symbol = 'O';
            }
        }

};

//class that manipulates and checks the tictactoe board
class BoardPlacement
{
  private:
    int boardPlacement[TICTACTOEPLACEMENTROWS][TICTACTOEPLACEMENTCOLS] = {0,0,0,0,0,0};

  public:
    //constructor
    BoardPlacement()
    {
        boardPlacement[TICTACTOEPLACEMENTROWS][TICTACTOEPLACEMENTCOLS];
    }
    
    //accessors and mutators
    int getPlacement(int location) const
    {
        return boardPlacement[TICTACTOEPLACEMENTLOCATIONS[location-1][COL1]][TICTACTOEPLACEMENTLOCATIONS[location-1][COL2]];
    }
      
    void setPlacement(int location, int player1Turn)
    {
        boardPlacement[TICTACTOEPLACEMENTLOCATIONS[location-1][COL1]][TICTACTOEPLACEMENTLOCATIONS[location-1][COL2]] = player1Turn;
    }

    //determines if given placement is valid on the current tactactoe board
    bool checkIfValidPlacement(string location) const
    {
        bool valid = false;

        for(int count = 0; count < TICTACTOEPLACEMENTLOCATIONSROWS; count++)
        {
            if(location == VALIDBOARDPOSITIONS[count])
            {
                valid = true;
            }
        }

        if(!valid)
        {
            return false;
        }

        int boardPosition = boardPlacement[TICTACTOEPLACEMENTLOCATIONS[stoi(location)-1][COL1]][TICTACTOEPLACEMENTLOCATIONS[stoi(location)-1][COL2]];
        
        if(boardPosition == 0)
        {
            return true;
        }

        return false;
    }

    //checks if a player has won or not
    bool checkIfWon(bool player1Turn) const
    {
        int valueToCheck = 0;

        if(player1Turn)
        {
            valueToCheck = 2;
        }
        else
        {
            valueToCheck = 1;
        }

        for(int row = 0; row < TICTACTOEPLACEMENTROWS; row++)
        {
           if((boardPlacement[row][0] == valueToCheck) && (boardPlacement[row][1] == valueToCheck) && (boardPlacement[row][2] == valueToCheck))
           {
               return true;
           }
        }

        for(int col = 0; col < TICTACTOEPLACEMENTCOLS; col++)
        {
           if((boardPlacement[0][col] == valueToCheck) && (boardPlacement[1][col] == valueToCheck) && (boardPlacement[2][col] == valueToCheck))
           {
               return true;
           }
        }

        bool diagonal1 = (boardPlacement[0][0] == valueToCheck) && (boardPlacement[1][1] == valueToCheck) && (boardPlacement[2][2] == valueToCheck);
        bool diagonal2 = (boardPlacement[0][2] == valueToCheck) && (boardPlacement[1][1] == valueToCheck) && (boardPlacement[2][0] == valueToCheck);

        if(diagonal1 || diagonal2)
        {
            return true;
        }

        return false;

    }

    //checks if the game resulted in a tie
    bool checkIfTie() const
    {
        
        for(int row = 0; row < TICTACTOEPLACEMENTROWS; row++)
        {
            for(int col = 0; col < TICTACTOEPLACEMENTCOLS; col++)
            {
                if(boardPlacement[row][col] == 0)
                {
                    return false;
                }
            }
        }

        return true;

    }
    
};

//class derived from the XandO class that conatins functionalities of the enemy AI
class AI: public XandO
{
private:

public:
    //returns a placement on the board to either block the user or win
    int blockOrWin(BoardPlacement ticTacToeSetUp, int defOrOff) const
    {
        bool check1 = false;
        bool check2 = false;
        bool check3= false;
        bool check4 = false;
        bool check5= false;
        bool check6 = false;

        //checks the board to determine where and how to play offensively or defensively
        for(int row = 0; row < CHECKROWS; row++)
        {
            //checks horizontal possibilities
            check1 = (ticTacToeSetUp.getPlacement(HORIZONTALCHECK[row][0])) == defOrOff && (ticTacToeSetUp.getPlacement(HORIZONTALCHECK[row][1])) == defOrOff && (ticTacToeSetUp.getPlacement(ENEMYPLAY[0][row])) == 0;
            check2 = (ticTacToeSetUp.getPlacement(HORIZONTALCHECK[row][2])) == defOrOff && (ticTacToeSetUp.getPlacement(HORIZONTALCHECK[row][3])) == defOrOff && (ticTacToeSetUp.getPlacement(ENEMYPLAY[1][row])) == 0;
            
             //checks vertical possibilities
            check3 = (ticTacToeSetUp.getPlacement(VERTICALCHECK[row][0])) == defOrOff && (ticTacToeSetUp.getPlacement(VERTICALCHECK[row][1])) == defOrOff && (ticTacToeSetUp.getPlacement(ENEMYPLAY[2][row])) == 0;
            check4 = (ticTacToeSetUp.getPlacement(VERTICALCHECK[row][2])) == defOrOff && (ticTacToeSetUp.getPlacement(VERTICALCHECK[row][3])) == defOrOff && (ticTacToeSetUp.getPlacement(ENEMYPLAY[3][row])) == 0;
            
             //checks diagonal possibilities
            if(row < 2)
            {
                check5 = (ticTacToeSetUp.getPlacement(DIAGONALCHECK[row][0])) == defOrOff && (ticTacToeSetUp.getPlacement(DIAGONALCHECK[row][1])) == defOrOff && (ticTacToeSetUp.getPlacement(ENEMYPLAY[4][row])) == 0;
                check6 = (ticTacToeSetUp.getPlacement(DIAGONALCHECK[row][2])) == defOrOff && (ticTacToeSetUp.getPlacement(DIAGONALCHECK[row][3])) == defOrOff && (ticTacToeSetUp.getPlacement(ENEMYPLAY[5][row])) == 0;
            }

            //checks if it can make a play to block player 1 or to win
            if(check1 || check2 || check3 || check4 || check5 || check6)
            {
                if(check1)
                {
                    return ENEMYPLAY[0][row];

                }else if(check2)
                {
                    return ENEMYPLAY[1][row];
                }
                else if(check3)
                {
                   return ENEMYPLAY[2][row];
                }
                else if(check4)
                {
                     return ENEMYPLAY[3][row];
                }
                else if(check5)
                {
                    return ENEMYPLAY[4][row];
                }
                else
                {
                    return ENEMYPLAY[5][row];
                }
            }
        
        }

        return -1;//returns -1 if it cant block the opponent or win
    }

    //function that returns the AI's final placement decisions
    int enemyPlacement(BoardPlacement ticTacToeSetUp)
    {
        //variables that contain a placement choice for either blocking the user or to win
        int defPlacement = blockOrWin(ticTacToeSetUp, 1);
        int offPlacement = blockOrWin(ticTacToeSetUp, 2);
        int placement = 0;

        if(defPlacement < 0 && offPlacement < 0)//if AI cant block or win
        {
            bool valid = false;

            while(!valid)
            {
                srand(time(0));
                placement = (rand() % TICTACTOEPLACEMENTLOCATIONSROWS) + 1;
                valid = ticTacToeSetUp.checkIfValidPlacement(to_string(placement));//random placement
            }

            return placement;
        }
        else if(offPlacement >= 0)//returns placement to win
        {
            return offPlacement;
        }
        else//returns placement to block
        {
            return defPlacement;
        }
    }

};

#endif